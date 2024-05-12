#include <Eigen/Dense>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <fstream>
#include <iostream>
#include <string>

auto tokenize(const std::string &s,
              const std::string &delim) -> std::vector<std::string> {
  std::vector<std::string> tokens;
  boost::split(tokens, s, boost::is_any_of(delim));
  return tokens;
}

int main() {
  auto filename = "../day15.txt";
  std::ifstream in(filename);
  std::string s;

  Eigen::MatrixXi matrix(5, 4);
  for (int i = 0; i < 4; ++i) {
    std::getline(in, s);
    auto tokens = tokenize(s, " ");
    for (int j = 2; j <= 10; j += 2) {
      auto t = tokenize(tokens[j], ",");
      matrix((j - 1) / 2, i) = stoi(t[0]);
    }
  }
  int res = 0;
  for (int i = 0; i <= 100; ++i) {
    for (int j = 0; j <= 100 - i; ++j) {
      for (int k = 0; k <= 100 - i - j; ++k) {
        auto l = 100 - i - j - k;
        Eigen::Vector4i vec(i, j, k, l);
        auto calc = (matrix * vec).cwiseMax(0);
        if (calc(4) == 500) {
          auto tmp = calc.segment(0, 4);
          res = std::max(res, tmp.prod());
        }
      }
    }
    std::cout << i << ' ' << res << '\n';
  }
  std::cout << res << '\n';
}

/*
 * a * x + b * x + c * x + d * x
 * a * y + b * y + c * y + d * y
 * a * z + b * z + c * z + d * z
 * a * t + b * t + c * t + d * t
 */
