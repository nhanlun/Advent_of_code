#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <fstream>
#include <iostream>
#include <map>
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
  return 0;
}
