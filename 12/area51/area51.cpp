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
#define BUFFER_SIZE 0x100000

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
  putchar_unlocked('\n');
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
    if (direction(p, hull[i - 1], hull[i]) < 0)
      return false;
  }
  if (direction(p, hull.back(), hull[0]) < 0)
    return false;
  return true;
}

inline bool on_segment(point a, point b, point p) {
  if (p.x <= max(a.x, b.x) && p.x >= min(a.x, b.x) && p.y <= max(a.y, b.y) &&
      p.y >= min(a.y, b.y)) {
    return true;
  }
  return false;
}

inline bool intersect(const point &a_from, const point &a_to,
                      const point &b_from, const point &b_to) {
  int d1 = direction(a_from, a_to, b_from);
  int d2 = direction(a_from, a_to, b_to);
  int d3 = direction(b_from, b_to, a_from);
  int d4 = direction(b_from, b_to, a_to);

  if (d1 != d2 && d3 != d4)
    return true;
  if (d1 == 0 && on_segment(a_from, a_to, b_from)) return true;
  if (d2 == 0 && on_segment(a_from, a_to, b_to)) return true;
  if (d3 == 0 && on_segment(b_from, b_to, a_from)) return true;
  if (d4 == 0 && on_segment(b_from, b_to, a_to)) return true;
  return false;
}

inline bool cuts_polygon(const point &a, const point &b,
                         const vector<point> hull) {
  // int left_max, right_max, top_max, bottom_max;
  int cuts_count = 0;
  for (int i = 1; i < hull.size(); i++) {
    if (intersect(a, b, hull[i-1], hull[i])) {
      cuts_count++;
    }
  }
  if (intersect(a, b, hull.back(), hull[0])) {
    cuts_count++;
  }
  return cuts_count > 0;
}

int main(int argc, char *argv[]) {
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  int buildings_count;
  readn(buildings_count);
  short flights_count;
  readn(flights_count);

  point buildings[buildings_count];
  point lowest_point = point{INT32_MAX, INT32_MAX};
  int lowest_point_id = -1;
  rep(i, buildings_count) {
    int x, y;
    readn(x);
    readn(y);
    buildings[i] = point{x, y};
    if (y < lowest_point.y || y == lowest_point.y && x < lowest_point.x) {
      lowest_point = point{x, y};
      lowest_point_id = i;
    }
  }

  vector<pair<double, point>> arcs;
  arcs.reserve(buildings_count - 1);
  rep(i, buildings_count) {
    if (i == lowest_point_id)
      continue;
    arcs.push_back(make_pair(arc(lowest_point, buildings[i]), buildings[i]));
  }

  auto cmp = [](const pair<double, point> &a, const pair<double, point> &b) {
    return a.first < b.first;
  };

  sort(arcs.begin(), arcs.end(), cmp);

  vector<point> hull;
  hull.reserve(128);
  hull.push_back(lowest_point);
  hull.push_back(arcs.begin()->second);
  for (auto iter = ++arcs.cbegin(); iter != arcs.cend(); iter++) {
    while (direction(hull[hull.size() - 2], hull[hull.size() - 1],
                     iter->second) < 0) {
      hull.pop_back();
    }
    hull.push_back(iter->second);
  }

  rep(flight, flights_count) {
    int from_x, from_y, to_x, to_y;
    readn(from_x);
    readn(from_y);
    readn(to_x);
    readn(to_y);
    point from = point{from_x, from_y};
    point to = point{to_x, to_y};

    const bool started_in = in_polygon(from, hull);
    const bool target_in = in_polygon(to, hull);
    if (started_in && target_in) {
      print("TOPSECRET");
    } else if (started_in != target_in) {
      print("DANGER");
    } else {
      if (cuts_polygon(from, to, hull)) {
        print("WARNING");
      } else {
        print("IRRELEVANT");
      }
    }
  }

  return 0;
}
