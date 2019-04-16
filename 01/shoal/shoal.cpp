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
  // bool neg = 0;
  register T c = getchar_unlocked();

  // if (c == '-') neg = 1, c = getchar_unlocked();

  for (; c >= '0' && c <= '9'; c = getchar_unlocked())
    x = (x << 3) + (x << 1) + (c & 15);

  // if (neg) x *= -1;
}

// create output buffer
char outputbuffer[OUTPUT_LENGTH];

template <typename T> inline void write(T n) {
  // bool neg = 0;
  // if (n < 0) n *= -1, neg = 1;

  int i = 0;
  do {
    outputbuffer[i++] = n % 10 + '0';
    n /= 10;
  } while (n);
  --i;

  // if (neg) putchar_unlocked('-');

  while (i >= 0)
    putchar_unlocked(outputbuffer[i--]);

  putchar_unlocked('\n');
}

////////////////////////////// Graph ///////////////////////
typedef struct Vertex tVertex;

typedef short vertexindex;

struct Vertex {
  vertexindex parent;
  short rank;
};

#define MAX_VERTEX_COUNT 1000
tVertex vertices[MAX_VERTEX_COUNT];

#define vertex(ivertex) vertices[ivertex]
#define parent(ivertex) vertex(ivertex).parent
#define rank(ivertex) vertex(ivertex).rank

#define debugVertex(ivertex)                                                   \
  debug(ivertex);                                                              \
  debug(parent(ivertex));

// update the whole hierarchy (reset parent)
template <typename T>
inline void compressSet(T ivertex_initial, T ivertex_parent) {
  register vertexindex bufferVertex;
  while (parent(ivertex_initial) != ivertex_parent) {
    bufferVertex = parent(ivertex_initial);
    parent(ivertex_initial) = ivertex_parent;
    ivertex_initial = bufferVertex;
  }
}

// get the set of a vertex by following its parents and compress the set
// structure
template <typename T> inline T findSet(T ivertex) {
  auto bufferVertex = ivertex;
  while (ivertex != parent(ivertex)) {
    // debugVertex(ivertex);
    ivertex = parent(ivertex);
  }
  compressSet(bufferVertex, ivertex);
  return ivertex;
}

// make set_a a subset of set_b
template <typename T> inline void unionSetAWithB(T ivertex_a, T ivertex_b) {
  parent(ivertex_a) = ivertex_b;
  rank(ivertex_b)++;
}

// make the less high set a subset of the higher set
template <typename T>
inline void unionKnownSets(T ivertex_a, T ivertex_b, T ivertex_a_upd,
                           T ivertex_b_upd) {
  if (rank(ivertex_a) <= rank(ivertex_b)) {
    unionSetAWithB(ivertex_a, ivertex_b);
  } else {
    unionSetAWithB(ivertex_b, ivertex_a);
  }
}

template <typename T> inline void unionSets(T ivertex_a, T ivertex_b) {
  unionKnownSets(findSet(ivertex_a), findSet(ivertex_b), ivertex_a, ivertex_b);
}

template <typename T> inline bool sameSet(T ivertex_a, T ivertex_b) {
  return findSet(ivertex_a) == findSet(ivertex_b);
}

////////////////////////////// Task ////////////////////////

int main(int argc, char *argv[]) {
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  unsigned short n, m;
  readn(n);
  readn(m);

  rep(puddle, n) { parent(puddle) = puddle; }

  rep(moat, m) {
    vertexindex start, end;
    readn(start);
    readn(end);
    unionSets(start, end);
  }

  rep(puddle, n) {
    if (!sameSet(0, puddle)) {
      write(0);
      return 0;
    }
  }

  write(1);

  return 0;
}
