#include <algorithm>
#include <fmt/format.h>
#include <iostream>
#include <vector>

struct Item {
  int cost;
  int dame;
  int armor;
};

struct Player {
  int hp;
  int dame;
  int armor;

  auto operator+=(const Item &item) -> Player & {
    dame += item.dame;
    armor += item.armor;
    return *this;
  }
};

auto winable(const Player &me, const Player &boss) -> bool {
  int myDame = std::max(1, me.dame - boss.armor);
  int bossDame = std::max(1, boss.dame - me.armor);
  int myNeedTurn = (boss.hp + myDame - 1) / myDame;
  int bossNeedTurn = (me.hp + bossDame - 1) / bossDame;
  return myNeedTurn <= bossNeedTurn;
}

auto checkWin(const Player &me, const Player &boss,
              const std::vector<Item> &items) -> bool {
  Player tmp{me};
  for (const auto &item : items) {
    tmp += item;
  }
  return winable(tmp, boss);
}

int main() {
  std::vector<Item> weapons = {
      {8, 4, 0}, {10, 5, 0}, {25, 6, 0}, {40, 7, 0}, {74, 8, 0}};
  std::vector<Item> armors = {{13, 0, 1}, {31, 0, 2},  {53, 0, 3},
                              {75, 0, 4}, {102, 0, 5}, {0, 0, 0}};
  std::vector<Item> rings = {{25, 1, 0}, {50, 2, 0}, {100, 3, 0},
                             {20, 0, 1}, {40, 0, 2}, {80, 0, 3}};
  Player boss{100, 8, 2};
  Player me{100, 0, 0};
  int res1 = 1e9;
  int res2 = 0;
  for (const auto &weapon : weapons) {
    for (const auto &armor : armors) {
      for (int state = 0; state < (1 << 6); ++state) {
        if (__builtin_popcount(state) > 2) {
          continue;
        }
        std::vector<Item> items;
        int cost = 0;
        for (int i = 0; i < 6; ++i) {
          if ((state >> i) & 1) {
            items.push_back(rings[i]);
            cost += rings[i].cost;
          }
        }
        items.push_back(weapon);
        cost += weapon.cost;
        items.push_back(armor);
        cost += armor.cost;
        if (checkWin(me, boss, items)) {
          res1 = std::min(res1, cost);
        } else {
          res2 = std::max(res2, cost);
        }
      }
    }
  }
  std::cout << fmt::format("part1: {}\n", res1);
  std::cout << fmt::format("part2: {}\n", res2);
  return 0;
}
