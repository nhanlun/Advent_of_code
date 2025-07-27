#include <fstream>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>

#include <boost/algorithm/string.hpp>

using namespace std;

auto count1(const string &s) -> int {
  int pos = 0;
  auto check = [](const string &s) {
    for (int i = 0; i + 3 < s.length(); ++i) {
      if ((s[i] == s[i + 3]) && (s[i + 1] == s[i + 2]) && (s[i] != s[i + 1])) {
        return true;
      }
    }
    return false;
  };
  bool inner = false;
  bool atLeast = false;
  while (pos < s.length()) {
    if (!inner) {
      string tmp;
      for (; pos < s.length() && s[pos] != '['; ++pos) {
        tmp += s[pos];
      }
      if (check(tmp)) {
        atLeast = true;
      }
      inner = true;
    } else {
      string tmp;
      for (; pos < s.length() && s[pos] != ']'; ++pos) {
        tmp += s[pos];
      }
      if (check(tmp)) {
        return false;
      }
      inner = false;
    }
  }
  return atLeast;
}

auto count2(const string &s) -> int {
  int pos = 0;
  auto build = [](const string &s, set<string> &se) {
    for (int i = 0; i + 2 < s.length(); ++i) {
      if ((s[i] == s[i + 2]) && (s[i] != s[i + 1])) {
        string tmp;
        tmp += s[i];
        tmp += s[i + 1];
        se.insert(tmp);
      }
    }
  };
  bool inner = false;
  set<string> s1;
  set<string> s2;
  while (pos < s.length()) {
    if (!inner) {
      string tmp;
      for (; pos < s.length() && s[pos] != '['; ++pos) {
        tmp += s[pos];
      }
      build(tmp, s1);
      inner = true;
    } else {
      string tmp;
      for (; pos < s.length() && s[pos] != ']'; ++pos) {
        tmp += s[pos];
      }
      build(tmp, s2);
      inner = false;
    }
  }
  for (const auto &i : s1) {
    string tmp{};
    tmp += i[1];
    tmp += i[0];
    if (s2.contains(tmp)) {
      return true;
    }
  }
  return false;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    throw runtime_error("missing input");
  }
  ifstream in(argv[1]);
  string s;
  int res1 = 0;
  int res2 = 0;
  while (getline(in, s)) {
    res1 += count1(s);
    res2 += count2(s);
  }
  cout << res1 << '\n';
  cout << res2 << '\n';
  return 0;
}