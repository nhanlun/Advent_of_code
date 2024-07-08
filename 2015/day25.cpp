#include <iostream>

int main() {
  // 3010, 3019
  long long r, c;
  std::cin >> r >> c;
  long long tmp = r + c - 2;
  tmp = tmp * (tmp + 1) / 2;
  long long cur = 20151125;
  for (long long i = 2; i <= tmp + (r + c - 1) - r + 1; ++i) {
    cur = (cur * 252533) % 33554393;
  }
  std::cout << cur << '\n';
  return 0;
}
