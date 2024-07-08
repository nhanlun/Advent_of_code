#include <iostream>

int main() {
  // std::cout << (33511524LL * 252533) % 33554393LL << '\n';
  // std::cout << (12231762LL * 252533) % 33554393LL << '\n';
  
  // 3010, 3019
  // 6027
  // 3019
  // -> 9046
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
