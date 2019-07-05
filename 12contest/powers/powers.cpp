#include <bits/stdc++.h>
#include <unistd.h>

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

////////////////////// Angelika's Input ////////////////////

struct Input {
  char *buf;

  Input(size_t size) : buf((char *)malloc(size)) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.precision(10);

    char *start = buf;
    int n = 0;
    do {
      buf += n;
      n = read(STDIN_FILENO, buf, size);
    } while (n > 0);
    assert(buf <= start + size);
    buf = start;
  }

  void skip_space() {
    while (*buf <= ' ')
      buf++;
  }

  operator char() {
    skip_space();
    return *buf++;
  }

  operator bool() {
    skip_space();
    return *buf++ != '0';
  }

  operator char *() {
    skip_space();
    char *s = buf;
    while (*buf++ > ' ')
      ;
    buf[-1] = '\0';
    return s;
  }

  operator float() { return (double)*this; }

  operator double() {
    char *s = *this;
    return atof(s);
  }

  template <typename T> operator T() {
    skip_space();
    T n = 0;
    char c = *buf++;
    bool neg = c == '-';
    if (neg)
      c = *buf++;
    while (c > ' ') {
      n *= 10;
      n += c - '0';
      c = *buf++;
    }
    if (neg)
      n = -n;
    return n;
  }
};

////////////////////////////// I/O /////////////////////////
#define BASE 10
#define OUTPUT_LENGTH 24
#define BUFFER_SIZE 0x10000

// buffer stdin
char inputbuffer[BUFFER_SIZE];

template <typename T> inline void readn(T &x) {
  x = 0;
  bool neg = 0;
  register char c = getchar_unlocked();

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

}

inline void print(const char *str) {
  for (const char *c = str; *c; c++) {
    putchar_unlocked(*c);
  }
  putchar_unlocked('\n');
}

////////////////////////////// Task ////////////////////////

int main(int argc, char *argv[]) {
  // disable for Angelika's Input
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  // disable for Mirko's Input
  //auto in = Input(1 << 28);

  int games_count;
  readn(games_count);

  rep(game, games_count) {
    uint32_t n;
    char k;
    readn(n);
    readn(k);
    
    int ones = __builtin_popcount(n);
    if (ones > k) {
      print("NOT POSSIBLE");
      continue;
    }

    vector<uint32_t> powers;
    for(uint32_t i = 1u; i > 0; i = i << 1) {
      if ((n & i) > 0) {
        powers.push_back(i);
      }
    }
    int i = 0;
    for(int i = 0; i < powers.size() && powers.size() < k; i++) {
      while(powers.size() < k && powers[i] > 1) {
        powers[i] /= 2;
        powers.push_back(powers[i]);
      }
      sort(powers.begin(), powers.end());
    }
    if (powers.size() < k) {
      print("NOT POSSIBLE");
      continue;
    }
    print("POSSIBLE");
    

    bool first = true;
    for(auto power : powers) {
      if (!first) {
        putchar_unlocked(' ');
      } else {
        first = false;
      }
      write(power);
    }
    putchar_unlocked('\n');
  }

  return 0;
}
