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

// squared
inline int64_t dist(const point &a, const point &b) {
  return ((int64_t)(a.x - b.x)) * ((int64_t)(a.x - b.x)) +
         ((int64_t)(a.y - b.y)) * ((int64_t)(a.y - b.y));
}

bool cmp_x(const point &a, const point &b) { return a.x < b.x; }

bool cmp_y(const point &a, const point &b) { return a.y < b.y; }

// end points to the next element
int64_t dnc(int start, int end, const vector<point> &points) {
  if (end - start == 3) {
    int64_t ab, bc, ca;
    ab = dist(points[start], points[start + 1]);
    bc = dist(points[start + 1], points[start + 2]);
    ca = dist(points[start], points[start + 2]);
    return min(min(ab, bc), ca);
  }
  if (end - start == 2) {
    return dist(points[start], points[start + 1]);
  }
  // end - start is always > 3

  int64_t left_dist, right_dist;
  int middle = (start + end) / 2;
  left_dist = dnc(start, middle, points);
  right_dist = dnc(middle, end, points);

  int splitting_x = (points[middle - 1].x + points[middle].x) / 2;

  int64_t recent_dist = min(left_dist, right_dist);
  int distance_range = floor(sqrt(recent_dist) + 0.5);
  point lower_point = point{splitting_x - distance_range, 0};
  point upper_point = point{splitting_x + distance_range, 0};
  auto lower = lower_bound(points.begin() + start, points.begin() + middle,
                           lower_point, cmp_x);
  auto upper = upper_bound(points.begin() + middle, points.begin() + end,
                           upper_point, cmp_x);
  int64_t min_dist = recent_dist;

  vector<point> yordered_left;
  copy(lower, points.begin() + middle, back_inserter(yordered_left));
  sort(yordered_left.begin(), yordered_left.end(), cmp_y);

  vector<point> yordered_right;
  copy(points.begin() + middle, upper, back_inserter(yordered_right));
  sort(yordered_right.begin(), yordered_right.end(), cmp_y);

  auto a = yordered_left.begin();
  auto b = yordered_right.begin();
  while (a < yordered_left.end() && b < yordered_right.end()) {
    if (a->y < b->y - distance_range) {
      a++;
      continue;
    }
    if (a->y - distance_range > b->y) {
      b++;
      continue;
    }
    int64_t possible_dist = dist(*a, *b);
    if (possible_dist < min_dist) {
      min_dist = possible_dist;
    }

    for (auto right = b + 1; right < yordered_right.end(); right++) {
      if (a->y < right->y - distance_range) {
        break;
      }
      int64_t possible_dist = dist(*a, *right);
      if (possible_dist < min_dist) {
        min_dist = possible_dist;
      }
    }

    for (auto left = a + 1; left < yordered_left.end(); left++) {
      if (b->y < left->y - distance_range) {
        break;
      }
      int64_t possible_dist = dist(*left, *b);
      if (possible_dist < min_dist) {
        min_dist = possible_dist;
      }
    }

    a++;
    b++;
  }
  return min_dist;
}

int main(int argc, char *argv[]) {
  // disable for Angelika's Input
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  // disable for Mirko's Input
  // auto in = Input(1 << 28);

  int students_count;
  readn(students_count);

  vector<point> students;
  students.reserve(students_count);
  rep(s, students_count) {
    int x, y;
    readn(x);
    readn(y);
    students.push_back(point{x, y});
  }

  sort(students.begin(), students.end(), cmp_x);

  write(dnc(0, students.size(), students));

  return 0;
}
