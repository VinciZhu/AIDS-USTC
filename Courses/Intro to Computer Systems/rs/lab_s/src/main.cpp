#include "simulator.h"

using namespace virtual_machine_nsp;
namespace po = boost::program_options;

bool gIsSingleStepMode = false;
bool gIsDetailedMode = false;
std::string gInputFileName = "input.txt";
std::string gRegisterStatusFileName = "register.txt";
std::string gOutputFileName = "";
int gBeginningAddress = 0x3000;

int main(int argc, char **argv) {
  po::options_description desc{"LC3 SIMULATOR\n\nOptions"};
  desc.add_options()
      ("help,h", "Help screen")
      ("file,f", po::value<std::string>()->default_value("input.txt"),
       "Input file")
      ("register,r", po::value<std::string>()->default_value("register.txt"),
       "Register Status")
      ("single,s", "Single Step Mode")
      ("begin,b", po::value<int>()->default_value(0x3000),
       "Begin address (0x3000)")("output,o",
                                 po::value<std::string>()->default_value(""),
                                 "Output file")("detail,d", "Detailed Mode");

  po::variables_map vm;
  store(parse_command_line(argc, argv, desc), vm);
  notify(vm);

  if (vm.count("help")) {
    std::cout << desc << std::endl;
    return 0;
  }
  if (vm.count("file")) gInputFileName = vm["file"].as<std::string>();
  if (vm.count("register"))
    gRegisterStatusFileName = vm["register"].as<std::string>();
  if (vm.count("single")) gIsSingleStepMode = true;
  if (vm.count("begin")) gBeginningAddress = vm["begin"].as<int>();
  if (vm.count("output")) gOutputFileName = vm["output"].as<std::string>();
  if (vm.count("detail")) gIsDetailedMode = true;
  
  virtual_machine_tp virtual_machine(gBeginningAddress, gInputFileName,
                                     gRegisterStatusFileName);
  int halt_flag = true;
  int time_flag = 0;
  while (halt_flag) {
    if (gIsSingleStepMode) {
      std::cout << "Press any key to continue..." << std::endl;
      std::cin.get();
    }
    halt_flag = virtual_machine.NextStep();
    ++time_flag;
    if (gIsDetailedMode) std::cout << virtual_machine.reg << std::endl;
  }
  std::cout << "registers: " << std::endl << virtual_machine.reg << std::endl;
  std::cout << "cycle: " << std::dec << time_flag << std::endl;
  return 0;
}