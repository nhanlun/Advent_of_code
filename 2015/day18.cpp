#include <fstream>
#include <iostream>

char arr[2][105][105];
int rr[] = {0, 0, 1, -1, 1, -1, -1, 1};
int cc[] = {1, -1, 0, 0, 1, 1, -1, -1};

auto inside(int x, int y) -> bool {
  return (x >= 0 && x < 100 && y >= 0 && y < 100);
}

auto isCorner(int x, int y) -> bool {
  return (x == 0 && y == 0) || (x == 0 && y == 99) || (x == 99 && y == 0) ||
         (x == 99 && y == 99);
}

int main() {
  std::ifstream in("../day18.txt");
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      in >> arr[0][i][j];
    }
  }

  for (int cnt = 1; cnt <= 100; ++cnt) {
    int cur = (cnt + 1) % 2;
    int ne = cnt % 2;
    for (int i = 0; i < 100; ++i) {
      for (int j = 0; j < 100; ++j) {
        if (isCorner(i, j)) {
          arr[ne][i][j] = '#';
          continue;
        }
        int on = 0;
        for (int k = 0; k < 8; ++k) {
          int u = i + rr[k];
          int v = j + cc[k];
          if (inside(u, v) && arr[cur][u][v] == '#') {
            ++on;
          }
        }
        if (arr[cur][i][j] == '#') {
          if (on == 2 || on == 3) {
            arr[ne][i][j] = '#';
          } else {
            arr[ne][i][j] = '.';
          }

        } else {
          if (on == 3) {
            arr[ne][i][j] = '#';
          } else {
            arr[ne][i][j] = '.';
          }
        }
      }
    }
  }
  int res = 0;
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      if (arr[0][i][j] == '#') {
        ++res;
      }
    }
  }
  std::cout << res << '\n';
  return 0;
}
