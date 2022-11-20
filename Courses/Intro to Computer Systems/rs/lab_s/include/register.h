#include "common.h"

namespace virtual_machine_nsp {
enum RegisterName {
  R_R0,
  R_R1,
  R_R2,
  R_R3,
  R_R4,
  R_R5,
  R_R6,
  R_R7,
  R_PC,
  R_COND,
  kRegisterNumber
};

typedef std::array<int16_t, kRegisterNumber> register_tp;
std::ostream& operator<<(std::ostream& os, const register_tp& reg);
}  // namespace virtual_machine_nsp