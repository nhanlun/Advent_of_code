#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

int f[1000];
std::vector<int> trace[1000];

int main() {
  std::vector<int> weights = {1,  3,  5,  11,  13,  17,  19,  23, 29, 31,
                              37, 41, 43, 47,  53,  59,  67,  71, 73, 79,
                              83, 89, 97, 101, 103, 107, 109, 113};
  std::fill(f, f + 1000, 1e9);
  f[0] = 0;
  for (int i : weights) {
    for (int j = 600; j >= 0; --j) {
      if (f[j + i] > f[j] + 1) {
        f[j + i] = f[j] + 1;
        trace[j + i].clear();
        trace[j + i].push_back(i);
      } else if (f[j + i] == f[j] + 1) {
        trace[j + i].push_back(i);
      }
    }
  }
  std::function<void(int, int, std::vector<int>)> dfs;
  long long res = 1e18;
  dfs = [&](int cur, int level, std::vector<int> vals) {
    if (cur == 0) {
      long long prod = 1;
      for (int i : vals) {
        prod *= i;
      }
      if (prod < res) {
        res = prod;
        for (int i : vals) {
          std::cout << i << ' ';
        }
        std::cout << '\n';
      }
      return;
    }
    for (int i : trace[cur]) {
      if (std::find(vals.begin(), vals.end(), i) == vals.end()) {
        vals.push_back(i);
        dfs(cur - i, level + 1, vals);
        vals.pop_back();
      }
    }
  };
  dfs(381, 0, {});
  std::cout << res << '\n';
  std::cout << '\n';
  return 0;
}
