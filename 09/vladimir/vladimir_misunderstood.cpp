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
  register char c = getchar_unlocked();

  for (; c >= '0' && c <= '9'; c = getchar_unlocked())
    x = (x << 3) + (x << 1) + (c & 15);
}

// create output buffer
char outputbuffer[OUTPUT_LENGTH];

template <typename T> inline void write(T n) {
  int i = 0;
  do {
    outputbuffer[i++] = n % 10 + '0';
    n /= 10;
  } while (n);
  --i;

  while (i >= 0)
    putchar_unlocked(outputbuffer[i--]);
}

inline void print(const char *str) {
  for (const char *c = str; *c; c++) {
    putchar_unlocked(*c);
  }
}

////////////////////////////// Task ////////////////////////

int main(int argc, char *argv[]) {
  // disable for Angelika's Input
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  // disable for Mirko's Input
  // auto in = Input(1 << 28);

  int blocks_count;
  readn(blocks_count);

  int colours_count;
  readn(colours_count);

  int blocks[blocks_count];
  int blocks_reverse[blocks_count];
  for (int i = blocks_count - 1, j = 0; i >= 0; i--, j++) {
    int colour;
    readn(colour);
    blocks_reverse[i] = colour;
    blocks[j] = colour;
  }

  int relevant_count = (blocks_count) / 2;
  //int relevant_count = blocks_count;

  int string_length = relevant_count + blocks_count + 1;
  int string[string_length];

  string[relevant_count] = 0;
  int second_half = relevant_count + 1;
  rep(i, relevant_count) {
    string[i] = blocks_reverse[i];
  }

  for(int i = 0; i < blocks_count; i++) {
    string[second_half + i] = blocks[i];
  }

  int Z[string_length] = {};
  int l = 0;
  int r = 0;
  for (int i = 1; i < string_length; i++) {
    if (i <= r) {
      Z[i] = min(r - i + 1, Z[i - l]);
    }
    while (i + Z[i] < string_length && string[Z[i]] == string[i + Z[i]]) {
      Z[i]++;
    }
    if (i + Z[i] - 1 > r) {
      l = i;
      r = i + Z[i] - 1;
    }
  }

  bool first = true;
  for (int i = string_length - 2*relevant_count; i < string_length; i+=2) {
    if (2 * Z[i] + i >= string_length) {
      if (first) {
        first = false;
      } else {
        putchar_unlocked(' ');
      }
      write((i + string_length + 1) / 2 - second_half);
    }
  }
  if (!first) {
    putchar_unlocked(' ');
  }
  write(blocks_count);
  putchar_unlocked('\n');

  return 0;
}
