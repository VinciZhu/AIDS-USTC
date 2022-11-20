#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>

#define API_VER 2
#include "common.h"
#include "console_inputter.h"
#include "console_printer.h"
#include "interface.h"

using namespace std;

const int CASE_NUM = 100;
const string OBJ_SUFFIX = ".obj";
const string BIN_SUFFIX = ".bin";
uint32_t print_level = 4;
bool enable_liberal_asm = false;
bool ignore_privilege = false;
uint32_t inst_limit = 1919810;

int main(int argc, char* argv[]) {
  if (argc != 2) return 0;
  // Initialize
  lc3::ConsolePrinter printer;
  lc3::ConsoleInputter inputter;
  lc3::conv converter(printer, print_level);
  lc3::as assembler(printer, print_level, enable_liberal_asm);
  lc3::sim simulator(printer, inputter, print_level);
  simulator.setIgnorePrivilege(ignore_privilege);
  simulator.setRunInstLimit(inst_limit);
  string filename(argv[1]);
  if (filename.size() < OBJ_SUFFIX.size() ||
      !equal(OBJ_SUFFIX.rbegin(), OBJ_SUFFIX.rend(), filename.rbegin())) {
    filename =
        filename.size() > BIN_SUFFIX.size() &&
                equal(BIN_SUFFIX.rbegin(), BIN_SUFFIX.rend(), filename.rbegin())
            ? *converter.convertBin(filename)
            : assembler.assemble(filename)->first;
  }

  // Test
  uint64_t prev_count, sum = 0;
  int16_t num0, num1, result,
      sample[5][2] = {{1, 1}, {5, 4000}, {4000, 5}, {-500, 433}, {-114, -233}};
  mt19937 gen(unsigned(time(0)));
  uniform_int_distribution<int16_t> dis(0x0000, 0xffff);
  for (int i = 0; i < CASE_NUM; i++) {
    // Generate random numbers
    i < 5 ? (num0 = sample[i][0], num1 = sample[i][1])
          : (num0 = dis(gen), num1 = dis(gen));
    // Set machine state
    prev_count = simulator.getInstExecCount();
    simulator.zeroState();
    simulator.writeReg(0, num0);
    simulator.writeReg(1, num1);
    if (!simulator.loadObjFile(filename)) {
      cerr << "invalid obj file" << endl;
      return 0;
    }
    // Run and check
    simulator.runUntilHalt();
    result = static_cast<int16_t>(simulator.readReg(7));
    if ((int16_t)(num0 * num1) != result) {
      cerr << "wrong answer" << endl;
      return 0;
    }
    sum += simulator.getInstExecCount() - prev_count;
    if (i < 5) cout << num0 << " * " << num1 << " = " << result << endl;
    if (i == 4) cout << "average instruction count: " << 1.0 * sum / 5 << endl;
  }
  // Print result
  cout << CASE_NUM - 5 << " random cases passed" << endl;
  cout << "instruction count: " << sum << endl;
  cout << "average instruction count: " << 1.0 * sum / CASE_NUM << endl;
  return 0;
}