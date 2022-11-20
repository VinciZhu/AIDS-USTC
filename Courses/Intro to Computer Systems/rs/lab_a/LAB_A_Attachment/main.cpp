#include "assembler.h"

using namespace std;

bool gIsDebugMode = false;
bool gIsErrorLogMode = false;
bool gIsHexMode = false;

std::pair<bool, string> getCmdOption(char **begin, char **end,
                                     const std::string &option) {
  char **itr = std::find(begin, end, option);
  return itr != end && ++itr != end ? std::make_pair(true, *itr)
                                    : std::make_pair(false, "");
}

bool cmdOptionExists(char **begin, char **end, const std::string &option) {
  return std::find(begin, end, option) != end;
}

int main(int argc, char **argv) {
  if (cmdOptionExists(argv, argv + argc, "-h")) {
    std::cout << "This is a simple assembler for LC-3." << std::endl
              << std::endl;
    std::cout << "Usage" << std::endl;
    std::cout << "./assembler [OPTION] ... [FILE] ..." << std::endl
              << std::endl;
    std::cout << "Options" << std::endl;
    std::cout << "-h : print out help information" << std::endl;
    std::cout << "-f : the path for the input file" << std::endl;
    std::cout << "-d : print out debug information" << std::endl;
    std::cout << "-e : print out error information" << std::endl;
    std::cout << "-o : the path for the output file" << std::endl;
    std::cout << "-s : hex mode" << std::endl;
    return 0;
  }

  auto input_info = getCmdOption(argv, argv + argc, "-f");
  string input_filename = input_info.first ? input_info.second : "input.txt";
  auto output_info = getCmdOption(argv, argv + argc, "-o");
  string output_filename = output_info.first ? output_info.second : "";

  if (cmdOptionExists(argv, argv + argc, "-d")) SetDebugMode(true);
  if (cmdOptionExists(argv, argv + argc, "-e")) SetErrorLogMode(true);
  if (cmdOptionExists(argv, argv + argc, "-s")) SetHexMode(true);

  auto ass = assembler();
  auto status = ass.assemble(input_filename, output_filename);

  if (gIsErrorLogMode) cout << "Status: " << std::dec << status << endl;

  return 0;
}
