
#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

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
    buf[-1] = '\\0';
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
  int w;
};

bool sortingCriteria(edge e1, edge e2) { return e2.w > e1.w; }

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

int main() {
  //auto in = Input(1 << 28);
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);
  int n;
  readn(n);
  node nodeArray[n+1] = {};

  int m;
  readn(m);

  int c;
  readn(c);

	for(int i = 0; i < n; i++) {
		nodeArray[i].parent = 0;
	}

  edge edge_array[m + n];

  for (int i = 0; i < m; i++) {
    int a;
	readn(a);
    int b;
	readn(b);
    int w;
	readn(w);

    edge_array[i].a = a;
    edge_array[i].b = b;
    edge_array[i].w = w;
  }

  for (int i = 0; i < n; i++) {
    edge_array[i + m].a = n;
    edge_array[i + m].b = i;
    edge_array[i + m].w = c;
  }

  uint64_t total = 0;
  
  sort(edge_array, edge_array + m + n, sortingCriteria);

  for (int i = 0; i < m + n; i++) {
    const edge &current = edge_array[i];

    node *x = nodeArray[current.a].find();
    node *y = nodeArray[current.b].find();
    if (x != y) {
      x->unionWith(y);
      total += current.w;
    }
  }

  printf("%llu\n", total);
}
