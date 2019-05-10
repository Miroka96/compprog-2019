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

constexpr const long long int  infinity = LLONG_MAX/2-1;

// create output buffer
char outputbuffer[OUTPUT_LENGTH];

inline void print(const char *str) {
  for (const char *c = str; *c; c++) {
    putchar_unlocked(*c);
  }
}

template <typename T> inline void write(T n) {
  if (n > infinity/4) {
    print("oo\n");
    return;
  }

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

////////////////////////////// Task ////////////////////////

typedef short vertex_t;
typedef int weight_t;
typedef long long int path_weight_t;

constexpr const int unknown = INT_MIN;
// constexpr const int infinity = INT_MAX;

template <typename T> inline T &min(T &a, T &b) {
  if (a > b)
    return b;
  return a;
}

int main(int argc, char *argv[]) {
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  vertex_t planet_count;
  int route_count;
  int query_count;

  readn(planet_count);
  readn(route_count);
  readn(query_count);

  // unordered_map<vertex_t, weight_t> weights[planet_count] = {};

  path_weight_t distances[planet_count][planet_count];
  rep(i, planet_count) rep(j, planet_count) distances[i][j] = infinity;

  rep(m, route_count) {
    vertex_t from, to;
    weight_t weight;
    readn(from);
    readn(to);
    readn(weight);

    distances[from][to] = weight;
  }

  rep(k, planet_count) rep(i, planet_count) {
    if (distances[i][k] == infinity)
      continue;
    rep(j, planet_count) {
      distances[i][j] = min(distances[i][j], distances[i][k] + distances[k][j]);
    }
  }

  rep(k, query_count) {
    vertex_t from, to;
    readn(from);
    readn(to);

    write(distances[from][to]);
  }

  return 0;
}
