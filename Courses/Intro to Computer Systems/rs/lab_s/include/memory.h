#include "common.h"

namespace virtual_machine_nsp {
const int kInstructionLength = 16;

inline int16_t TranslateInstruction(std::string& line) {
  // TODO: translate hex mode
  int16_t result = 0;
  if (line.size() == kInstructionLength) {
    for (int index = 0; index < kInstructionLength; ++index) {
      result = (result << 1) | (line[index] & 1);
    }
  }
  return result;
}

const int kVirtualMachineMemorySize = 0xFFFF;

class memory_tp : public std::array<int16_t, kVirtualMachineMemorySize> {
 public:
  memory_tp() : std::array<int16_t, kVirtualMachineMemorySize>() { fill(0); }
  // Managements
  void ReadMemoryFromFile(const std::string& filename,
                          int beginning_address = 0x3000);
  int16_t GetContent(int address) const;
};

};  // namespace virtual_machine_nsp