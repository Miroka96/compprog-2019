#include <bits/stdc++.h>

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

int main(int argc, char *argv[]) {
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  short knotenanzahl;
  int kantenanzahl;
  readn(knotenanzahl);
  readn(kantenanzahl);

  int distances[knotenanzahl];

  
  

  unsigned short weights[kantenanzahl];
  
  int lists[kantenanzahl];
  int outgoing_edges[knotenanzahl];

  short target[kantenanzahl];
  rep(i, knotenanzahl) {
    outgoing_edges[i] = -1;
    distances[i] = INT_MAX;
  }

  rep(i, kantenanzahl) {
    short from;
    short to;
    unsigned short weight;
    readn(from);
    readn(to);
    readn(weight);
    debug(from);
    debug(to);
    debug(weight);
    weights[i] = weight;

    lists[i] = outgoing_edges[from];
    outgoing_edges[from] = i;
    target[i] = to;

  }

  auto comp = [&](short a, short b){return distances[a] > distances[b];};

  vector<short> knoten;
  knoten.resize(knotenanzahl);
  

  distances[0] = 0;
  rep(i, knotenanzahl) {
    knoten.push_back(i);
  }
  make_heap (knoten.begin(),knoten.end(), comp);
//  sort_heap(knoten.begin(), knoten.end(), comp);


  while(!knoten.empty()) {
    pop_heap (knoten.begin(),knoten.end(), comp);
    short recent = knoten.back();
    knoten.pop_back();
    debug(recent);

    if (recent == knotenanzahl - 1) {
        write(distances[knotenanzahl-1]);
  
        return 0;
      }


    unsigned short dist = distances[recent];

    for( int neighbor_edge = outgoing_edges[recent]; 
      neighbor_edge != -1; 
      neighbor_edge = lists[neighbor_edge] ){

      short to = target[neighbor_edge];
      
      int to_dist = distances[to];
      int new_dist = dist + weights[neighbor_edge];


      if (to_dist >  new_dist) {
        distances[to] = new_dist;
      }

    }

    //sort_heap(knoten.begin(), knoten.end(), comp);
  }

  write(distances[knotenanzahl-1]);
  
  return 0;
}
