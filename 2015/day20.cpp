#include <fmt/format.h>
#include <functional>
#include <iostream>
#include <vector>

const int N = 10000000;
std::vector<bool> isPrime(N);
std::vector<int> base(N);

void sieve() {
  std::fill(isPrime.begin(), isPrime.end(), true);
  for (int i = 2; i < N; ++i) {
    if (isPrime[i]) {
      base[i] = i;
      for (int j = i; j < N / i; ++j) {
        if (isPrime[i * j]) {
          isPrime[i * j] = false;
          base[i * j] = i;
        }
      }
    }
  }
}

auto sigma(int x) -> long {
  if (x == 1) {
    return 1;
  }
  int cur = 0;
  long Pow = 1;
  long res = 1;
  while (x > 1) {
    if (base[x] != cur) {
      if (cur != 0) {
        res *= (Pow * cur - 1) / (cur - 1);
      }
      cur = base[x];
      Pow = 1;
    }
    x /= base[x];
    Pow *= cur;
  }
  res *= (Pow * cur - 1) / (cur - 1);
  return res * 10;
}

void part1() {
  int inp = 36000000;
  for (int i = 2; i < N; ++i) {
    auto presents = sigma(i);

    if (presents >= inp) {
      std::cout << fmt::format("part1: {} {}", i, presents) << '\n';
      return;
    }
  }
}

auto factorize(int x) -> std::vector<std::pair<long, long>> {
  std::vector<std::pair<long, long>> res;
  long cur = 0;
  long cnt = 0;
  while (x > 1) {
    if (base[x] != cur) {
      if (cur != 0) {
        res.emplace_back(cur, cnt);
      }
      cnt = 0;
      cur = base[x];
    }
    x /= base[x];
    cnt++;
  }
  res.emplace_back(cur, cnt);
  return res;
}

auto generateDivisors(const std::vector<std::pair<long, long>> &factors)
    -> std::vector<long> {
  std::vector<long> res;
  std::function<void(int, long)> generateFunc;
  generateFunc = [&factors, &res, &generateFunc](int pos, long cur) {
    if (pos == factors.size()) {
      res.push_back(cur);
      return;
    }
    long p = 1;
    for (int i = 0; i <= factors[pos].second; ++i) {
      generateFunc(pos + 1, cur * p);
      p *= factors[pos].first;
    }
  };
  generateFunc(0, 1);
  return res;
}

void part2() {
  int inp = 36000000;
  for (int i = 2; i < N; ++i) {
    auto factors = factorize(i);
    auto divisors = generateDivisors(factors);
    long sum = 0;
    for (auto divisor : divisors) {
      if (i / divisor > 50) {
        continue;
      }
      sum += divisor;
    }
    if (sum * 11 >= inp) {
      std::cout << fmt::format("part2: {} {}\n", i, sum);
      return;
    }
  }
}

int main() {
  sieve();
  part1();
  part2();
  return 0;
}

/*
 * let f(n) = sum of divisors of n
 * if n is prime p^k -> f(n) = p^0 + p^1 + ... + p^k = (p^(k+1) - 1) / (p - 1)
 * f(n) is multiplicative => f(n) = f(p1) * f(p2)
 */
