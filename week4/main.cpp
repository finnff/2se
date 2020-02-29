#include <boost/range/adaptor/reversed.hpp> //niet stl:D
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

std::vector<char> readtxt(const char *filein) { // 4.1
  std::ifstream file(filein, std::ios::in);
  return std::vector<char>(std::istreambuf_iterator<char>(file),
                           std::istreambuf_iterator<char>());
}

template <typename A, typename B> // 4.8
std::multimap<B, A> flip_map(std::map<A, B> &src) {
  std::multimap<B, A> cpy;
  for (typename std::map<A, B>::const_iterator it = src.begin();
       it != src.end(); ++it)
    cpy.insert(std::pair<B, A>(it->second, it->first));
  return cpy;
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

  // 4.6/4.7:
  std::cout << '\n' << "How often each letter is used: " << '\n';
  std::map<char, int> map;
  for (auto c : bijbel) {
    map[c]++;
  }
  for (auto j : map) {
    if (isalpha(j.first)) {
      std::cout << j.first << " = " << j.second << '\n';
    }
  };

  // 4.7:
  std::cout<<"sorted by amount used: "<<'\n';

  std::multimap<int, char> sortedchar = flip_map(map);
  for (auto &k : boost::adaptors::reverse(sortedchar)) {
    if (isalpha(k.second)){
      std::cout << k.first << " = " << k.second << '\n';
  }
  }

  // 4.8:
  std::cout << '\n' << "10 most common words in Bible: " << '\n';
  std::map<std::string, int> strmap;
  std::string word{""};
  for (auto c : bijbel) {
    if (isalpha(c)) {
      word += c;
    } else if (word.length() > 0) {
      strmap[word]++;
      word = "";
    }
  }
  std::multimap<int, std::string> sorted = flip_map(strmap);
  int amount = 0;
  for (auto &k : boost::adaptors::reverse(
           sorted)) { /// zou ook met reverse iterators kunnen en niet ranged
                      /// based, maar dit is korter?
    std::cout << k.first << " = " << k.second << '\n';
    amount++;
    if (amount > 9) {
      break;
    }
  }
}
