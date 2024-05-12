#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

auto tokenize(const std::string &s,
              const std::string &delim = " ") -> std::vector<std::string> {
  std::vector<std::string> tokens;
  boost::split(tokens, s, boost::is_any_of(delim));
  return tokens;
}

auto check(const std::map<std::string, int> &a,
           const std::map<std::string, int> &b) -> bool {
  for (auto &i : b) {
    if (!a.contains(i.first)) {
      return false;
    }
    if (i.first == "cats:" || i.first == "trees:") {
      if (i.second <= a.at(i.first)) {
        return false;
      }
      continue;
    }
    if (i.first == "pomeranians:" || i.first == "goldfish:") {
      if (i.second >= a.at(i.first)) {
        return false;
      }
      continue;
    }
    if (a.at(i.first) != i.second) {
      return false;
    }
  }
  return true;
}

int main() {
  std::string target = R"(children: 3
cats: 7
samoyeds: 2
pomeranians: 3
akitas: 0
vizslas: 0
goldfish: 5
trees: 3
cars: 2
perfumes: 1)";
  std::stringstream ss(target);
  std::map<std::string, int> m;

  std::string s;
  while (std::getline(ss, s)) {
    auto tokens = tokenize(s);
    m[tokens[0]] = std::stoi(tokens[1]);
  }
  std::ifstream in("../day16.txt");
  const int N = 500;
  for (int i = 0; i < N; ++i) {
    std::getline(in, s);
    auto tokens = tokenize(s);
    std::map<std::string, int> cur;
    for (int j = 2; j < tokens.size(); j += 2) {
      auto tmp = tokenize(tokens[j + 1], ",");
      cur[tokens[j]] = std::stoi(tmp[0]);
    }
    if (check(m, cur)) {
      std::cout << i + 1 << ' ' << s << '\n';
    }
  }

  return 0;
}
