#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

auto tokenize(const std::string &s,
              const std::string &delim = " ") -> std::vector<std::string> {
  std::vector<std::string> tokens;
  boost::split(tokens, s, boost::is_any_of(delim));
  return tokens;
}

void part1(const std::vector<std::string> &tokens) {
  int x = 0;
  int y = 0;
  int rr[] = {1, 0, -1, 0};
  int cc[] = {0, 1, 0, -1};
  int dir = 0;
  for (auto token : tokens) {
    if (token.back() == ',') {
      token.pop_back();
    }
    if (token[0] == 'R') {
      dir = (dir + 1) % 4;
    } else {
      dir = (dir - 1 + 4) % 4;
    }
    auto step = std::stoi(token.substr(1));
    x += step * rr[dir];
    y += step * cc[dir];
  }
  std::cout << "part 1: " << abs(x) + abs(y) << '\n';
}

void part2(const std::vector<std::string> &tokens) {
  int x = 0;
  int y = 0;
  int rr[] = {1, 0, -1, 0};
  int cc[] = {0, 1, 0, -1};
  int dir = 0;
  std::set<std::pair<int, int>> visited;
  visited.emplace(0, 0);
  for (auto token : tokens) {
    if (token.back() == ',') {
      token.pop_back();
    }
    if (token[0] == 'R') {
      dir = (dir + 1) % 4;
    } else {
      dir = (dir - 1 + 4) % 4;
    }
    auto step = std::stoi(token.substr(1));
    for (int i = 0; i < step; ++i) {
      x += rr[dir];
      y += cc[dir];
      if (visited.contains({x, y})) {
        std::cout << "part 2: " << abs(x) + abs(y) << '\n';
        return;
      }
      visited.emplace(x, y);
    }
  }
}

int main() {
  std::ifstream in("../day01.txt");
  std::string input;
  std::getline(in, input);
  auto tokens = tokenize(input);
  part1(tokens);
  part2(tokens);
  return 0;
}
