#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <regex>

void part1() {
  std::ifstream in("../day12_input.txt");
  std::string s;
  std::regex isNum("(-|)[0-9]+");
  long res = 0;
  while (in >> s) {
    for (std::smatch sm; std::regex_search(s, sm, isNum);) {
      // std::cout << sm.str() << '\n';
      auto tmp = std::stol(sm.str());
      s = sm.suffix();
      res += tmp;
    }
  }
  std::cout << res;
}

auto getNum(const nlohmann::json &json) -> int32_t {
  int32_t res = 0;
  for (auto &[key, val] : json.items()) {
    if (val.is_string() && val.get<std::string>() == "red" &&
        !json.is_array()) {
      return 0;
    }
    if (val.is_structured()) {
      res += getNum(val);
    } else if (val.is_number()) {
      res += val.get<int32_t>();
    }
  }
  return res;
}

void part2() {
  std::ifstream in("../day12_input.txt");
  auto json = nlohmann::json::parse(in);
  std::cout << getNum(json);
}

int main() {
  // part1();
  part2();
  return 0;
}