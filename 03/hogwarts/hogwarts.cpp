#include <bits/stdc++.h>

////////////////////////////// Helper //////////////////////

// disable debugging for submission
#define debug(x)    //x
// print value of debug variable
//#define debug(x) clog << #x << " = " << x << endl

// print a debug string
#define debugs(str) // clog << str << endl
#define rep(a, b) for (int a = 0; a < (b); ++a)
#define repd(a, b) for (int a = 0; a < (b); debug(++a))
#define all(a) (a).begin(), (a).end()

using namespace std;

////////////////////////////// I/O /////////////////////////
#define OUTPUT_LENGTH 24
#define BUFFER_SIZE 1024

// buffer stdin
char inputbuffer[BUFFER_SIZE];

template <typename T> inline void readn(T &x) {
  x = 0;
  T c = getchar_unlocked();

  for (; c >= '0' && c <= '9'; c = getchar_unlocked())
    x = (x << 3) + (x << 1) + (c & 15);
}

// create output buffer
char outputbuffer[OUTPUT_LENGTH];

template <typename T> inline void write(T n) {
  char i = 0;
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
  putchar_unlocked('\n');
}

#define MAX_WORD_LENGTH 150
char string_buffer[MAX_WORD_LENGTH + 1];

string read_string(char delimeter) {
  unsigned short i = 0;
  while ((string_buffer[i++] = getchar_unlocked()) != delimeter);
  i--;
  string_buffer[i] = 0;
  return string(string_buffer, i);
}

////////////////////////////// Task ////////////////////////

#define MAX_VERTEX_COUNT 610
typedef unsigned short vertex_t;
typedef unsigned int weight_t;
typedef unsigned int path_weight_t;

typedef struct Vertex {
  path_weight_t distance;
  unordered_map<vertex_t,weight_t> outgoing;
} vertex;

std::vector<vertex> vertices;

#define get_vertex(v) vertices[v-1]
#define get_distance(v) get_vertex(v).distance

unordered_map<string, vertex_t> str_to_int;
vertex_t highest_map_index = 0;

vertex_t get_or_create_index(const string& str) {
  vertex_t& value = str_to_int[str];
  if (value == 0) {
    value = ++highest_map_index;
    vertices.push_back(vertex{});
    debug(&get_vertex(highest_map_index).outgoing);
  }
  return value;
}



inline void insert_weight(const vertex_t& x, const vertex_t& y, const weight_t& w) {
  if (w == 0) {
    vertices[x-1].outgoing.erase(y);
    vertices[y-1].outgoing.erase(x);
  } else {
    vertices[x-1].outgoing[y] = w;
    vertices[y-1].outgoing[x] = w;
  }
}

/*
weight_t weights[MAX_VERTEX_COUNT*MAX_VERTEX_COUNT];
inline void insert_weight(vertex_t x, vertex_t y, weight_t w) {
  x--;
  y--;
  weights[x * MAX_VERTEX_COUNT + y] = w;
  weights[y * MAX_VERTEX_COUNT + x] = w;
}
// preferably iterate by incrementing y
inline weight_t get_weight(vertex_t x, vertex_t y) {
  x--;
  y--;
  return weights[x * MAX_VERTEX_COUNT + y];
}
*/
typedef pair<path_weight_t,vertex_t> dijkstra_distance;


int main(int argc, char *argv[]) {
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  vertices.reserve(MAX_VERTEX_COUNT);
  str_to_int.reserve(MAX_VERTEX_COUNT);
  
  get_or_create_index("Gryffindor-Common-Room");
  vertex_t start = 1;

  short n;  // number of help requests
  readn(n);

  auto comp_minimum_distance = [](dijkstra_distance& a, dijkstra_distance& b) {
    return a.first > b.first;
  };

  rep(help_i, n) {
    debug(start);
    vertex_t target = get_or_create_index(read_string('\n'));
    debug(target);

    short k;  // number of changed corridors
    readn(k);

    rep(edge_i, k) {
      vertex_t from = get_or_create_index(read_string(' '));
      vertex_t to = get_or_create_index(read_string(' '));
      
      weight_t time;
      readn(time);

      debug(from);
      debug(to);
      debug(time);

      insert_weight(from, to, time);
    }

    priority_queue<dijkstra_distance, std::vector<dijkstra_distance>, decltype(comp_minimum_distance)> distance_queue(comp_minimum_distance);
    for (auto& vertex : vertices) {
      vertex.distance = 0xffffffff;
    }
    get_distance(start) = 0;
    //path_weight_t* distances = new path_weight_t[highest_map_index]();

    path_weight_t recent_distance = 0;

    do {
      debug(start);
      debug(recent_distance);
      debug(get_distance(start));
      if (get_distance(start) == recent_distance) {
        if (start == target) break;

        for (auto& neighbor : get_vertex(start).outgoing) {
          debug(neighbor.first);
          debug(neighbor.second);
          if (neighbor.first == start) continue;

          const auto& possible_dist = recent_distance + neighbor.second;
          debug(possible_dist);

          if (get_distance(neighbor.first) > possible_dist) {
            get_distance(neighbor.first) = possible_dist;
            debug(get_distance(neighbor.first));
            distance_queue.push({possible_dist, neighbor.first});
          }
        }
        /*
        for (vertex_t neighbor = 1; neighbor <= highest_map_index; neighbor++) {
          debug(neighbor);
          if (neighbor == start) continue;

          weight_t edge_weight = get_weight(start, neighbor);
          debug(edge_weight);
          if (edge_weight == 0) continue;
          //insert_weight(start, neighbor, 0);// delete edge for the second direction (can only be larger)
          
          const auto& neighbor_dist = distances[neighbor-1];
          const auto& possible_dist = recent_distance + edge_weight;
          debug(neighbor_dist);
          debug(possible_dist);

          if (neighbor_dist == 0 || neighbor_dist > possible_dist) {
            distances[neighbor - 1] = possible_dist;
            debug(distances[neighbor - 1]);
            distance_queue.push({possible_dist, neighbor});
          }
        }*/
      }
      // if (distance_queue.empty()) return 1; // no path
      tie(recent_distance, start) = distance_queue.top();
      distance_queue.pop();
    } while(true);

    write(recent_distance);

    start = target;
  }

  return 0;
}
