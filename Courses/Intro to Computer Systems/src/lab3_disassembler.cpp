#include <algorithm>
#include <bitset>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

// Disassemble machine code
void disassemble(const string& filename, const string& out_filename) {
  ifstream in(filename);
  if (!in) {
    cerr << "Error: cannot open file " << filename << endl;
    return;
  }
  ofstream out(out_filename);
  if (!out) {
    cerr << "Error: cannot open file " << out_filename << endl;
    return;
  }

  stringstream buf;
  string line;

  // // Find .ORIG pseudo command
  // while (!in.eof() && line.size() == 0) {
  //   getline(in, line);
  //   line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
  // }
  // if (line != "0011000000000000") {
  //   cerr << "Error: cannot find .ORIG x3000 in" << filename << endl;
  //   exit(1);
  // } else
  //   buf << ".ORIG x3000" << endl;

  buf << ".ORIG x3000" << endl;

  bool is_data = false;
  uint16_t PC = 0x3000, opcode, DR, SR1, SR2, BaseR, trapvect8;
  int16_t imm5, PCoffset9, offset6;
  map<uint16_t, string> labels;
  int branch_count = 0, data_count = 0;

  // Process each instruction
  while (!in.eof()) {
    getline(in, line);
    line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
    if (line.size() == 0) continue;
    if (line.size() != 16) {
      cerr << "Error: invalid line " << line << endl;
      exit(1);
    }
    PC++;
    if (is_data) {
      buf << ".FILL x" << hex << uppercase << bitset<16>(line).to_ulong()
          << endl;
      continue;
    }
    opcode = bitset<4>(line).to_ulong();
    switch (opcode) {
      case 0b0001:  // ADD
        DR = bitset<3>(line.substr(4, 3)).to_ulong();
        SR1 = bitset<3>(line.substr(7, 3)).to_ulong();
        buf << "ADD R" << DR << ", R" << SR1;
        if (line[10] == '0') {
          SR2 = bitset<3>(line.substr(13, 3)).to_ulong();
          buf << ", R" << SR2;
        } else {
          imm5 = bitset<5>(line.substr(11, 5)).to_ulong();
          if (line[11] == '1') imm5 = imm5 - 32;
          buf << ", #" << imm5;
        }
        buf << endl;
        break;

      case 0b0101:  // AND
        DR = bitset<3>(line.substr(4, 3)).to_ulong();
        SR1 = bitset<3>(line.substr(7, 3)).to_ulong();
        buf << "AND R" << DR << ", R" << SR1;
        if (line[10] == '0') {
          SR2 = bitset<3>(line.substr(13, 3)).to_ulong();
          buf << ", R" << SR2;
        } else {
          imm5 = bitset<5>(line.substr(11, 5)).to_ulong();
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
        PCoffset9 = bitset<9>(line.substr(7, 9)).to_ulong();
        if (line[7] == '1') PCoffset9 = PCoffset9 - 512;
        if (labels.find(PC + PCoffset9) == labels.end())
          labels[PC + PCoffset9] = "BRANCH" + to_string(++branch_count);
        buf << ' ' << labels[PC + PCoffset9] << endl;
        break;

      case 0b1100:  // JMP && RET
        /* Since the collected pieces of code do not contain all kinds of
        instructions, I leave those unused cases in blank.*/
        buf << "JMP" << endl;
        break;

      case 0b0100:  // JSR && JSRR
        // incomplete
        buf << "JSR" << endl;
        break;

      case 0b0010:  // LD
        DR = bitset<3>(line.substr(4, 3)).to_ulong();
        buf << "LD R" << DR << ", ";
        PCoffset9 = bitset<9>(line.substr(7, 9)).to_ulong();
        if (line[7] == '1') PCoffset9 = PCoffset9 - 512;
        if (labels.find(PC + PCoffset9) == labels.end())
          labels[PC + PCoffset9] = "DATA" + to_string(++data_count);
        buf << labels[PC + PCoffset9] << endl;
        break;

      case 0b1010:  // LDI
        DR = bitset<3>(line.substr(4, 3)).to_ulong();
        buf << "LDI R" << DR << ", ";
        PCoffset9 = bitset<9>(line.substr(7, 9)).to_ulong();
        if (line[7] == '1') PCoffset9 = PCoffset9 - 512;
        if (labels.find(PC + PCoffset9) == labels.end())
          labels[PC + PCoffset9] = "DATA" + to_string(++data_count);
        buf << labels[PC + PCoffset9] << endl;
        break;

      case 0b0110:  // LDR
        DR = bitset<3>(line.substr(4, 3)).to_ulong();
        BaseR = bitset<3>(line.substr(7, 3)).to_ulong();
        buf << "AND R" << DR << ", R" << BaseR;
        offset6 = bitset<5>(line.substr(11, 5)).to_ulong();
        if (line[10] == '1') offset6 = offset6 - 64;
        buf << ", #" << offset6 << endl;
        break;

      case 0b1110:  // LEA
        DR = bitset<3>(line.substr(4, 3)).to_ulong();
        buf << "LEA R" << DR << ", ";
        PCoffset9 = bitset<9>(line.substr(7, 9)).to_ulong();
        if (line[7] == '1') PCoffset9 = PCoffset9 - 512;
        if (labels.find(PC + PCoffset9) == labels.end())
          labels[PC + PCoffset9] = "DATA" + to_string(++data_count);
        buf << labels[PC + PCoffset9] << endl;
        break;

      case 0b1001:  // NOT
        if (line.substr(10) != "111111") {
          cerr << "Error: invalid line " << line << endl;
          return;
        }
        DR = bitset<3>(line.substr(4, 3)).to_ulong();
        SR1 = bitset<3>(line.substr(7, 3)).to_ulong();
        buf << "NOT R" << DR << ", R" << SR1 << endl;
        break;

      case 0b1000:  // RTI
        // incomplete
        buf << "RTI" << endl;
        break;

      case 0b0011:  // ST
        DR = bitset<3>(line.substr(4, 3)).to_ulong();
        buf << "ST R" << DR << ", ";
        PCoffset9 = bitset<9>(line.substr(7, 9)).to_ulong();
        if (line[7] == '1') PCoffset9 = PCoffset9 - 512;
        if (labels.find(PC + PCoffset9) == labels.end())
          labels[PC + PCoffset9] = "DATA" + to_string(++data_count);
        buf << labels[PC + PCoffset9] << endl;
        break;

      case 0b1011:  // STI
        DR = bitset<3>(line.substr(4, 3)).to_ulong();
        buf << "STI R" << DR << ", ";
        PCoffset9 = bitset<9>(line.substr(7, 9)).to_ulong();
        if (line[7] == '1') PCoffset9 = PCoffset9 - 512;
        if (labels.find(PC + PCoffset9) == labels.end())
          labels[PC + PCoffset9] = "DATA" + to_string(++data_count);
        buf << labels[PC + PCoffset9] << endl;
        break;

      case 0b0111:  // STR
        DR = bitset<3>(line.substr(4, 3)).to_ulong();
        BaseR = bitset<3>(line.substr(7, 3)).to_ulong();
        buf << "STR R" << DR << ", R" << BaseR;
        offset6 = bitset<5>(line.substr(11, 5)).to_ulong();
        if (line[10] == '1') offset6 = offset6 - 64;
        buf << ", #" << offset6 << endl;
        break;

      case 0b1111:  // TRAP
        // incomplete
        trapvect8 = bitset<8>(line.substr(8)).to_ulong();
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
        buf << ".FILL x" << hex << uppercase << bitset<16>(line).to_ulong()
            << endl;
        break;
    }
  }
  buf << ".END";
  in.close();

  // Output with label
  getline(buf, line);
  out << line << endl;
  PC = 0x3000;
  while (!buf.eof()) {
    getline(buf, line);
    if (labels.find(PC) != labels.end()) out << labels[PC] << ' ';
    out << line << endl;
    PC++;
  }
  out.close();
}

// Main
int main(int argc, char* argv[]) {
  if (argc != 2) return 0;
  string filename(argv[1]);
  auto p = filename.find_last_of('.');
  string name = p == string::npos ? filename : filename.substr(0, p);
  string out_filename(name + ".asm");
  disassemble(filename, out_filename);
  return 0;
}