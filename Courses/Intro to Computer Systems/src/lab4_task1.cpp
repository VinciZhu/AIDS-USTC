#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

#define API_VER 2
#include "console_inputter.h"
#include "console_printer.h"
#include "interface.h"
lc3::ConsolePrinter printer;
lc3::ConsoleInputter inputter;
uint32_t print_level = 4;

// Generate possible machine code
const vector<string> generate(const string& filename) {
  vector<string> out_names;
  if (filename.empty()) return out_names;
  string content;
  getline(ifstream(filename), content, '\0');
  string dir = filename.substr(0, filename.find_last_of('/')) + "/gen";
  filesystem::create_directory(dir);
  vector<int> indices;
  for (int i = 0; i < content.size(); i++)
    if (content[i] == 'x') indices.push_back(i);
  int n = indices.size();
  for (int cnt = 0; cnt < 1 << n; cnt++) {
    for (int i = 0; i < n; i++)
      content[indices[i]] = '0' + ((cnt & 1 << i) > 0);
    string dir_i = dir + '/' + to_string(cnt);
    filesystem::create_directory(dir_i);
    string out_name = dir_i + '/' + to_string(cnt) + ".txt";
    ofstream(out_name) << content;
    out_names.push_back(out_name);
  }
  return out_names;
}

