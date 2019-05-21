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

inline char pattern_to_n(const bool& lu, const bool& ru, const bool& lb, const bool& rb) {
  char res = 0;
  res += lu;
  res += ru<<1;
  res += lb<<2;
  res += rb<<3;
  return res;
}

inline bool read_field() {
  return getchar_unlocked() == '#';
}

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
    rep(j, 4) {
      field[i][j] = read_field();
    }
    getchar_unlocked();
  }

  int k = 0;
  for (int i = 0; i < 4; i+=2) {
    for (int j = 0; j < 4; j+=2) {
      res[k++] = pattern_to_n(
        field[i][j],
        field[i][j + 1],
        field[i + 1][j],
        field[i + 1][j + 1]
      );
    }
  }
}

int main(int argc, char *argv[]) {
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  uint64_t iteration_count;
  readn(iteration_count);

  char initial = read_2x2_pattern();

  char evolutions[16][4];

  rep(i, 16) {
    char init = read_2x2_pattern();
    read_4x4_pattern(evolutions[init]);
  }

  // first row is after 0 iterations, second after 1... DP
  vector<int[16]> number_of_black_after_n_iterations;
  number_of_black_after_n_iterations.reserve(16);

  return 0;
}
