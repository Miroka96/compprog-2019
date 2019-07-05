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

  putchar_unlocked('\n');
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
  vector<char> chars;
  chars.reserve(300000);
  int char_counts[3] = {};
  int char_count = 0;
  for (char c = getchar_unlocked(); c != '\n'; c = getchar_unlocked()) {
    char i = c - '0';
    char_count++;
    char_counts[i]++;
    chars.push_back(i);
  }

  int amounts_each = char_count / 3;
  char first_missing;
  rep(i, 3) {
    if (char_counts[i] < amounts_each) {
      first_missing = i;
      break;
    }
  }
  int seen[3] = {};
  for (int i = 0; i < chars.size(); i++) {
    if (char_counts[chars[i]] > amounts_each) {
      if (chars[i] == 0 && seen[0] < amounts_each) {
        seen[0]++;
        continue;
      }
      if (chars[i] == 1 && first_missing == 2 && seen[1] < amounts_each) {
        seen[1]++;
        continue;
      }

      char_counts[chars[i]]--;
      chars[i] = first_missing;
      char_counts[first_missing]++;
      if (char_counts[first_missing] == amounts_each) {
        bool found = false;
        rep(j, 3) {
          if (char_counts[j] < amounts_each) {
            first_missing = j;
            found = true;
            break;
          }
        }
        if (!found) {
          // solved
          break;
        }
      }
    }
    seen[chars[i]]++;
  }
  for(char i : chars) {
    putchar_unlocked(i + '0');
  }
  putchar_unlocked('\n');

  return 0;
}
