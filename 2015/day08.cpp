#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

void part1() {
  std::ifstream in("../day08_input.txt");
  std::string s;
  int len1 = 0;
  int len2 = 0;
  while (std::getline(in, s)) {
    len1 += s.length();
    auto tmp = s.length() - 2;
    for (int i = 0; i < s.length();) {
      if (s[i] == '\\') {
        if (s[i + 1] == '\\') {
          tmp--;
          i += 2;
        } else if (s[i + 1] == 'x') {
          tmp -= 3;
          i += 4;
        } else {
          tmp--;
          i += 2;
        }
      } else {
        ++i;
      }
    }
    len2 += tmp;
  }
  std::cout << "out: " << len1 - len2;
}

void part2() {
  std::ifstream in("../day08_input.txt");
  std::string s;
  int len1 = 0;
  int len2 = 0;
  std::unordered_set<char> special = {'"', '\\'};
  while (std::getline(in, s)) {
    len1 += s.length();
    auto tmp = s.length();
    for (int i = 0; i < s.length(); i++) {
      if (special.contains(s[i])) {
        tmp++;
      }
    }
    len2 += tmp + 2;
  }
  std::cout << "out: " << len2 - len1;
}

int main() {
  // part1();
  part2();
  return 0;
}