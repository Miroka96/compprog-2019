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

int main(int argc, char *argv[]) {
  // disable for Angelika's Input
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  // disable for Mirko's Input
  // auto in = Input(1 << 28);

  int rooms_count;
  readn(rooms_count);
  int connection_count;
  readn(connection_count);

  vector<int> vertices[rooms_count] = {};

  rep(i, connection_count) {
    int a;
    int b;
    readn(a);
    readn(b);
    a--;
    b--;
    vertices[a].push_back(b);
    vertices[b].push_back(a);
  }

  vector<int> campus_leaves;
  vector<int> campus_sizes;

  bool seen[rooms_count] = {};

  rep(root, rooms_count) {
    if (seen[root])
      continue;
    seen[root] = true;
    int size = 0;

    // node, distance
    queue<int> bfs;

    int node_id = root;
    bfs.push(node_id);
    while (!bfs.empty()) {
      tie(node_id) = bfs.front();
      size++;

      for (int child_id : vertices[node_id]) {
        if (seen[child_id])
          continue;
        seen[child_id] = true;

        bfs.push(child_id);
      }
    }

    campus_leaves.push_back(node_id);
    campus_sizes.push_back(size);
  }

  int parents[rooms_count];
  fill_n(seen, rooms_count, false);
  vector<int> campus_centres;

  for (int root : campus_leaves) {
    parents[root] = root;
    seen[root] = true;

    // node, distance
    queue<pair<int, int>> bfs;

    int node_id = root;
    int dist = 0;
    bfs.push(make_pair(node_id, dist));

    while (!bfs.empty()) {
      tie(node_id, dist) = bfs.front();

      for (int child_id : vertices[node_id]) {
        if (seen[child_id])
          continue;
        seen[child_id] = true;
		parents[child_id] = node_id;

        bfs.push(make_pair(child_id, dist + 1));
      }
    }
	// node_id is now the opposite leave of root
	// dist is the diameter-1 of the tree
	int steps_to_go_back = dist / 2;
	int middle = node_id;
	while(steps_to_go_back--) {
		middle = parents[middle];
	}

	campus_centres.push_back(middle);
  }

  // find largest campus
  // make it the central campus
  // connect all other campus centres with the central campus centre
  // run again two bfs to find diameter

  return 0;
}
