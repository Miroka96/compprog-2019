#include <bits/stdc++.h>
#include <unistd.h>

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

///////////////////////////// Graph ////////////////////////

#define MAX_VERTEX_COUNT 610
typedef int vertex_t;
typedef unsigned int weight_t;
typedef unsigned int path_weight_t;
#undef INFINITY
#define INFINITY 0xffffffff;

typedef struct Vertex {
  path_weight_t distance;
  vector<vertex_t> outgoing;
  bool visited;
  bool finished;
} vertex;



#define get_vertex(v) vertices[v-1]
#define get_distance(v) get_vertex(v).distance

////////////////////////// Dijkstra /////////////////////

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

      for (const auto& neighbor : get_vertex(start).outgoing) {
        debug(neighbor);
        if (neighbor == start) continue;

        const auto possible_dist = recent_distance + 1;
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

////////////////////////////// Task ////////////////////////
int height;
int width;

inline int cood_to_id(int a, int b) {
	return a * (int)width + b;
}

int main(int argc, char *argv[]) {
	// disable for Angelika's Input
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

	// disable for Mirko's Input
	//auto in = Input(1 << 28);

	
	readn(height);
	
	readn(width);

	char k;
	readn(k);

	bool field[height][width];

	vector<vertex> vertices;
	rep(i, height) {
		rep(j, width) {
			char c = getchar_unlocked();
			field[i][j] = (c == '.');
			
			vertices.push_back({});
		}
		getchar_unlocked();
	}

	int x[] = {-1, 1, 0, 0, -k, k, 0, 0};
	int y[] = {0, 0, -1, 1, 0, 0, -k, k};

	rep(i, height) {
		rep(j, width) {
			if (!field[i][j]) continue;

			vertex &vert = vertices[cood_to_id(i, j)];
			vert.distance = INFINITY;

			rep(f, 8) {
				if (i + x[f] < 0 || i + x[f] >= height) continue;
				if (j + y[f] < 0 || j + y[f] >= width) continue;

				if (field[i + x[f]][j + y[f]]) {
					vert.outgoing.push_back(cood_to_id(i + x[f], j + y[f]));
				}
			}
/*
			for(int n_k = 1; n_k <= k; n_k += (k - 1)) {
				for(int n_i = -n_k; n_i <= n_k; n_i+=2*n_k) {
					if (i + n_i < 0) continue;
					if (i + n_i >= height) continue;

					if (field[i + n_i][j]) {
						vert.outgoing.push_back(cood_to_id(i + n_i, j));
					}
				}
				for(int n_j = -n_k; n_j <= n_k; n_j+=2*n_k) {
					if (i + n_j < 0) continue;
					if (i + n_j >= width) continue;

					if (field[i][j + n_j]) {
						vert.outgoing.push_back(cood_to_id(i, j + n_j));
					}
				}
			}*/
		}
	}

	vertices[0].distance = 0;

// --------------------- Breitensuche ---------------------
	
	// vertex, dist
	list<pair<int, int>> queue;

	vertices[0].visited = true;
	queue.push_back(make_pair(0, 0));

	int current_distance = 0;

	while (!queue.empty())
	{
		auto [id, dist] = queue.front();
		
		if (dist > current_distance) {
			current_distance ++;
		}
		vertex &c = vertices[id];

		queue.pop_front();

		if (c.finished) continue;
		c.finished = true;

		for (int neighbor_id : c.outgoing)
		{
			if (neighbor_id == cood_to_id(height-1, width - 1)) {
				write(current_distance + 1);
				return 0;
			}

			vertex &neighbor = vertices[neighbor_id];

			if (!neighbor.visited)
			{
				neighbor.visited = true;
				queue.push_back(make_pair(neighbor_id, current_distance + 1));
			}
		}
	}
	write(-1);

  return 0;
}
