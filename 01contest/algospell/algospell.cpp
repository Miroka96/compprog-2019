#include <bits/stdc++.h>

////////////////////////////// Helper //////////////////////

#define rep(a, b) for (int a = 0; a < (b); ++a)

using namespace std;

////////////////////////////// I/O /////////////////////////
#define OUTPUT_LENGTH 24
#define BUFFER_SIZE 0xfffff

char inputbuffer[BUFFER_SIZE];

template <typename T> inline void readn(T &x) {
  x = 0;
  bool neg = 0;
  register T c = getchar_unlocked();

  for (; c >= '0' && c <= '9'; c = getchar_unlocked())
    x = (x << 3) + (x << 1) + (c & 15);
}

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

typedef uint16_t vertex_t;
typedef uint16_t weight_t;
typedef uint32_t path_weight_t;

constexpr const path_weight_t infinity = -1;

int main(int argc, char *argv[]) {
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  vertex_t vertex_count;
  int edge_count;
  readn(vertex_count);
  readn(edge_count);

  weight_t weights[vertex_count][vertex_count];

  rep(i, vertex_count) {
    rep(j, vertex_count) { weights[i][j] = infinity; }
  }

  while (edge_count--) {
    vertex_t from, to;
    weight_t weight;
    readn(from);
    readn(to);
    readn(weight);

    weights[from][to] = weight;
  }

  vertex_t start = 0;
  vertex_t target = vertex_count - 1;

  path_weight_t distances[vertex_count];
  fill_n(distances, vertex_count, infinity);

  bool marked[vertex_count];
  fill_n(marked, vertex_count, false);

  distances[start] = 0;
  path_weight_t recent_distance = 0;

  while (start != target) {
    marked[start] = true;

    rep(neighbor, vertex_count) {
      if (weights[start][neighbor] == infinity)
        continue;

      const path_weight_t possible_dist =
          recent_distance + weights[start][neighbor];

      if (distances[neighbor] > possible_dist) {
        distances[neighbor] = possible_dist;
      }
    }

    recent_distance = infinity;
    rep(i, vertex_count) {
      if (marked[i])
        continue;
      if (distances[i] < recent_distance) {
        recent_distance = distances[i];
        start = i;
      }
    }
  }
  write(distances[target]);

  return 0;
}
