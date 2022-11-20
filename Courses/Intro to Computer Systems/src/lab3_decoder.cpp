#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

void decode(const string& filename, const string& out_filename) {
  // Hash Table for the inverse mapping
  static const unordered_multimap<uint16_t, uint16_t> f = {
      {1, 0},    {1, 1},    {2, 2},    {2, 64},   {4, 3},    {6, 4},
      {6, 93},   {10, 5},   {18, 6},   {22, 43},  {30, 7},   {34, 36},
      {50, 8},   {50, 62},  {54, 23},  {66, 72},  {70, 53},  {82, 66},
      {86, 9},   {86, 67},  {98, 44},  {102, 65}, {118, 47}, {130, 80},
      {146, 10}, {150, 91}, {162, 52}, {166, 25}, {178, 14}, {178, 78},
      {182, 71}, {194, 88}, {210, 82}, {226, 60}, {242, 22}, {246, 11},
      {246, 95}, {258, 96}, {262, 61}, {274, 26}, {290, 68}, {294, 73},
      {306, 94}, {326, 21}, {338, 98}, {342, 35}, {354, 76}, {358, 33},
      {370, 38}, {386, 16}, {402, 42}, {406, 59}, {418, 12}, {418, 84},
      {438, 39}, {454, 69}, {470, 19}, {470, 83}, {482, 92}, {486, 81},
      {498, 54}, {502, 63}, {518, 29}, {530, 58}, {550, 41}, {566, 87},
      {626, 70}, {646, 77}, {658, 74}, {662, 27}, {678, 89}, {706, 24},
      {710, 13}, {710, 37}, {722, 18}, {726, 51}, {742, 17}, {742, 49},
      {754, 86}, {758, 31}, {770, 32}, {786, 90}, {790, 75}, {818, 30},
      {822, 55}, {834, 40}, {838, 85}, {850, 34}, {854, 99}, {870, 97},
      {886, 79}, {898, 48}, {902, 45}, {930, 20}, {934, 57}, {946, 46},
      {962, 56}, {978, 50}, {994, 28}, {1014, 15}};
  ifstream in(filename);
  if (!in) {
    cerr << "Error: cannot open file " << filename << endl;
    return;
  }
  ofstream out(out_filename, ios::app);
  if (!out) {
    cerr << "Error: cannot open file " << out_filename << endl;
    return;
  }
  vector<string> lines;
  while (!in.eof()) {
    string line;
    getline(in, line);
    line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
    if (line.empty()) continue;
    lines.push_back(line);
  }
  int n = lines.size();
  string id = "PB";
  for (int i = 4; i > 0; i--) {
    auto range = f.equal_range(stoi(lines[n - i], nullptr, 2));
    // The first segment in a student number
    if (i == 4)
      while (range.first != range.second &&
             (range.first->second < 17 || range.first->second > 21))
        range.first++;
    if (range.first == range.second) {
      // Caused by invalid format
      id = "PB????????";
      break;
    } else if (distance(range.first, range.second) > 1)
      // If there are more than one possible values
      id += "??";
    else {
      if (range.first->second < 10) id += '0';
      id += to_string(range.first->second);
    }
  }
  out << "student number: " << id << endl;
}

int main(int argc, char* argv[]) {
  if (argc != 2) return 0;
  string filename(argv[1]);
  auto p = filename.find_last_of('.');
  string name = p == string::npos ? filename : filename.substr(0, p);
  string out_filename(name + ".out");
  decode(filename, out_filename);
  return 0;
}