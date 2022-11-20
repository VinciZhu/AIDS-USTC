#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>

#define API_VER 2
#include "console_inputter.h"
#include "console_printer.h"
#include "interface.h"

using namespace std;
using namespace lc3;

const int CASE_NUM = 10, SAMPLE_NUM = 10;
const uint16_t SAMPLE[SAMPLE_NUM] = {24,   144,  456,  1088,  1092,
                                     2096, 4200, 8192, 12000, 14000};
uint32_t print_level = 0;
bool enable_liberal_asm = false;
bool ignore_privilege = false;
uint32_t inst_limit = 1919810;
ConsolePrinter printer;
ConsoleInputter inputter;

uint16_t F(uint16_t n) {
  static uint16_t f[0x4001] = {1, 1, 2};
  return f[n] ? f[n] : f[n] = (F(n - 1) + 2 * F(n - 3)) % 1024;
}

void test(const string& filename, const string& out_filename) {
  lc3::as assembler(printer, print_level, enable_liberal_asm);
  string file = assembler.assemble(filename)->first;
  ofstream out(out_filename);
  if (!out) {
    cerr << "Error: cannot open file " << out_filename << endl;
    return;
  }
  lc3::sim simulator(printer, inputter, print_level);
  simulator.setIgnorePrivilege(ignore_privilege);
  simulator.setRunInstLimit(inst_limit);

  // Test
  uint64_t prev_count, sum = 0;
  uint16_t n, result;
  bool is_wrong = false;
  mt19937 gen(unsigned(time(0)));
  uniform_int_distribution<uint16_t> dis(0x0000, 0x4000);
  out << left;
  for (int i = 0; i < CASE_NUM; i++) {
    // Set machine state
    simulator.zeroState();
    if (!simulator.loadObjFile(file)) {
      cerr << "Error: invalid file " << filename << endl;
      out.close();
      exit(1);
    }
    n = i < SAMPLE_NUM ? SAMPLE[i] : dis(gen);
    simulator.writeReg(0, n);
    prev_count = simulator.getInstExecCount();
    // Run and check
    simulator.runUntilHalt();
    result = static_cast<uint16_t>(simulator.readReg(7));
    sum += simulator.getInstExecCount() - prev_count;
    out << "Case " << setw(4) << i + 1 << setw(8) << ("F(" + to_string(n) + ")")
        << " =    " << setw(8) << result;
    if (F(n) != result) {
      out << "Wrong answer!";
      is_wrong = true;
    }
    out << endl;
  }
  // Print result
  out << "correctness: " << (is_wrong ? "wrong" : "correct") << endl;
  out << "instruction count: " << sum << endl;
  out << "average instruction count: " << 1.0 * sum / CASE_NUM << endl;

  // Get line count
  ifstream in(filename);
  if (!in) {
    cerr << "Error: cannot open file " << filename << endl;
    exit(1);
  }
  string line;
  sum = -1;
  getline(in, line);
  while (!in.eof()) {
    getline(in, line);
    if (line != "") sum++;
  }
  out << "line count: " << sum << endl;
  out.close();
}

int main(int argc, char* argv[]) {
  if (argc != 2) return 0;
  string filename(argv[1]);
  auto p = filename.find_last_of('.');
  string name = p == string::npos ? filename : filename.substr(0, p);
  string out_filename(name + ".out");
  test(filename, out_filename);
  return 0;
}