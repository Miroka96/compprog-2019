#include <bits/stdc++.h>

////////////////////////////// Helper //////////////////////

// disable debugging for submission
#define debug(x)    x
// print value of debug variable
//#define debug(x) clog << #x << " = " << x << endl

// print a debug string
#define debugs(str) // clog << str << endl
#define rep(a, b) for (int a = 0; a < (b); ++a)
#define repd(a, b) for (int a = 0; a < (b); debug(++a))
#define all(a) (a).begin(), (a).end()

using namespace std;

////////////////////////////// I/O /////////////////////////
#define BASE 10
#define OUTPUT_LENGTH 24
#define BUFFER_SIZE 1024

// buffer stdin
char inputbuffer[BUFFER_SIZE];

template <typename T> inline void readn(T &x) {
  x = 0;
  bool neg = 0;
  T c = getchar_unlocked();

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
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  char n_playlists;
  readn(n_playlists);

  int last_seen[26];

  rep(n, n_playlists) {
    // through all playlists
    int count = 0; // line length
    readn(count);
    debug(count);

    rep(i, 26) {
      last_seen[i] = -1;
    }

    char max_length = 0;
    int min = 0;
    char c;
    rep(i, count) {
      c = getchar_unlocked() - 'a';
      debug((int)c);

      int last = last_seen[c];
      last_seen[c] = i;

      debug(last);
      debug(min);

      if (last >= min) {
        min = last + 1;
        debug(min);
      } 
      
      if (i - min + 1 > max_length) {
        max_length = i - min + 1;
      }
      debug((int)max_length);
    }

    getchar_unlocked();

    write(max_length);
  }

  return 0;
}
