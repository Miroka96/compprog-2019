#include <bits/stdc++.h>

////////////////////////////// Helper //////////////////////

// disable debugging for submission
//#define debug(x)    x
// print value of debug variable
#define debug(x) clog << #x << " = " << x << endl

#define rep(a, b) for (int a = 0; a < (b); ++a)

using namespace std;

////////////////////////////// I/O /////////////////////////
#define BASE 10
#define OUTPUT_LENGTH 24
#define BUFFER_SIZE 0x100000

// buffer stdin
char inputbuffer[BUFFER_SIZE];

template <typename T> inline void readn(T &x) {
  x = 0;
  char c = getchar_unlocked();

  for (; c >= '0' && c <= '9'; c = getchar_unlocked())
    x = (x << 3) + (x << 1) + (c & 15);
}

constexpr const uint64_t decimals[] = {
    1,       10,       100,       1000,       10000,       100000,
    1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000};

typedef double weight_t;

inline void readd(weight_t &f) {
  int64_t x = 0;
  char c = getchar_unlocked();

  for (; c >= '0' && c <= '9'; c = getchar_unlocked())
    x = (x << 3) + (x << 1) + (c & 15);

  if (c == '.') {
    c = getchar_unlocked();
    char i = 0;
    for (; c >= '0' && c <= '9'; c = getchar_unlocked(), i++) {
      x = (x << 3) + (x << 1) + (c & 15);
    }
    f = ((weight_t)x) / decimals[i];
  } else {
    f = (weight_t)x;
  }
}

////////////////////////////// Task ////////////////////////

typedef int vertex_t;

typedef pair<vertex_t, weight_t> vertexChild;

int main(int argc, char *argv[]) {
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);
  // ios_base::sync_with_stdio(false); // do not mix up c with c++ IO !
  cin.tie(NULL); // manually flush cout
  cout.precision(7);

  vertex_t vertex_count;
  readn(vertex_count);

  weight_t ratios_to_anti[vertex_count];
  vertex_t parents[vertex_count];
  vector<vertexChild> childs[vertex_count];

  for (vertex_t r = 0; r < vertex_count; r++) {
    weight_t ratio_to_anti;
    readd(ratio_to_anti);
    ratios_to_anti[r] = ratio_to_anti;
    parents[r] = -1;
    childs[r] = {};
  }
  getchar_unlocked();

  parents[0] = 0;

  rep(i, vertex_count - 1) {
    vertex_t from, to;
    readn(from);
    readn(to);
    from--;
    to--;
    weight_t matter, anti;
    readd(matter);
    readd(anti);

    weight_t double_way_ratio = matter * anti;
    childs[from].push_back(make_pair(to, double_way_ratio));
    childs[to].push_back(make_pair(from, double_way_ratio));
  }

  vertex_t tree_size = 0;
  pair<vertex_t, vertexChild> tree[vertex_count - 1]; // tree ordered by layer

  {
    vertex_t parent = 0;
    for (vertex_t i = 0; i < vertex_count - 1; i++) {
      for (const auto &child : childs[parent]) {
        if (parents[child.first] != -1)
          continue;
        parents[child.first] = parent;
        tree[tree_size++] = make_pair(parent, child);
      }
      parent = tree[i].second.first;
    }
  }

  for (vertex_t i = vertex_count - 2; i >= 0; i--) {
    const vertex_t parent = tree[i].first;
    const vertexChild &child = tree[i].second;
    const weight_t to_anti_over_child = child.second * ratios_to_anti[child.first];
    if (ratios_to_anti[parent] < to_anti_over_child) {
      ratios_to_anti[parent] = to_anti_over_child;
    }
  }

  for (vertex_t i = 0; i < vertex_count - 1; i++) {
    const vertex_t &parent = tree[i].first;
    const vertexChild &child = tree[i].second;

    const weight_t to_anti_over_parent = child.second * ratios_to_anti[parent];
    if (ratios_to_anti[child.first] < to_anti_over_parent) {
      ratios_to_anti[child.first] = to_anti_over_parent;
    }
  }

  rep(i, vertex_count) { cout << ratios_to_anti[i] << endl; }

  cout.flush();
  return 0;
}
