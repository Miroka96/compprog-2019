#include <bits/stdc++.h>

////////////////////////////// Helper //////////////////////

// disable debugging for submission
//#define debug(x)    x
// print value of debug variable
#define debug(x) clog << #x << " = " << x << endl

// print a debug string
#define debugs(str) // clog << str << endl
#define rep(a, b) for (int a = 0; a < (b); ++a)
#define repd(a, b) for (int a = 0; a < (b); debug(++a))
#define all(a) (a).begin(), (a).end()

using namespace std;

////////////////////////////// I/O /////////////////////////
#define BASE 10
#define OUTPUT_LENGTH 24
#define BUFFER_SIZE 0x10000

// buffer stdin
char inputbuffer[BUFFER_SIZE];

template <typename T> inline void readn(T &x) {
  x = 0;
  bool neg = 0;
  register T c = getchar_unlocked();

  if (c == '-')
    neg = 1, c = getchar_unlocked();

  for (; c >= '0' && c <= '9'; c = getchar_unlocked())
    x = (x << 3) + (x << 1) + (c & 15);

  if (neg)
    x *= -1;
}

// create output buffer
char outputbuffer[OUTPUT_LENGTH];

template <typename T> inline void write(T n) {
  bool neg = 0;
  if (n < 0)
    n *= -1, neg = 1;

  int i = 0;
  do {
    outputbuffer[i++] = n % 10 + '0';
    n /= 10;
  } while (n);
  --i;

  if (neg)
    putchar_unlocked('-');

  while (i >= 0)
    putchar_unlocked(outputbuffer[i--]);

  putchar_unlocked('\n');
}

inline void print(const char *str) {
  for (const char *c = str; *c; c++) {
    putchar_unlocked(*c);
  }
}

////////////////////////////// Task ////////////////////////

constexpr static int mod = 998244353;

typedef uint64_t mul_t;

template <typename R = mul_t, typename T>
inline T modadd(const T &a, const T &b, const T &modulus = mod) {
  return (((R)a) + ((R)b)) % ((R)modulus);
}

template <typename R = mul_t, typename T>
inline T modmul(const T &a, const T &b, const T &modulus = mod) {
  return (((R)a) * ((R)b)) % ((R)modulus);
}

template <typename R = mul_t, typename T>
inline R modpow(T base, T exp, const T &modulus = mod) {
  base %= modulus;
  R result = 1;
  while (exp > 0) {
    if (exp & 1)
      result = modmul<R>(result, base, modulus);
    base = modmul<R>(base, base, modulus);
    exp >>= 1;
  }
  return result;
}

inline char pattern_to_n(const bool &lu, const bool &ru, const bool &lb,
                         const bool &rb) {
  char res = 0;
  res += lu;
  res += ru << 1;
  res += lb << 2;
  res += rb << 3;
  return res;
}

inline bool read_field() { return getchar_unlocked() == '#'; }

inline char read_2x2_pattern() {
  bool lu, ru, lb, rb;
  lu = read_field();
  ru = read_field();
  getchar_unlocked();
  lb = read_field();
  rb = read_field();
  getchar_unlocked();
  return pattern_to_n(lu, ru, lb, rb);
}

inline void read_4x4_pattern(char res[4]) {
  bool field[4][4];
  rep(i, 4) {
    rep(j, 4) { field[i][j] = read_field(); }
    getchar_unlocked();
  }

  int k = 0;
  for (int i = 0; i < 4; i += 2) {
    for (int j = 0; j < 4; j += 2) {
      res[k++] = pattern_to_n(field[i][j], field[i][j + 1], field[i + 1][j],
                              field[i + 1][j + 1]);
    }
  }
}

inline void modmul_layers(int posterior[16], int prior[16][16], int res[16]) {
  rep(j, 16) {
    int posterior_count = posterior[j];
    if (posterior_count == 0)
      continue;
    rep(k, 16) {
      int prior_count = prior[j][k];
      if (prior_count == 0)
        continue;
      res[k] = modadd(res[k], modmul(prior_count, posterior_count));
    }
  }
}

int main(int argc, char *argv[]) {
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  uint64_t iteration_count;
  readn(iteration_count);

  char largest_power_of_2 = 64 - __builtin_clzll(iteration_count);
  int pattern_counts[largest_power_of_2][16][16] = {};

  char initial = read_2x2_pattern();

  rep(i, 16) {
    char init = read_2x2_pattern();
    char results[4];
    read_4x4_pattern(results);
    rep(j, 4) { pattern_counts[0][init][results[j]] += 1; }
  }

  for (int iter = 1; iter < largest_power_of_2; iter++) {
    rep(i, 16) {
      modmul_layers(pattern_counts[iter-1][i], pattern_counts[iter-1], pattern_counts[iter][i]);
    }
  }

  int(&result_patterns)[16] = pattern_counts[largest_power_of_2 - 1][initial];

  for (int iter = largest_power_of_2 - 2; iter >= 0; iter--) {
    if ((iteration_count & (1L << iter)) == 0)
      continue;

    int iteration_results[16] = {};

    modmul_layers(result_patterns, pattern_counts[iter], iteration_results);

    rep(i, 16) {
      result_patterns[i] = iteration_results[i];
    }
  }

  int result = 0;

  rep(i, 16) {
    result = modadd(result, modmul(result_patterns[i], __builtin_popcount(i)));
  }

  write(result);

  return 0;
}
