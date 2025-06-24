
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Info {
  std::string name;
  int speed;
  int speedDuration;
  int restDuration;
};

auto readInp() -> std::vector<Info> {
  std::ifstream in("../day14_input.txt");
  std::string s;
  std::vector<Info> candidates;
  while (std::getline(in, s)) {
    std::vector<std::string> tokens;
    boost::split(tokens, s, boost::is_any_of(" "));
    candidates.emplace_back(tokens[0], std::stoi(tokens[3]),
                            std::stoi(tokens[6]), std::stoi(tokens[13]));
  }
  return candidates;
}

auto cal(const Info &info, int t) -> int {
  auto tmp = (info.speedDuration + info.restDuration);
  auto cnt = t / tmp;
  auto rem = t % tmp;
  auto res = info.speed * cnt * info.speedDuration;
  res += std::min(rem, info.speedDuration) * info.speed;
  return res;
};

void part1(const std::vector<Info> &candidates, int totalTime) {
  int res = 0;
  for (const auto &candidate : candidates) {
    res = std::max(res, cal(candidate, totalTime));
  }
  std::cout << res << '\n';
}

void part2(const std::vector<Info> &candidates, int totalTime) {
  std::vector<int> cur, score;
  cur.assign(candidates.size(), 0);
  score.assign(candidates.size(), 0);
  for (int t = 1; t <= totalTime; ++t) {
    int Max = 0;
    for (int i = 0; i < candidates.size(); ++i) {
      cur[i] = cal(candidates[i], t);
      Max = std::max(Max, cur[i]);
    }
    for (int i = 0; i < candidates.size(); ++i) {
      if (cur[i] == Max) {
        score[i]++;
      }
    }
  }
  std::cout << *std::max_element(score.begin(), score.end());
}

int main() {
  auto candidates = readInp();
  part1(candidates, 2503);
  part2(candidates, 2503);

  return 0;
}