#include <fstream>
#include <iostream>
#include <vector>

struct Item {
  int x, y, z;
};

int main() {
  std::ifstream in("../day03.txt");
  int x, y, z;
  std::vector<Item> arr;
  while (in >> x >> y >> z) {
    arr.emplace_back(x, y, z);
  }
  auto cmp = [](int x, int y, int z) -> bool { return x + y > z; };
  int res = 0;
  for (auto &i : arr) {
    if (cmp(i.x, i.y, i.z) && cmp(i.x, i.z, i.y) && cmp(i.y, i.z, i.x)) {
      ++res;
    }
  }
  std::cout << "part1: " << res << '\n';
  std::vector<Item> arr2;
  for (int i = 0; i < arr.size(); i += 3) {
    arr2.emplace_back(arr[i].x, arr[i + 1].x, arr[i + 2].x);
    arr2.emplace_back(arr[i].y, arr[i + 1].y, arr[i + 2].y);
    arr2.emplace_back(arr[i].z, arr[i + 1].z, arr[i + 2].z);
  }
  int res2 = 0;
  for (auto &i : arr2) {
    if (cmp(i.x, i.y, i.z) && cmp(i.x, i.z, i.y) && cmp(i.y, i.z, i.x)) {
      ++res2;
    }
  }

  std::cout << "part2: " << res2 << '\n';
  return 0;
}
