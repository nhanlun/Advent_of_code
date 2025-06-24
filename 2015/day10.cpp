#include <iostream>
#include <string>

auto process(const std::string &s) -> std::string {
  std::string res;
  char cur = ' ';
  int cnt = 0;
  for (const auto &c : s) {
    if (c != cur) {
      if (cur != ' ') {
        res += std::to_string(cnt) + cur;
      }
      cur = c;
      cnt = 0;
    }
    cnt++;
  }
  res += std::to_string(cnt) + cur;
  return res;
}

int main() {
  std::string inp = "1321131112";
  for (int i = 0; i < 50; ++i) {
    inp = process(inp);
    // std::cerr << i << ' ' << inp << '\n';
  }
  std::cout << inp.length() << '\n';
}