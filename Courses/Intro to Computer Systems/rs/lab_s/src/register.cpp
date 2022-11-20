#include "register.h"

namespace virtual_machine_nsp {
std::ostream& operator<<(std::ostream& os, const register_tp& reg) {
  os << "R0 = " << std::dec << reg[R_R0] << ", ";
  os << "R1 = " << reg[R_R1] << ", ";
  os << "R2 = " << reg[R_R2] << ", ";
  os << "R3 = " << reg[R_R3] << std::endl;
  os << "R4 = " << reg[R_R4] << ", ";
  os << "R5 = " << reg[R_R5] << ", ";
  os << "R6 = " << reg[R_R6] << ", ";
  os << "R7 = " << reg[R_R7] << std::endl;
  os << "COND[NZP] = " << std::bitset<3>(reg[R_COND]) << std::endl;
  os << "PC = x" << std::hex << reg[R_PC] << std::endl;
  return os;
}
}  // namespace virtual_machine_nsp