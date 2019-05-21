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

int main(int argc, char *argv[]) {
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);
  
  int cups_count;
  readn(cups_count);

  bool is_root[cups_count];
  fill(is_root, is_root + cups_count, true);

  short values[cups_count];
  vector<int> children[cups_count] = {};

  rep(i, cups_count) {
    short value;
    readn(value);
    values[i] = value;
  }

  rep(i, cups_count - 1) {
    int from;
    int to;
    readn(from);
    readn(to);
    is_root[to] = false;
    children[from].push_back(to);
  }

  int root;

  rep(i, cups_count) {
    if (is_root[i]) {
      root = i;
      break;
    }
  }

  // level, node
  auto cmp = [](const pair<int, int>& a, const pair<int, int>& b){
    return a.first > b.first;
  };

  vector<pair<int, int>> leaf_queue;
  leaf_queue.reserve(cups_count);
  leaf_queue.push_back(make_pair(0, root));

  vector<pair<int,int>> stack;
  stack.reserve(1<<8);

  int level = 0;
  stack.push_back(make_pair(level, root));

  rep(i, cups_count) {
    const auto& [current_level, current_node] = stack.back();
    stack.pop_back();

    if(current_level > level) level = current_level;

    for (const auto& child : children[current_node]) {
      stack.push_back(make_pair(level + 1, child));
      leaf_queue.push_back(make_pair(level + 1, child));
    }
  }

  sort(leaf_queue.begin(), leaf_queue.end(), cmp);

  // with, without
  pair<unsigned int, unsigned int> max_values[cups_count];

  rep(i, cups_count) {
    const auto [current_level, current_node] = leaf_queue[i];

    unsigned int with, without;
    with = values[current_node];
    without = 0;

    for (const auto& child : children[current_node]) {
      with += max_values[child].second;
      without += max(max_values[child].first, max_values[child].second);
    }

    max_values[current_node] = {with, without};
  }

  if (max_values[root].first > max_values[root].second) {
    write(max_values[root].first);
  } else {
    write(max_values[root].second);
  }

  return 0;
}
