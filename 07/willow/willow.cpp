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

struct Input
{
	char *buf;

	Input(size_t size) : buf((char *)malloc(size))
	{
		ios_base::sync_with_stdio(0);
		cin.tie(0);
		cout.precision(10);

		char *start = buf;
		int n = 0;
		do
		{
			buf += n;
			n = read(STDIN_FILENO, buf, size);
		} while (n > 0);
		assert(buf <= start + size);
		buf = start;
	}

	void skip_space()
	{
		while (*buf <= ' ')
			buf++;
	}

	operator char()
	{
		skip_space();
		return *buf++;
	}

	operator bool()
	{
		skip_space();
		return *buf++ != '0';
	}

	operator char *()
	{
		skip_space();
		char *s = buf;
		while (*buf++ > ' ')
			;
		buf[-1] = '\0';
		return s;
	}

	operator float()
	{
		return (double)*this;
	}

	operator double()
	{
		char *s = *this;
		return atof(s);
	}

	template <typename T>
	operator T()
	{
		skip_space();
		T n = 0;
		char c = *buf++;
		bool neg = c == '-';
		if (neg)
			c = *buf++;
		while (c > ' ')
		{
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
  register char c;
	for(c = getchar_unlocked(); c < '0' || c > '9'; c = getchar_unlocked());
 
  for (; c >= '0' && c <= '9'; c = getchar_unlocked())
    x = (x << 3) + (x << 1) + (c & 15);
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

typedef int vertex_t;
typedef int weight_t;
typedef int path_weight_t;

int main(int argc, char *argv[]) {
	// disable for Angelika's Input
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

	// disable for Mirko's Input
	//auto in = Input(1 << 28);

	vertex_t node_count;
	readn(node_count);

	vector<pair<vertex_t, weight_t>> neighbors[node_count];
	rep(i, node_count-1) {
		vertex_t from;
		vertex_t to;
		weight_t dist;
		readn(from);
		readn(to);
		readn(dist);
		neighbors[from].push_back(make_pair(to, dist));
		neighbors[to].push_back(make_pair(from, dist));
	}

	bool seen[node_count] = {};

	//vector<pair<vertex_t, path_weight_t>> stack;
	queue<pair<vertex_t, path_weight_t>> stack;
	vertex_t farest_node = 0;
	path_weight_t farest_distance = 0;
	stack.push(make_pair(farest_node, farest_distance));

	while(!stack.empty()) {
		const auto& [node, dist] = stack.front();
		stack.pop();
		seen[node] = true;
		if (dist > farest_distance) {
			farest_distance = dist;
			farest_node = node;
		}
		for(const auto& [child, child_dist] : neighbors[node]) {
			if (seen[child]) continue;
			stack.push(make_pair(child, dist + child_dist));
		}
	}

	//stack.resize(0);
	fill_n(seen, node_count, false);
	farest_distance = 0;
	stack.push(make_pair(farest_node, farest_distance));

	while(!stack.empty()) {
		const auto& [node, dist] = stack.front();
		stack.pop();
		seen[node] = true;
		if (dist > farest_distance) {
			farest_distance = dist;
		}
		for(const auto& [child, child_dist] : neighbors[node]) {
			if (seen[child]) {
				continue;
			}
			stack.push(make_pair(child, dist + child_dist));
		}
	}

	write(farest_distance);

  return 0;
}
