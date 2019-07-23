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

struct point {
  int x, y;
};

inline point subtract(const point &a, const point &b) {
  return point{a.x - b.x, a.y - b.y};
}

#define DOUBLE_MAX (double)1000000

inline double arc2(const point &p) {
  if (p.x > 0) {
    assert ((double)p.y / p.x < DOUBLE_MAX);
    return (double)p.y / p.x - DOUBLE_MAX; // between -inf and 0
  } else if (p.x < 0) {
    if (p.y > 0) {
      assert ((double)-p.y / p.x < DOUBLE_MAX);
      return (double)-p.x / p.y; // between 0 and inf
    } else {
      return DOUBLE_MAX;
    }
  } else {
    return 0;
  }
}

inline double arc(const point &p) {
  return atan2(p.y, p.x);
}

inline double arc(const point &s, const point &p) {
  return arc(subtract(p, s));
}

template <typename T> inline int sgn(T val) {
  return (T(0) < val) - (val < T(0));
}

inline int direction(const point &a, const point &b, const point &c) {
  return sgn((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));
}

inline bool in_polygon(const point &p, const vector<point> &hull) {
  for (int i = 1; i < hull.size(); i++) {
    if (direction(p, hull[i - 1], hull[i]) > 0)
      return false;
  }
  if (direction(p, hull.back(), hull[0]) > 0)
    return false;
  return true;
}

inline bool on_segment(point a, point b, point p) {
  if (p.x <= max(a.x, b.x) && p.x >= min(a.x, b.x) && p.y <= max(a.y, b.y) &&
      p.y >= min(a.y, b.y)) {
        /* 
    point d1 = subtract(b, a);
    point d2 = subtract(p, a);
    double a1 = (double)d1.y / (double)d1.x;
    double a2 = (double)d2.y / (double)d2.x;
    if (abs(a1-a2) < 0.01) {
      return true;
    }
    */
   if (direction(a, b, p) == 0) {
     return true;
   }
  }
  return false;
}

int main(int argc, char *argv[]) {
  // disable for Angelika's Input
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  int test_cases;
  readn(test_cases);

  while(test_cases--) {
    vector<point> landing_zone;
    landing_zone.reserve(4);
    rep(p, 4) {
      int x;
      int y;
      readn(x);
      readn(y);
      landing_zone.push_back(point{x,y});
    }

    bool in_it = true;

    point points[4];
    rep(i, 4) {
      // package
      int x;
      int y;
      readn(x);
      readn(y);
      points[i] = point{x,y};
    }

    rep(i, 4) {
      point p = points[i];
      if (!in_polygon(p, landing_zone)) {
        in_it = false;
        break;
      }

      for(int i = 0, j = 1; i < 4; i++, j = (j + 1) % 4) {
        if (on_segment(landing_zone[i], landing_zone[j], p)) {
          in_it = false;
          goto result;
        }
      }

    }
    result:
    if (in_it) {
      print("IN\n");
    } else {
      print("NOT IN\n");
    }
  }
  

  return 0;
}
