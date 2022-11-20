#include "simulator.h"

namespace virtual_machine_nsp {
template <typename T, unsigned B>
inline T SignExtend(const T x) {
  return x >> (B - 1) ? x | ~((1 << B) - 1) : x;
}

void virtual_machine_tp::UpdateCondRegister(int regname) {
  reg[R_COND] = 0;
  reg[R_COND] |= reg[regname] > 0;
  reg[R_COND] |= (reg[regname] == 0) << 1;
  reg[R_COND] |= (reg[regname] < 0) << 2;
}

void virtual_machine_tp::VM_ADD(int16_t inst) {
  if (gIsDetailedMode) std::cout << "ADD" << std::endl;
  int dr = (inst >> 9) & 0x7;
  int sr1 = (inst >> 6) & 0x7;
  if (inst & 0x20) {
    int16_t imm = SignExtend<int16_t, 5>(inst & 0x1F);
    reg[dr] = reg[sr1] + imm;
  } else {
    int sr2 = inst & 0x7;
    reg[dr] = reg[sr1] + reg[sr2];
  }
  UpdateCondRegister(dr);
}

void virtual_machine_tp::VM_AND(int16_t inst) {
  if (gIsDetailedMode) std::cout << "AND" << std::endl;
  int dr = (inst >> 9) & 0x7;
  int sr1 = (inst >> 6) & 0x7;
  if (inst & 0x20) {
    int16_t imm = SignExtend<int16_t, 5>(inst & 0x1F);
    reg[dr] = reg[sr1] & imm;
  } else {
    int sr2 = inst & 0x7;
    reg[dr] = reg[sr1] & reg[sr2];
  }
  UpdateCondRegister(dr);
}

void virtual_machine_tp::VM_BR(int16_t inst) {
  int16_t pc_offset = SignExtend<int16_t, 9>(inst & 0x1FF);
  int16_t cond_flag = (inst >> 9) & 0x7;
  if (gIsDetailedMode)
    std::cout << "BR x" << std::hex << reg[R_PC] << " -> x"
              << reg[R_PC] + pc_offset << std::endl;
  if (cond_flag & reg[R_COND]) reg[R_PC] += pc_offset;
}

void virtual_machine_tp::VM_JMP(int16_t inst) {
  int16_t baser = (inst >> 6) & 0x7;
  if (gIsDetailedMode)
    std::cout << "JMP x" << std::hex << reg[R_PC] << " -> x" << reg[baser]
              << std::endl;
  reg[R_PC] = reg[baser];
}

void virtual_machine_tp::VM_JSR(int16_t inst) {
  if (inst & 0x8FF) {
    int16_t pc_offset = SignExtend<int16_t, 11>(inst & 0x7FF);
    reg[R_R7] = reg[R_PC];
    reg[R_PC] += pc_offset;
    if (gIsDetailedMode)
      std::cout << "JSR x" << std::hex << reg[R_PC] << " -> x"
                << reg[R_PC] + pc_offset << std::endl;
  } else {
    int16_t baser = (inst >> 6) & 0x7;
    reg[R_R7] = reg[R_PC];
    reg[R_PC] = reg[baser];
    if (gIsDetailedMode)
      std::cout << "JSRR x" << std::hex << reg[R_PC] << " -> x" << reg[baser]
                << std::endl;
  }
}

void virtual_machine_tp::VM_LD(int16_t inst) {
  if (gIsDetailedMode) std::cout << "LD" << std::endl;
  int16_t dr = (inst >> 9) & 0x7;
  int16_t pc_offset = SignExtend<int16_t, 9>(inst & 0x1FF);
  reg[dr] = mem[reg[R_PC] + pc_offset];
  UpdateCondRegister(dr);
}

void virtual_machine_tp::VM_LDI(int16_t inst) {
  if (gIsDetailedMode) std::cout << "LDI" << std::endl;
  int16_t dr = (inst >> 9) & 0x7;
  int16_t pc_offset = SignExtend<int16_t, 9>(inst & 0x1FF);
  reg[dr] = mem[mem[reg[R_PC] + pc_offset]];
  UpdateCondRegister(dr);
}

void virtual_machine_tp::VM_LDR(int16_t inst) {
  if (gIsDetailedMode) std::cout << "LDR" << std::endl;
  int16_t dr = (inst >> 9) & 0x7;
  int16_t baser = (inst >> 6) & 0x7;
  int16_t pc_offset = SignExtend<int16_t, 6>(inst & 0x3F);
  reg[dr] = mem[reg[baser] + pc_offset];
  UpdateCondRegister(dr);
}

void virtual_machine_tp::VM_LEA(int16_t inst) {
  if (gIsDetailedMode) std::cout << "LEA" << std::endl;
  int16_t dr = (inst >> 9) & 0x7;
  int16_t pc_offset = SignExtend<int16_t, 9>(inst & 0x1FF);
  reg[dr] = reg[R_PC] + pc_offset;
  UpdateCondRegister(dr);
}

void virtual_machine_tp::VM_NOT(int16_t inst) {
  if (gIsDetailedMode) std::cout << "NOT" << std::endl;
  int dr = (inst >> 9) & 0x7;
  int sr = (inst >> 6) & 0x7;
  reg[dr] = ~reg[sr];
  UpdateCondRegister(dr);
}

void virtual_machine_tp::VM_RTI(int16_t inst) {
  ;  // PASS
}

void virtual_machine_tp::VM_ST(int16_t inst) {
  if (gIsDetailedMode) std::cout << "ST" << std::endl;
  int16_t sr = (inst >> 9) & 0x7;
  int16_t pc_offset = SignExtend<int16_t, 9>(inst & 0x1FF);
  mem[reg[R_PC] + pc_offset] = reg[sr];
}

void virtual_machine_tp::VM_STI(int16_t inst) {
  if (gIsDetailedMode) std::cout << "STI" << std::endl;
  int16_t sr = (inst >> 9) & 0x7;
  int16_t pc_offset = SignExtend<int16_t, 9>(inst & 0x1FF);
  mem[mem[reg[R_PC] + pc_offset]] = reg[sr];
}

void virtual_machine_tp::VM_STR(int16_t inst) {
  if (gIsDetailedMode) std::cout << "STR" << std::endl;
  int16_t sr = (inst >> 9) & 0x7;
  int16_t baser = (inst >> 6) & 0x7;
  int16_t pc_offset = SignExtend<int16_t, 6>(inst & 0x3F);
  mem[reg[baser] + pc_offset] = reg[sr];
}

void virtual_machine_tp::VM_TRAP(int16_t inst) {
  int trapnum = inst & 0xFF;
  switch (trapnum) {
    case T_HALT:
      if (gIsDetailedMode) std::cout << "HALT" << std::endl;
      reg[R_PC] = 0;
      break;
    default:
      break;
  }
}

virtual_machine_tp::virtual_machine_tp(const int16_t address,
                                       const std::string &memfile,
                                       const std::string &regfile) {
  // Read memory
  if (memfile != "") {
    mem.ReadMemoryFromFile(memfile);
  }

  // Read registers
  std::ifstream input_file;
  input_file.open(regfile);
  if (input_file.is_open()) {
    int line_count = std::count(std::istreambuf_iterator<char>(input_file),
                                std::istreambuf_iterator<char>(), '\n');
    input_file.close();
    input_file.open(regfile);
    if (line_count >= 8)
      for (int index = R_R0; index <= R_R7; ++index) input_file >> reg[index];
    else
      for (int index = R_R0; index <= R_R7; ++index) reg[index] = 0;
    input_file.close();
  } else {
    for (int index = R_R0; index <= R_R7; ++index) reg[index] = 0;
  }

  // Set address
  reg[R_PC] = address;
  reg[R_COND] = 0;
}

void virtual_machine_tp::SetReg(const register_tp &new_reg) { reg = new_reg; }

int16_t virtual_machine_tp::NextStep() {
  int16_t current_instruct = mem[reg[R_PC]++];
  int opcode = (current_instruct >> 12) & 15;
  switch (opcode) {
    case O_ADD:
      VM_ADD(current_instruct);
      break;
    case O_AND:
      VM_AND(current_instruct);
      break;
    case O_BR:
      VM_BR(current_instruct);
      break;
    case O_JMP:
      VM_JMP(current_instruct);
      break;
    case O_JSR:
      VM_JSR(current_instruct);
      break;
    case O_LD:
      VM_LD(current_instruct);
      break;
    case O_LDI:
      VM_LDI(current_instruct);
      break;
    case O_LDR:
      VM_LDR(current_instruct);
      break;
    case O_LEA:
      VM_LEA(current_instruct);
      break;
    case O_NOT:
      VM_NOT(current_instruct);
      break;
    case O_RTI:
      VM_RTI(current_instruct);
      break;
    case O_ST:
      VM_ST(current_instruct);
      break;
    case O_STI:
      VM_STI(current_instruct);
      break;
    case O_STR:
      VM_STR(current_instruct);
      break;
    case O_TRAP:
      VM_TRAP(current_instruct);
      break;
    default:
      break;
  }
  if (current_instruct == 0) return 0;
  return reg[R_PC];
}

}  // namespace virtual_machine_nsp