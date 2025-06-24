#include <algorithm>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <unordered_map>

int main() {
  std::ifstream in("../day09_input.txt");
  std::string s;
  std::unordered_map<std::string, int> nameMap;
  int cnt = 0;
  std::vector<std::vector<int>> adj;
  adj.assign(100, std::vector<int>(100));
  while (std::getline(in, s)) {
    std::vector<std::string> tokens;
    boost::split(tokens, s, boost::is_any_of(" "));
    if (!nameMap.contains(tokens[0])) {
      nameMap[tokens[0]] = cnt++;
    }
    if (!nameMap.contains(tokens[2])) {
      nameMap[tokens[2]] = cnt++;
    }
    int u = nameMap[tokens[0]];
    int v = nameMap[tokens[2]];
    int x = std::stoi(tokens.back());
    adj[u][v] = x;
    adj[v][u] = x;
  }
  auto n = nameMap.size();
  std::vector<int> id(n);
  std::iota(id.begin(), id.end(), 0);
  int res = std::numeric_limits<int>::max();
  int res2 = 0;
  do {
    int sum = 0;
    for (int i = 0; i + 1 < n; ++i) {
      sum += adj[id[i]][id[i + 1]];
    }
    res = std::min(res, sum);
    res2 = std::max(res2, sum);
  } while (std::next_permutation(id.begin(), id.end()));
  std::cout << res << '\n' << res2 << '\n';
}