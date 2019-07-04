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

////////////////////////////// I/O /////////////////////////
#define BASE 10
#define OUTPUT_LENGTH 24
#define BUFFER_SIZE 0x10000000

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

inline void skip() {
  char c = getchar_unlocked();
  if (c == '-')
    c = getchar_unlocked();
  for (; c >= '0' && c <= '9'; c = getchar_unlocked())
    ;
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

int main(int argc, char *argv[]) {
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  int64_t area = 0;

  int numbers_count;
  readn(numbers_count);

  int64_t x_old, y_old;
  readn(x_old);
  readn(y_old);
  int64_t first_x, first_y;
  first_x = x_old;
  first_y = y_old;
  int64_t x, y;
  readn(x);
  readn(y);

  int i;
  if (x == x_old) {
    i = 1;
    goto vertical;
  } else {
    i = 0;
    goto horizontal;
  }

  for (; i < numbers_count - 1; i += 2) {
    x_old = x;
    skip();
    readn(y);

  vertical:
    // same x
    area += x * (y - y_old);

    y_old = y;
    readn(x);
    skip();

  horizontal:
    // same y
    area += y * (x_old - x);
  }

  if (i == numbers_count - 1) {
    if (x == x_old) {
      y_old = y;
      readn(x);
      skip();

      // same y
      area += y * (x_old - x);

      // same x
      area += x * (first_y - y);
    } else {
      x_old = x;
      skip();
      readn(y);

      // same x
      area += x * (y - y_old);

      // same y
      area += y * (x - first_x);
    }
  } else {
    if (x == x_old) {
      // same y
      area += y * (x - first_x);
    } else {
      // same x
      area += x * (first_y - y);
    }
  }
  
  if (area < 0) area *= -1;
  write(area/2);

  return 0;
}
