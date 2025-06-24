#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

int main() {
  std::ifstream in("../day13_input.txt");
  std::string s;
  std::map<std::string, int> m;
  int cnt = 0;
  std::vector<std::vector<int>> arr;
  arr.assign(9, std::vector<int>(9));
  while (std::getline(in, s)) {
    s.pop_back();
    std::vector<std::string> tokens;
    boost::split(tokens, s, boost::is_any_of(" "));
    const auto &a = tokens[0];
    const auto &b = tokens.back();
    if (!m.contains(a)) {
      m[a] = cnt++;
    }
    if (!m.contains(b)) {
      m[b] = cnt++;
    }
    auto c = m[a];
    auto d = m[b];
    arr[c][d] = std::stoi(tokens[3]);
    if (tokens[2] == "lose") {
      arr[c][d] = -arr[c][d];
    }
  }

  std::vector<int> id(9);
  std::iota(id.begin(), id.end(), 0);
  int res = 0;
  do {
    int sum = 0;
    for (int i = 0; i < 8; ++i) {
      sum += arr[id[i]][id[i + 1]];
      sum += arr[id[i + 1]][id[i]];
    }
    sum += arr[id[0]][id[8]];
    sum += arr[id[8]][id[0]];
    res = std::max(res, sum);
  } while (std::next_permutation(id.begin(), id.end()));
  std::cout << res;
  return 0;
}