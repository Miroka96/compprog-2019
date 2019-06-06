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
}

////////////////////////////// Task ////////////////////////

struct node {
  int level;
  vector<int> neighbors[2];
};

struct node *planets;

struct district {
  int planet_count;
  char company;
  vector<int> neighbors;
};

vector<struct district> districts = {};

int* dfs(int parent_id, const int grand_parent_level,
         const int grand_parent_district_ids[2], const char edge_company) {
	struct node &parent = planets[parent_id];

// should be given as return parameter
	int parent_districts[2];
	rep(company, 2) {
		if (company == edge_company) {
			int district_id = grand_parent_district_ids[company];
			parent_districts[company] = district_id;
			districts[district_id].planet_count++;
		} else {
			if (parent.neighbors[company].size() > 0) {
				struct district new_district;
				new_district.planet_count = 1;
				new_district.company = company;
				new_district.neighbors.push_back(parent_id);
				parent_districts[company] = districts.size();
				districts.push_back(new_district);
			} else {
				parent_districts[company] = -1;
			}
		}
	}

  rep(company, 2) {
    for (const int &child_id : parent.neighbors[company]) {
      struct node &child = planets[child_id];
      if (grand_parent_level != child.level) {
        child.level = parent.level + 1;
      } else {
				continue;
			}
      dfs(child_id, parent.level, parent_districts, company);
    }
  }
}

int main(int argc, char *argv[]) {
  // disable for Angelika's Input
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  // disable for Mirko's Input
  // auto in = Input(1 << 28);

  int planet_count;
  readn(planet_count);
  struct node p[planet_count] = {};
  planets = p;

  rep(i, planet_count - 1) {
    int a;
    int b;
    char company;
    readn(a);
    readn(b);
    readn(company);

    planets[a].neighbors[company].push_back(b);
    planets[b].neighbors[company].push_back(a);
  }

	int initial_parent_district_ids[2] = {-1, -1};
  dfs(planets[0], -1, initial_parent_district_ids);

  // node, children_id
  stack<pair<int, int>> dfs;
  dfs.push(make_pair(0, 0));

  while (!dfs.empty()) {
    auto &[node_id, children_id] = dfs.top();
    struct node &parent = planets[node_id];

    if (children_id < parent.neighbors.size()) {
      const auto &[company, child_id] = parent.neighbors[children_id];
      struct node &child = planets[child_id];
      if (child.level < parent.level) {
        // found parent
        children_id++;
        continue;
      }

      if (child.neighbors.size() == 1) {
        // only parent
        parent.reachable_nodes[company]++;
        if (company)
      }
    }

    struct node &recent = planets[bfs.front()];
    bfs.pop();
    for (const auto &[ignore, child_id] : recent.neighbors) {
      struct node &child = planets[child_id];
      if (child.level < recent.level)
        continue;
      child.level = recent.level + 1;
      bfs.push(child_id);
    }
  }

  return 0;
}
