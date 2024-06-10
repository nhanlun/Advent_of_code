#include <fstream>
#include <iostream>
#include <string>
#include <vector>

auto getDirection(char c) -> int {
  switch (c) {
  case 'U':
    return 0;
  case 'D':
    return 1;
  case 'R':
    return 2;
  default:
    return 3;
  }
}

void part1(const std::vector<std::string> &inp) {
  std::vector<std::vector<int>> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int x = 1;
  int y = 1;
  int rr[] = {0, 0, 1, -1};
  int cc[] = {-1, 1, 0, 0};
  std::string res;
  for (const auto &s : inp) {
    for (auto c : s) {
      auto dir = getDirection(c);
      x += rr[dir];
      y += cc[dir];
      if (x < 0) {
        x = 0;
      } else if (x > 2) {
        x = 2;
      }
      if (y < 0) {
        y = 0;
      } else if (y > 2) {
        y = 2;
      }
    }
    res += std::to_string(a[y][x]);
  }
  std::cout << "part 1: " << res << '\n';
}

void part2(const std::vector<std::string> &inp) {
  std::vector<std::string> a = {"1 4 9", " 3 8 ", "2 7 C", " 6 B ", "5 A D"};
  int x = 0;
  int y = 4;
  int rr[] = {-1, 1, 1, -1};
  int cc[] = {-1, 1, -1, 1};
  std::string res;
  for (const auto &s : inp) {
    for (auto c : s) {
      auto dir = getDirection(c);
      x += rr[dir];
      y += cc[dir];
      if (x < 0 || y < 0 || x > 4 || y > 4) {
        x -= rr[dir];
        y -= cc[dir];
      }
    }
    res += a[y][x];
  }
  std::cout << "part 2: " << res << '\n';
}

int main() {
  std::ifstream in("../day02.txt");
  std::string s;
  std::vector<std::string> inp;
  while (std::getline(in, s)) {
    inp.push_back(s);
  }

  part1(inp);
  part2(inp);
  return 0;
}
/*
 * 1 4 9
 *  3 8
 * 2 7 C
 *  6 B
 * 5 A D
 */