// Translate machine code into assembly code
const string translate(const string& filename) {
  if (filename.empty()) return "";
  string name = filename.substr(0, filename.find_last_of('.'));
  ifstream in(filename);
  ofstream out(name + ".asm");

  uint16_t PC = 0x3000, opcode, DR, SR1, SR2, BaseR, trapvect8;
  int16_t imm5, PCoffset9, PCoffset11, offset6;
  map<uint16_t, string> branch_labels;
  map<uint16_t, string> subroutine_labels;
  map<uint16_t, string> data_labels;
  bool is_data = false;
  string line;
  stringstream buf;
  buf << ".ORIG x3000" << endl;

  // Process each instruction
  while (!in.eof()) {
    getline(in, line);
    line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
    if (line.size() == 0) continue;
    if (line.size() != 16) {
      cerr << "Error: invalid line " << line << "at" << filename << endl;
      return "";
    }
    if (branch_labels.find(PC) != branch_labels.end() ||
        subroutine_labels.find(PC) != subroutine_labels.end())
      is_data = false;
    PC++;
    if (is_data) {
      buf << ".FILL x" << hex << uppercase << stoi(line, nullptr, 2) << endl;
      continue;
    }
    opcode = stoi(line.substr(0, 4), nullptr, 2);
    switch (opcode) {
        /* Since the collected pieces of code do not contain all kinds of
        instructions, I leave those unused cases in blank.*/

      case 0b0001:  // ADD
        DR = stoi(line.substr(4, 3), nullptr, 2);
        SR1 = stoi(line.substr(7, 3), nullptr, 2);
        buf << "ADD R" << DR << ", R" << SR1;
        if (line[10] == '0') {
          if (line.substr(11, 2) != "00") {
            cerr << "Error: invalid line " << line << "at" << filename << endl;
            return "";
          }
          SR2 = stoi(line.substr(13, 3), nullptr, 2);
          buf << ", R" << SR2;
        } else {
          imm5 = stoi(line.substr(11, 5), nullptr, 2);
          if (line[11] == '1') imm5 = imm5 - 32;
          buf << ", #" << imm5;
        }
        buf << endl;
        break;

      case 0b0101:  // AND
        DR = stoi(line.substr(4, 3), nullptr, 2);
        SR1 = stoi(line.substr(7, 3), nullptr, 2);
        buf << "AND R" << DR << ", R" << SR1;
        if (line[10] == '0') {
          if (line.substr(11, 2) != "00") {
            cerr << "Error: invalid line " << line << "at" << filename << endl;
            return "";
          }
          SR2 = stoi(line.substr(13, 3), nullptr, 2);
          buf << ", R" << SR2;
        } else {
          imm5 = stoi(line.substr(11, 5), nullptr, 2);
          if (line[11] == '1') imm5 = imm5 - 32;
          buf << ", #" << imm5;
        }
        buf << endl;
        break;

      case 0b0000:  // BR
        buf << "BR";
        if (line[4] == '1') buf << 'n';
        if (line[5] == '1') buf << 'z';
        if (line[6] == '1') buf << 'p';
        PCoffset9 = stoi(line.substr(7, 9), nullptr, 2);
        if (line[7] == '1') PCoffset9 = PCoffset9 - 512;
        if (branch_labels.find(PC + PCoffset9) == branch_labels.end())
          branch_labels[PC + PCoffset9] =
              "BRANCH" + to_string(branch_labels.size());
        buf << ' ' << branch_labels[PC + PCoffset9] << endl;
        break;

      case 0b1100:  // JMP && RET
        if (line.substr(4, 3) != "000" || line.substr(10) != "000000") {
          cerr << "Error: invalid line " << line << "at" << filename << endl;
          return "";
        }
        BaseR = stoi(line.substr(7, 3), nullptr, 2);
        if (BaseR == 7)
          buf << "RET" << endl;
        else
          buf << "JMP R" << BaseR << endl;
        is_data = true;
        break;

      case 0b0100:  // JSR && JSRR
        if (line[4] == '1') {
          buf << "JSR";
          PCoffset11 = stoi(line.substr(5, 11), nullptr, 2);
          if (line[5] == '1') PCoffset11 = PCoffset11 - 2048;
          if (subroutine_labels.find(PC + PCoffset11) ==
              subroutine_labels.end())
            subroutine_labels[PC + PCoffset11] =
                "SUB" + to_string(subroutine_labels.size());
          buf << ' ' << subroutine_labels[PC + PCoffset11] << endl;
        } else if (line[5] == '0' && line[6] == '0') {
          // incomplete
          buf << "JSRR";
        } else {
          cerr << "Error: invalid line " << line << "at" << filename << endl;
          return "";
        }
        break;

      case 0b0010:  // LD
        DR = stoi(line.substr(4, 3), nullptr, 2);
        buf << "LD R" << DR << ", ";
        PCoffset9 = stoi(line.substr(7, 9), nullptr, 2);
        if (line[7] == '1') PCoffset9 = PCoffset9 - 512;
        if (data_labels.find(PC + PCoffset9) == data_labels.end())
          data_labels[PC + PCoffset9] = "DATA" + to_string(data_labels.size());
        buf << data_labels[PC + PCoffset9] << endl;
        break;

      case 0b1010:  // LDI
        DR = stoi(line.substr(4, 3), nullptr, 2);
        buf << "LDI R" << DR << ", ";
        PCoffset9 = stoi(line.substr(7, 9), nullptr, 2);
        if (line[7] == '1') PCoffset9 = PCoffset9 - 512;
        if (data_labels.find(PC + PCoffset9) == data_labels.end())
          data_labels[PC + PCoffset9] = "DATA" + to_string(data_labels.size());
        buf << data_labels[PC + PCoffset9] << endl;
        break;

      case 0b0110:  // LDR
        DR = stoi(line.substr(4, 3), nullptr, 2);
        BaseR = stoi(line.substr(7, 3), nullptr, 2);
        buf << "LDR R" << DR << ", R" << BaseR;
        offset6 = stoi(line.substr(11, 5), nullptr, 2);
        if (line[10] == '1') offset6 = offset6 - 64;
        buf << ", #" << offset6 << endl;
        break;

      case 0b1110:  // LEA
        DR = stoi(line.substr(4, 3), nullptr, 2);
        buf << "LEA R" << DR << ", ";
        PCoffset9 = stoi(line.substr(7, 9), nullptr, 2);
        if (line[7] == '1') PCoffset9 = PCoffset9 - 512;
        if (data_labels.find(PC + PCoffset9) == data_labels.end())
          data_labels[PC + PCoffset9] = "DATA" + to_string(data_labels.size());
        buf << data_labels[PC + PCoffset9] << endl;
        break;

      case 0b1001:  // NOT
        if (line.substr(10) != "111111") {
          cerr << "Error: invalid line " << line << "at" << filename << endl;
          return "";
        }
        DR = stoi(line.substr(4, 3), nullptr, 2);
        SR1 = stoi(line.substr(7, 3), nullptr, 2);
        buf << "NOT R" << DR << ", R" << SR1 << endl;
        break;

      case 0b1000:  // RTI
        // incomplete
        buf << "RTI" << endl;
        break;

      case 0b0011:  // ST
        DR = stoi(line.substr(4, 3), nullptr, 2);
        buf << "ST R" << DR << ", ";
        PCoffset9 = stoi(line.substr(7, 9), nullptr, 2);
        if (line[7] == '1') PCoffset9 = PCoffset9 - 512;
        if (data_labels.find(PC + PCoffset9) == data_labels.end())
          data_labels[PC + PCoffset9] = "DATA" + to_string(data_labels.size());
        buf << data_labels[PC + PCoffset9] << endl;
        break;

      case 0b1011:  // STI
        DR = stoi(line.substr(4, 3), nullptr, 2);
        buf << "STI R" << DR << ", ";
        PCoffset9 = stoi(line.substr(7, 9), nullptr, 2);
        if (line[7] == '1') PCoffset9 = PCoffset9 - 512;
        if (data_labels.find(PC + PCoffset9) == data_labels.end())
          data_labels[PC + PCoffset9] = "DATA" + to_string(data_labels.size());
        buf << data_labels[PC + PCoffset9] << endl;
        break;

      case 0b0111:  // STR
        DR = stoi(line.substr(4, 3), nullptr, 2);
        BaseR = stoi(line.substr(7, 3), nullptr, 2);
        buf << "STR R" << DR << ", R" << BaseR;
        offset6 = stoi(line.substr(11, 5), nullptr, 2);
        if (line[10] == '1') offset6 = offset6 - 64;
        buf << ", #" << offset6 << endl;
        break;

      case 0b1111:  // TRAP
        // incomplete
        if (line.substr(4, 4) != "0000") {
          cerr << "Error: invalid line " << line << "at" << filename << endl;
          return "";
        }
        trapvect8 = stoi(line.substr(8), nullptr, 2);
        switch (trapvect8) {
          case 0x20:
            buf << "GETC";
            break;
          case 0x21:
            buf << "OUT";
            break;
          case 0x22:
            buf << "PUTS";
            break;
          case 0x23:
            buf << "IN";
            break;
          case 0x24:
            buf << "PUTSP";
            break;
          case 0x25:
            buf << "HALT";
            // Treat following lines as data
            is_data = true;
            break;
          default:
            buf << "TRAP x" << hex << trapvect8;
            break;
        }
        buf << endl;
        break;

      case 0b1101:  // reserved
        buf << ".FILL x" << hex << uppercase << stoi(line, nullptr, 2) << endl;
        break;
    }
  }
  buf << ".END";

  // Output with label
  getline(buf, line);
  out << line << endl;
  PC = 0x3000;
  while (!buf.eof()) {
    getline(buf, line);
    if (branch_labels.find(PC) != branch_labels.end())
      out << branch_labels[PC] << ' ';
    if (data_labels.find(PC) != data_labels.end())
      out << data_labels[PC] << ' ';
    if (subroutine_labels.find(PC) != subroutine_labels.end())
      out << subroutine_labels[PC] << ' ';
    out << line << endl;
    PC++;
  }
  return name + ".asm";
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
  static uint32_t inst_limit = 1107;
  static lc3::sim simulator(printer, inputter, print_level);
  if (init_flag) {
    simulator.setIgnorePrivilege(ignore_privilege);
    simulator.setRunInstLimit(inst_limit);
    init_flag = false;
  }
  // Set machine state
  simulator.zeroState();
  if (!simulator.loadObjFile(filename)) {
    cerr << "Error: invalid file " << filename << endl;
    return false;
  }
  simulator.runUntilHalt();
  return simulator.readReg(0) == 0x5 && simulator.readReg(1) == 0x0 &&
         simulator.readReg(2) == 0x300f && simulator.readReg(3) == 0x0 &&
         simulator.readReg(4) == 0x0 && simulator.readReg(5) == 0x0 &&
         simulator.readReg(6) == 0x0 && simulator.readReg(7) == 0x3003;
}

int main(int argc, char* argv[]) {
  for (auto& file : generate(argv[1]))
    if (test(assemble(translate(file))))
      cout << "\n---TEST PASSED---\n"
           << file << "\n-----------------\n"
           << endl;
    else
      cout << "\n---TEST FAILED---\n"
           << file << "\n-----------------\n"
           << endl;
  return 0;
}