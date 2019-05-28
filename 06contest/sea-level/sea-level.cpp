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
	putchar_unlocked('\n');
}

////////////////////////////// Task ////////////////////////

struct node {
  node *parent = 0;

  node *find() {
    node *current = this;
    while (current->parent != 0) {
      current = current->parent;
    }
    if (parent != 0) {
      parent = current;
    }
    return current;
  }

  void unionWith(node *other) { parent = other; }
};

struct edge {
  int a;
  int b;
  edge *next;
  int h;
};

struct query {
  int from;
  int to;
  int h;
  int index;
	bool works;
};

int main(int argc, char *argv[]) {
  // disable for Angelika's Input
  // setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  // disable for Mirko's Input
  auto in = Input(1 << 28);

  int towns_count = in;
  int roads_count = in;
  int queries_count = in;

  node towns[towns_count] = {};
  rep(i, towns_count) { towns[i].parent = 0; }
  edge roads[roads_count];

  rep(i, roads_count) {
    int a = in;
    int b = in;
    short h = in;
    roads[i].a = --a;
    roads[i].b = --b;
    roads[i].h = h;
  }

  query queries[queries_count];

  rep(i, queries_count) {
    int from = in;
    int to = in;
    int h = in;

    queries[i].from = --from;
    queries[i].to = --to;
    queries[i].h = h;
    queries[i].index = i;
  }

	auto edge_height_sorter = [](edge &a, edge &b) {
		return a.h > b.h;
	};

	auto query_height_sorter = [](query &a, query &b){
		return a.h > b.h;
	};
	auto index_sorter = [](query &a, query &b){
		return a.index < b.index;
	};

	sort(queries, queries + queries_count, query_height_sorter);
	sort(roads, roads + roads_count, edge_height_sorter);

	int roads_done = 0;
	int queries_done = 0;
	for(int height = 2000; height >= 0; height--) {
		for(; roads_done < roads_count && roads[roads_done].h >= height; roads_done++) {
			auto &road = roads[roads_done];
			node *x = towns[road.a].find();
			node *y = towns[road.b].find();
			if (x != y) {
				x->unionWith(y);
			}
		}

		for(; queries_done < queries_count && queries[queries_done].h >= height; queries_done++) {
			auto &query = queries[queries_done];
			node *x = towns[query.from].find();
    	node *y = towns[query.to].find();
			if (x == y) {
				query.works = true;
			} else {
				query.works = false;
			}
		}
	}

	sort(queries, queries + queries_count, index_sorter);
	rep(i, queries_count) {
		if (queries[i].works) {
			print("YES");
		} else {
			print("NO");
		}
	}

  return 0;
}
