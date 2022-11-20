#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

#define API_VER 2
#include "console_inputter.h"
#include "console_printer.h"
#include "interface.h"
lc3::ConsolePrinter printer;
lc3::ConsoleInputter inputter;
uint32_t print_level = 4;

bool is_prime(int n) {
  if (n <= 3) return true;
  if (n % 2 == 0 || n % 3 == 0) return false;
  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) return false;
  }
  return true;
}

// Assemble assembly code
const string assemble(const string& filename) {
  if (filename.empty()) return "";
  // Initialize
  static bool enable_liberal_asm = false;
  static lc3::as assembler(printer, print_level, enable_liberal_asm);
  return assembler.assemble(filename)->first;
}

// Test assembled program
bool test(const string& filename) {
  if (filename.empty()) return false;
  // Initialize
  static bool init_flag = true;
  static bool ignore_privilege = false;
  static uint32_t inst_limit = 1919810;
  static lc3::sim simulator(printer, inputter, print_level);
  if (init_flag) {
    simulator.setIgnorePrivilege(ignore_privilege);
    simulator.setRunInstLimit(inst_limit);
    init_flag = false;
  }
  vector<uint16_t> data(10000);
  iota(data.begin(), data.end(), 0);
  for (uint16_t r0 : data) {
    // Set machine state
    simulator.zeroState();
    if (!simulator.loadObjFile(filename)) {
      cerr << "Error: invalid file " << filename << endl;
      return false;
    }
    simulator.writeReg(0, r0);
    // Run and check
    simulator.runUntilHalt();
    cout << r0 << "\t" << simulator.readReg(1) << endl;
    if (simulator.readReg(1) != is_prime(r0)) return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  if (test(assemble("../../rs/lab5/prime.asm")))
    cout << "---TEST PASSED---" << endl;
  else
    cout << "---TEST FAILED---" << endl;
  return 0;
}