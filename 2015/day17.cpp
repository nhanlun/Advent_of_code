#include <fstream>
#include <iostream>
#include <vector>

const int N = 150;

int main() {
  std::ifstream in("../day17.txt");
  std::vector<int> arr;
  for (int x; in >> x;) {
    arr.push_back(x);
  }

  auto lim = 1 << arr.size();
  int res = 0;
  int Min = 1e9;
  for (int i = 1; i < lim; ++i) {
    int sum = 0;
    int cnt = 0;
    for (int j = 0; j < arr.size(); ++j) {
      if (i & (1 << j)) {
        sum += arr[j];
        ++cnt;
      }
    }
    if (sum == 150) {
      if (cnt < Min) {
        Min = cnt;
        res = 1;
      } else if (cnt == Min) {
        ++res;
      }
    }
  }
  std::cout << res << '\n';
  return 0;
}
