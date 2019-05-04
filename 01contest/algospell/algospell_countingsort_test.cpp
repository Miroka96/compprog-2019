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
  register T c = getchar_unlocked();

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

typedef unsigned short vertex_t;
typedef unsigned short weight_t;
typedef unsigned int path_weight_t;
#undef INFINITY
#define INFINITY 0xffffffff;

typedef struct Vertex {
  path_weight_t distance;
  unordered_map<vertex_t,weight_t> outgoing;
} vertex;

std::vector<vertex> vertices;

#define get_vertex(v) vertices[v]
#define get_distance(v) get_vertex(v).distance

inline void insert_weight(const vertex_t& x, const vertex_t& y, const weight_t& w) {
  get_vertex(x).outgoing[y] = w;
}

typedef pair<path_weight_t,vertex_t> dijkstra_distance;

const auto minimum_dijstra_distance_comparator = [](dijkstra_distance& a, dijkstra_distance& b) {
    return a.first > b.first;
};

#define create_dijkstra_priority_queue(name) priority_queue<dijkstra_distance, std::vector<dijkstra_distance>,decltype(minimum_dijstra_distance_comparator)> name(minimum_dijstra_distance_comparator)

inline path_weight_t AdjacencyListDijkstra(vector<vertex>& vertices, vertex_t start, const vertex_t& target) {
  create_dijkstra_priority_queue(distance_queue);

  for (auto& vertex : vertices) {
    vertex.distance = INFINITY;
  }
  get_distance(start) = 0;

  path_weight_t recent_distance = 0;

  while(true) {
    debug(start);
    debug(recent_distance);
    debug(get_distance(start));

    if (get_distance(start) == recent_distance) { // necessary to skip old values in the queue (they are hard to delete)
      if (start == target) break;

      for (const auto& [neighbor, edge_weight] : get_vertex(start).outgoing) {
        debug(neighbor);
        debug(edge_weight);
        if (neighbor == start) continue;

        const auto possible_dist = recent_distance + edge_weight;
        debug(possible_dist);

        if (get_distance(neighbor) > possible_dist) {
          get_distance(neighbor) = possible_dist;
          debug(get_distance(neighbor));
          distance_queue.push({possible_dist, neighbor});
        }
      }
    }
    // if (distance_queue.empty()) return 0; // no path

    tie(recent_distance, start) = distance_queue.top();
    distance_queue.pop();
  }
  return recent_distance;
}

#define MAX_VERTEX_COUNT 3000
#define MAX_EDGE_LENGTH 50000

vector<vertex_t>* distances[MAX_VERTEX_COUNT * MAX_EDGE_LENGTH + 1];

int main(int argc, char *argv[]) {
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  vertex_t vertex_count;
  int edge_count;
  readn(vertex_count);
  readn(edge_count);

  vertices.reserve(vertex_count);
  rep(i, vertex_count) vertices.push_back(vertex{0});

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

  for (auto& vertex : vertices) {
    vertex.distance = INFINITY;
  }
  get_distance(start) = 0;
  distances[0] = new vector<vertex_t>();
  distances[0]->push_back(0);
  
  for(int distance = 0; true; distance++) {
    if (distances[distance] != 0) {
      for (const auto& vertex : *distances[distance]) {
        if (get_distance(vertex) < distance) continue;
        if (vertex == target) {
          write(distance);
          return 0;
        }
        for (const auto& [neighbor, edge_weight] : get_vertex(vertex).outgoing) {
          const auto possible_dist = distance + edge_weight;
          
          if (get_distance(neighbor) > possible_dist) {
            bool not_yet_set = true;
            if (distances[possible_dist] == 0) {
              distances[possible_dist] = new vector<vertex_t>();
            } else {
              for(const auto& vertex : *distances[possible_dist]) {
                if (vertex == neighbor) {
                  not_yet_set = false;
                  break;
                }
              }
            }
            if (not_yet_set) {
              distances[possible_dist]->push_back(neighbor);
              get_distance(neighbor) = possible_dist;
            }
          }
        }
      }
    }
    
  }  
  return 0;
}
