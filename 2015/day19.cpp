#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <vector>

auto tokenize(const std::string &s,
              const std::string &delim = " ") -> std::vector<std::string> {
  std::vector<std::string> tokens;
  boost::split(tokens, s, boost::is_any_of(delim));
  return tokens;
}

auto findCandidates(const std::string &origin,
                    const std::pair<std::string, std::string> &replacement)
    -> std::vector<size_t> {
  size_t pos = 0;
  std::vector<size_t> candidates;
  while (pos + replacement.first.size() <= origin.size()) {
    pos = origin.find(replacement.first, pos);
    if (pos == std::string::npos) {
      break;
    }
    candidates.push_back(pos);
    pos++;
  }

  return candidates;
}

void part1(const std::vector<std::pair<std::string, std::string>> &arr,
           const std::string &origin) {
  std::set<std::string> cnt;
  for (auto &p : arr) {
    auto candidates = findCandidates(origin, p);
    for (auto i : candidates) {
      auto tmp = origin;
      tmp.replace(i, p.first.length(), p.second);

      cnt.insert(tmp);
    }
  }
  std::cout << "part1: " << cnt.size() << '\n';
}

void part2(std::vector<std::pair<std::string, std::string>> arr,
           const std::string &origin) {
  std::map<std::string, int> distance;
  // std::queue<std::string> q;
  std::set<std::pair<int, std::string>> q;
  // q.push(origin);
  q.emplace(origin.length(), origin);
  distance[origin] = 1;
  for (auto &i : arr) {
    std::swap(i.first, i.second);
  }
  while (!q.empty()) {
    // auto u = q.front();
    auto [len, u] = *(q.begin());
    auto x = distance[u];
    std::cerr << "###### " << u << ' ' << x << '\n';
    if (u == "e") {
      std::cout << "part2: " << x << '\n';
      return;
    }
    q.erase(q.begin());
    bool flag = false;
    for (auto &p : arr) {
      auto candidates = findCandidates(u, p);
      // if (p.first == "e") {
      //   std::cerr << "##### " << p.second << ' ' << replaceResults.size()
      //             << '\n';
      // }
      for (int i : candidates) {
        auto tmp = u;
        tmp.replace(i, p.first.length(), p.second);
        if (!distance.contains(tmp)) {
          distance[tmp] = x + 1;
          // q.push(v);
          q.emplace(tmp.length(), tmp);
          flag = true;
          break;
        }
      }
      if (flag) {
        break;
      }
    }
  }
}

int main() {
  std::ifstream in("../day19.txt");
  std::string s;
  std::string origin;
  std::vector<std::pair<std::string, std::string>> arr;
  while (std::getline(in, s)) {
    if (s.empty()) {
      std::getline(in, origin);
      break;
    }
    auto tokens = tokenize(s);
    arr.emplace_back(tokens[0], tokens[2]);
  }
  part1(arr, origin);
  part2(arr, origin);
  return 0;
}
