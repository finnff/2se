#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

std::vector<char> readtxt(const char *filein) {
  std::ifstream file(filein, std::ios::in);
  return std::vector<char>(std::istreambuf_iterator<char>(file),
                           std::istreambuf_iterator<char>());
}

int main() {
  // 4.1:
  std::vector<char> bijbel = readtxt("the-king-james-bible.txt");

  // 4.2:
  std::cout << "Amount of chars in bible: " << bijbel.size() << '\n';

  // 4.3: // +1 because last line not counted because null char
  std::cout << "Amount of lines in bible: "
            << int(count(bijbel.begin(), bijbel.end(), '\n') + 1) << '\n';

  // 4.4: // should work with regex but idk?
  std::cout << "Amount of letters in bible: "
            << int(count_if(
                   bijbel.begin(), bijbel.end(),
                   [](char i) {
                     return strchr(
                         "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",
                         i);
                   }))
            << '\n';

  // 4.5:
  for (auto &c : bijbel) {
    c = tolower(c);
  };

  // for(auto &c : bijbel){
  //    std::cout<<c;
  //   };

  // 4.6:
  std::map<char, int> map;
  for (auto c : bijbel) {
    map[c]++;
  }
  for (auto j : map) {
    if (isalpha(j.first)) {
      std::cout << j.first << " = " << j.second << '\n';
    }
  };
}
