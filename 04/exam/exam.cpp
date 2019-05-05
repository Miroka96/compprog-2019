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
  register T c = getchar_unlocked();

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

  putchar_unlocked('\n');
}

inline void print(const char *str) {
  for (const char *c = str; *c; c++) {
    putchar_unlocked(*c);
  }
}

////////////////////////////// Task ////////////////////////

inline int& max(int& a, int& b) {
  if (a > b) return a;
  return b;
}

inline int& max(int& a, int& b, int& c) {
  return max(a, max(b, c));
}

int main(int argc, char *argv[]) {
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  short w, h;
  readn(w);
  readn(h);

  int chocolate[h][w];

  rep(i, h) {
    rep(j, w) {
      int value;
      readn(value);
      chocolate[i][j] = value;
    }
  }

  for(short i = h - 2; i >= 0; i--) {
    chocolate[i][0] += max(chocolate[i+1][0], chocolate[i+1][1]);

    for (short j = 1; j < w - 1; j++) {
      chocolate[i][j] += max(chocolate[i + 1][j - 1], chocolate[i + 1][j], chocolate[i + 1][j + 1]);
    }

    chocolate[i][w-1] += max(chocolate[i+1][w-1], chocolate[i+1][w-2]);
  }

  int max = 0;
  rep(j, w) {
    if (chocolate[0][j] > max) {
      max = chocolate[0][j];
    }
  }
  write(max);

  return 0;
}
