#include "memory.h"

#include "common.h"

namespace virtual_machine_nsp {
void memory_tp::ReadMemoryFromFile(const std::string &filename,
                                   int beginning_address) {
  std::ifstream ifs(filename);
  int address = beginning_address;
  std::string line;
  while (address <= kVirtualMachineMemorySize && std::getline(ifs, line)) {
    (*this)[address++] = std::stoi(line, nullptr, 2);
  }
}

int16_t memory_tp::GetContent(int address) const { return (*this)[address]; }
};  // namespace virtual_machine_nsp
