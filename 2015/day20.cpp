#include <iostream>
#include <vector>

const int N = 100000;
std::vector<bool> isPrime(N);
std::vector<int> base(N);
std::vector<int> pow(N);

void sieve() {
  std::fill(isPrime.begin(), isPrime.end(), true);
  for (int i = 2; i < N; ++i) {
    if (isPrime[i]) {
      for (int j = i; j < N / i; ++j) {
        isPrime[i * j] = false;
        base[i * j] = i;
        pow[i * j] = pow[j] + 1;
      }
    }
  }
}

int main() {
  sieve();
  for (int i = 2; i <= 10; ++i) {
    std::cout << isPrime[i] << ' ' << base[i] << ' ' << pow[i] << '\n';
  }
  return 0;
}

/*
 * let f(n) = sum of divisors of n
 * if n is prime p^k -> f(n) = p^0 + p^1 + ... + p^k = (p^(k+1) - 1) / (p - 1)
 */
