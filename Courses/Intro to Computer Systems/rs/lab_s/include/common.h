#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

// Boost library
#include <boost/program_options.hpp>

// Application global variables
extern bool gIsSingleStepMode;
extern bool gIsDetailedMode;
extern std::string gInputFileName;
extern std::string gRegisterStatusFileName;
extern std::string gOutputFileName;
extern int gBeginningAddress;