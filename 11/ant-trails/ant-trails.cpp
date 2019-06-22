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
  register char c;
  for (c = getchar_unlocked(); c < '0' || c > '9'; c = getchar_unlocked());

  for (; c >= '0' && c <= '9'; c = getchar_unlocked())
    x = (x << 3) + (x << 1) + (c & 15);
}

// create output buffer
char outputbuffer[OUTPUT_LENGTH];

template <typename T> inline void write(T n) {
  int i = 0;
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
}

////////////////////////////// Task ////////////////////////

struct node_t {
  char path;
  char track;
  char out;
};

inline bool equal(const node_t &a, const node_t &b) {
  if (a.path != b.path) return false;
  if (a.track != b.track) return false;
  if (a.out != b.out) return false;
  return true;
}

int main(int argc, char *argv[]) {
  // disable for Angelika's Input
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  // disable for Mirko's Input
  //auto in = Input(1 << 28);

  char test_count;
  readn(test_count);

  rep(test, test_count) {
    char path_count;
    char track_count;
    readn(path_count);
    readn(track_count);

    vector<node_t> graph[path_count][track_count][2];
    rep(path, path_count) {
      rep(track, track_count) {
        vector<node_t> &outgoing = graph[path][track][1];
        outgoing.reserve(4);
        if (path - 1 >= 0) {
          outgoing.push_back(node_t{path-1, track, 0});
        }
        if (path + 1 < path_count) {
          outgoing.push_back(node_t{path+1, track, 0});
        }
        if (track - 1 >= 0) {
          outgoing.push_back(node_t{path, track-1, 0});
        }
        if (track + 1 < track_count) {
          outgoing.push_back(node_t{path, track+1, 0});
        }
        graph[path][track][0].push_back(node_t{path, track, 1});
      }
    }

    short crossing_count;
    readn(crossing_count);
    vector<node_t> crossings;
    crossings.reserve(crossing_count);

    rep(crossing, crossing_count) {
      char path;
      char track;
      readn(path);
      readn(track);
      path--;
      track--;
      graph[path][track][0].resize(0);
      if (0 < path && path < path_count - 1 && 0 < track && track < track_count - 1) {
        crossings.push_back(node_t{path, track, 1});
      }
    }

    node_t parents[path_count][track_count][2];

    for (node_t &source : crossings) {
      queue<node_t> bfs;
      bool seen[path_count][track_count][2] = {};

      node_t exit;
      bool found_path = false;
      parents[source.path][source.track][source.out] = source;

      seen[source.path][source.track][source.out] = true;
      bfs.push(source);
      
      while(!bfs.empty()) {
        node_t &parent = bfs.front();
        
        for(node_t &child : graph[parent.path][parent.track][parent.out]) {
          if (seen[child.path][child.track][child.out]) {
            continue;
          }
          parents[child.path][child.track][child.out] = parent;
          if (child.out == 1 && (child.path == 0 || child.path == path_count - 1 || child.track == 0 || child.track == track_count - 1)) {
            exit = child;
            found_path = true;
            goto found_border;
          }
          seen[child.path][child.track][child.out] = true;
          bfs.push(child);
        }
        
        bfs.pop();
      }
      found_border:

      if (found_path) {
        while (!equal(parents[exit.path][exit.track][exit.out], exit)) {
          node_t &parent = parents[exit.path][exit.track][exit.out];

          auto &children = graph[parent.path][parent.track][parent.out];
          auto it = children.cbegin();
          do {
            if (equal(*it, exit)) {
              children.erase(it);
              break;
            }
          } while(++it != children.cend());

          graph[exit.path][exit.track][exit.out].push_back(parent);

          exit = parent;
        }
      } else {
        print("not possible\n");
        goto next_test;
      }
    }
    print("possible\n");
    next_test:;
  }

  // BFS von allen Crossings zum Rand und dabei Pfade invertieren.
  // entweder es geht oder halt nicht


  return 0;
}
