#include <iostream>
#include <queue>

struct Player {
  int hp;
  int atk;
  int def;
  int mana;
};

struct Skill {
  int cost;
  int dame;
  int heal;
  int def;
  int turn;
  int regen;
};

struct State {
  int cost;
  int curTurn;
  Player me;
  Player boss;
  std::vector<int> trace;
  std::vector<int> turns{0, 0, 0, 0, 0};
  auto operator<(const State &other) const -> bool {
    return (cost < other.cost) ||
           (cost == other.cost && boss.hp < other.boss.hp) ||
           (cost == other.cost && me.hp > other.me.hp &&
            boss.hp == other.boss.hp);
  }
};

int main() {
  Player boss{58, 9, 0, 0};
  Player me{50, 0, 0, 500};
  std::vector<Skill> skills = {{53, 4, 0, 0, 0, 0},
                               {73, 2, 2, 0, 0, 0},
                               {113, 0, 0, 7, 6, 0},
                               {173, 3, 0, 0, 6, 0},
                               {229, 0, 0, 0, 5, 101}};
  std::priority_queue<State> q;
  State res;
  q.emplace(0, 0, me, boss);
  int limit = 1600;
  while (!q.empty()) {
    auto u = q.top();
    q.pop();
    u.me.hp--;
    if (u.me.hp <= 0) {
      continue;
    }
    for (int i = 2; i < 5; ++i) {
      if (u.turns[i]) {
        --u.turns[i];
        u.me.mana += skills[i].regen;
        u.boss.hp -= skills[i].dame;
        if (u.turns[i] == 0) {
          u.me.def -= skills[i].def;
        }
      }
    }
    if (u.boss.hp <= 0 && u.cost < limit) {
      limit = u.cost;
      res = u;
      continue;
    }
    if (u.cost > limit || u.me.hp <= 0) {
      continue;
    }
    if (u.curTurn == 0) {
      for (int i = 0; i < 5; ++i) {
        if (u.me.mana >= skills[i].cost) {
          State nextState(u);
          nextState.curTurn ^= 1;
          if (!skills[i].turn) {
            nextState.me.mana -= skills[i].cost;
            nextState.boss.hp -= skills[i].dame;
            nextState.me.hp += skills[i].heal;
            nextState.cost += skills[i].cost;
            nextState.trace.push_back(i);
          } else if (skills[i].turn && !u.turns[i]) {
            nextState.me.mana -= skills[i].cost;
            nextState.turns[i] = skills[i].turn;
            if (i == 2) {
              nextState.me.def = skills[i].def;
            }
            nextState.cost += skills[i].cost;
            nextState.trace.push_back(i);
          }
          if (nextState.cost <= limit && nextState.cost > u.cost) {
            q.emplace(nextState);
          }
        }
      }
    } else {
      State nextState(u);
      nextState.curTurn ^= 1;
      nextState.me.hp -= std::max(1, nextState.boss.atk - nextState.me.def);
      if (nextState.me.hp <= 0) {
        continue;
      }
      q.emplace(nextState);
    }
  }
  std::cout << limit << '\n';
  for (int i : res.trace) {
    std::cout << i << ' ';
  }
  std::cout << '\n';
  std::cout << res.cost << ' ' << res.me.hp << ' ' << res.boss.hp << ' '
            << res.curTurn;
  return 0;
}
/*
 * turn 0 - poison
 * 0 50 58 0 0 0 0 0
 * 173 50 58 0 0 0 6 0
 * turn 1
 * 173 50 55 0 0 0 5 0
 * 173 41 55 0 0 0 5 0
 * turn 2 - recharge
 * 173 41 52 0 0 0 4 0
 * 402 41 52 0 0 0 4 5
 * turn 3
 * 402 41 49 0 0 0 3 4
 * 402 32 49 0 0 0 3 4
 * turn 4 - shield
 * 402 32 46 0 0 0 2 3
 * 515 32 46 0 0 6 2 3
 * turn 5
 * 515 32 43 0 0 5 1 2
 * 515 30 43 0 0 5 1 2
 * turn 6 - poison
 * 515 30 40 0 0 4 0 1
 * 688 30 40 0 0 4 6 1
 * turn 7
 * 688 30 37 0 0 3 5 0
 * 688 28 37 0 0 3 5 0
 * turn 8 - recharge
 * 688 28 34 0 0 2 4 0
 * 917 28 34 0 0 2 4 5
 * turn 9
 * 917 28 31 0 0 1 3 4
 * 917 26 31 0 0 1 3 4
 * turn 10 - drain
 * 917 26 28 0 0 0 2 3
 * 990 28 26 0 0 0 2 3
 * turn 11
 * 990 28 23 0 0 0 1 2
 * 990 21 23 0 0 0 1 2
 * turn 12 - poison
 * 990 21 20 0 0 0 0 1
 * 1163 21 20 0 0 0 6 1
 * turn 13
 * 1163 21 17 0 0 0 5 0
 * 1163 12 17 0 0 0 5 0
 * turn 14 - missile
 * 1163 12 14 0 0 0 4 0
 * 1216 12 10 0 0 0 4 0
 * turn 15
 * 1216 12 7 0 0 0 3 0
 * 1216 3 7 0 0 0 3 0
 * turn 16
 * 1216 3 4 0 0 0 2 0
 * 1269 3 0 0 0 0 2 0
 */
