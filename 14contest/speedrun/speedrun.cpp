#include <bits/stdc++.h>
#include <unistd.h>

////////////////////////////// Helper //////////////////////

// disable debugging for submission
#define debug(x) x
// print value of debug variable
//#define debug(x) clog << #x << " = " << x << endl

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

  // putchar_unlocked('\n');
}

inline void print(const char *str) {
  for (const char *c = str; *c; c++) {
    putchar_unlocked(*c);
  }
}

////////////////////////////// Task ////////////////////////

typedef unsigned short vertex_t;
typedef uint32_t weight_t;
typedef uint64_t path_weight_t;
#undef INFINITY
#define INFINITY 0xffffffff;

typedef struct Vertex {
  path_weight_t distance;
  unordered_map<vertex_t, weight_t> outgoing;
  int parent;
  int steps;
} vertex;

std::vector<vertex> vertices;

#define get_vertex(v) vertices[v]
#define get_distance(v) get_vertex(v).distance

inline void insert_weight(const vertex_t &x, const vertex_t &y,
                          const weight_t &w) {
  get_vertex(x).outgoing[y] = w;
}

typedef pair<path_weight_t, vertex_t> dijkstra_distance;

const auto minimum_dijstra_distance_comparator = [](dijkstra_distance &a,
                                                    dijkstra_distance &b) {
  return a.first > b.first;
};

#define create_dijkstra_priority_queue(name)                                   \
  priority_queue<dijkstra_distance, std::vector<dijkstra_distance>,            \
                 decltype(minimum_dijstra_distance_comparator)>                \
      name(minimum_dijstra_distance_comparator)

inline path_weight_t AdjacencyListDijkstra(vector<vertex> &vertices,
                                           vertex_t start,
                                           const vertex_t &target) {
  create_dijkstra_priority_queue(distance_queue);

  for (auto &vertex : vertices) {
    vertex.distance = INFINITY;
    vertex.parent = -1;
    vertex.steps = -1;
  }
  get_distance(start) = 0;
  vertices[start].steps = 0;

  path_weight_t recent_distance = 0;

  while (true) {
    debug(start);
    debug(recent_distance);
    debug(get_distance(start));

    if (get_distance(start) ==
        recent_distance) { // necessary to skip old values in the queue (they
                           // are hard to delete)
      if (start == target)
        break;

      for (const auto &[neighbor, edge_weight] : get_vertex(start).outgoing) {
        debug(neighbor);
        debug(edge_weight);
        if (neighbor == start)
          continue;

        const auto possible_dist = recent_distance + edge_weight;
        debug(possible_dist);

        if (get_distance(neighbor) > possible_dist) {
          get_distance(neighbor) = possible_dist;
          get_vertex(neighbor).parent = start;
          get_vertex(neighbor).steps = get_vertex(start).steps + 1;
          distance_queue.push({possible_dist, neighbor});
        } else if (get_distance(neighbor) == possible_dist) {
          if (get_vertex(neighbor).steps > get_vertex(start).steps + 1) {
            get_vertex(neighbor).parent = start;
            get_vertex(neighbor).steps = get_vertex(start).steps + 1;
          } else if (get_vertex(neighbor).steps == get_vertex(start).steps + 1) {
            if (start < get_vertex(neighbor).parent) {
              get_vertex(neighbor).parent = start;
            }
          }
        }
      }
    }
    // if (distance_queue.empty()) return 0; // no path

    tie(recent_distance, start) = distance_queue.top();
    distance_queue.pop();
  }
  return recent_distance;
}

int main(int argc, char *argv[]) {
  // disable for Angelika's Input
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  int nodes_count;
  readn(nodes_count);
  int edge_count;
  readn(edge_count);

  vertices.reserve(nodes_count);
  rep(node, nodes_count) {
    vertices.push_back(Vertex{});
  }

  rep(i, edge_count) {
    vertex_t from;
    vertex_t to;
    weight_t weight;
    readn(from);
    readn(to);
    readn(weight);

    insert_weight(from, to, weight);
  }

  path_weight_t distance = AdjacencyListDijkstra(vertices, 0, nodes_count - 1);
  write(distance);
  putchar_unlocked('\n');

  vector<int> pres;
  pres.push_back(nodes_count - 1);

  for (int parent = get_vertex(nodes_count - 1).parent; parent != -1;
       parent = get_vertex(parent).parent) {
    pres.push_back(parent);
  }

  bool first = true;
  for (int i = pres.size() - 1; i >= 0; i--) {
    if (first) {
      first = false;
    } else {
      putchar_unlocked(' ');
    }
    write(pres[i]);
  }
  putchar_unlocked('\n');

  return 0;
}
