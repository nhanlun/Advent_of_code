#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

auto tokenize(const std::string &s,
              const std::string &delim = " ") -> std::vector<std::string> {
  std::vector<std::string> tokens;
  boost::split(tokens, s, boost::is_any_of(delim));
  return tokens;
}

void part1(const std::vector<std::pair<std::string, std::string>> &arr,
           const std::string &origin) {
  std::set<std::string> cnt;
  for (auto &p : arr) {
    size_t pos = 0;
    std::vector<size_t> candidates;
    while (pos + p.first.size() < origin.size()) {
      pos = origin.find(p.first, pos);
      if (pos == std::string::npos) {
        break;
      }
      candidates.push_back(pos);
      pos++;
    }

    for (auto i : candidates) {
      auto tmp = origin;
      cnt.insert(tmp.replace(i, p.first.length(), p.second));
    }
  }
  std::cout << "part1: " << cnt.size() << '\n';
}

void part2(const std::vector<std::pair<std::string, std::string>> &arr,
           const std::string &origin) 
{
  std::map<std::string, int> distance;
  std::queue<std::string> q;
  q.push("e");
  distance["e"] = 
  std::cout << "part2: " << '\n';
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
  //for (auto &i : arr) {
  //  std::cout << i.first << ' ' << i.second << '\n';
  //}
  part1(arr, origin);
  return 0;
}
