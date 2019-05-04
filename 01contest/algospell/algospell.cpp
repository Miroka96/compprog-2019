#include <bits/stdc++.h>

////////////////////////////// Helper //////////////////////

// disable debugging for submission
#define debug(x) // x
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

  while (i > 0)
    putchar_unlocked(outputbuffer[--i]);

  putchar_unlocked('\n');
}

////////////////////////////// Task ////////////////////////

#define MAX_VERTEX_COUNT 4000
typedef uint64_t vertex_t;
typedef uint64_t weight_t;
typedef uint64_t path_weight_t;
#undef INFINITY
#define INFINITY 0xffffffffffffffff;

weight_t weights[MAX_VERTEX_COUNT * MAX_VERTEX_COUNT];
inline void insert_weight(vertex_t x, vertex_t y, weight_t w) {
  weights[x * MAX_VERTEX_COUNT + y] = w;
}

inline weight_t &get_weight(vertex_t x, vertex_t y) {
  return weights[x * MAX_VERTEX_COUNT + y];
}

inline weight_t *get_neighbor_weights(vertex_t x) {
  return &weights[x * MAX_VERTEX_COUNT];
}

inline path_weight_t AdjacencyMatrixDijkstra(const vertex_t &vertex_count,
                                             vertex_t start,
                                             const vertex_t &target) {

  path_weight_t *distances = new path_weight_t[vertex_count]();
  bool *marked = new bool[vertex_count]();

  rep(i, vertex_count) { distances[i] = INFINITY; }

  distances[start] = 0;
  path_weight_t recent_distance = 0;

  while (start != target) {
    marked[start] = true;

    weight_t *neighbor_weights = get_neighbor_weights(start);

    for (vertex_t neighbor = 0; neighbor < vertex_count;
         neighbor++, neighbor_weights++) {
      if (*neighbor_weights == 0)
        continue;
  
      const path_weight_t neighbor_dist = distances[neighbor];
      const path_weight_t possible_dist = recent_distance + *neighbor_weights;

      if (neighbor_dist > possible_dist) {
        distances[neighbor] = possible_dist;
      }
    }

    recent_distance = INFINITY;
    rep(i, vertex_count) {
      if (marked[i])
        continue;
      if (distances[i] < recent_distance) {
        recent_distance = distances[i];
        start = i;
      }
    }
  }
  return recent_distance;
}

int main(int argc, char *argv[]) {
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  vertex_t vertex_count;
  uint64_t edge_count;
  readn(vertex_count);
  readn(edge_count);

  rep(i, edge_count) {
    vertex_t from;
    vertex_t to;
    weight_t weight;
    readn(from);
    readn(to);
    readn(weight);
    debug(from);
    debug(to);
    debug(weight);

    insert_weight(from, to, weight);
  }

  vertex_t start = 0;
  vertex_t target = vertex_count - 1;

  write(AdjacencyMatrixDijkstra(vertex_count, start, target));

  return 0;
}
