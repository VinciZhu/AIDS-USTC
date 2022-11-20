#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>

#define API_VER 2
#include "console_inputter.h"
#include "console_printer.h"
#include "interface.h"

using namespace std;
using namespace lc3;

const int CASE_NUM = 50;
const string ASM_SUFFIX = ".asm";
uint32_t print_level = 4;
bool enable_liberal_asm = false;
bool ignore_privilege = false;
uint32_t inst_limit = 1919810;

uint16_t F(uint16_t n) {
  static uint16_t f[0x4000] = {1, 1, 2};
  return f[n] ? f[n] : f[n] = (F(n - 1) + 2 * F(n - 3)) % 1024;
}

int main(int argc, char* argv[]) {
  if (argc != 2) return 0;
  // Initialize
  ConsolePrinter printer;
  ConsoleInputter inputter;
  lc3::as assembler(printer, print_level, enable_liberal_asm);
  lc3::sim simulator(printer, inputter, print_level);
  simulator.setIgnorePrivilege(ignore_privilege);
  simulator.setRunInstLimit(inst_limit);
  string filename(argv[1]);
  if (filename.size() >= ASM_SUFFIX.size() &&
      equal(ASM_SUFFIX.rbegin(), ASM_SUFFIX.rend(), filename.rbegin()))
    filename = assembler.assemble(filename)->first;
  else {
    cerr << "invalid asm file" << endl;
    return 0;
  }
  // Test
  uint64_t prev_count, sum = 0;
  uint16_t n, result, sample[] = {20, 6, 13, 72, 0, 1, 2, 3};
  mt19937 gen(unsigned(time(0)));
  uniform_int_distribution<uint16_t> dis(0x0000, 0x4000);
  for (int i = 0; i < CASE_NUM; i++) {
    // Generate random numbers
    n = i < 8 ? sample[i] : dis(gen);
    // Set machine state
    prev_count = simulator.getInstExecCount();
    simulator.zeroState();
    simulator.writeReg(0, n);
    if (!simulator.loadObjFile(filename)) {
      cerr << "invalid obj file" << endl;
      return 0;
    }
    // Run and check
    simulator.runUntilHalt();
    result = static_cast<uint16_t>(simulator.readReg(7));
    if (F(n) != result) {
      cerr << "wrong answer" << endl;
      return 0;
    }
    sum += simulator.getInstExecCount() - prev_count;
    cout << "F(" << n << ") = " << result << endl;
  }
  // Print result
  cout << CASE_NUM << " testing cases passed" << endl;
  cout << "instruction count: " << sum << endl;
  cout << "average instruction count: " << 1.0 * sum / CASE_NUM << endl;
  return 0;
}