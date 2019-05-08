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
#define BUFFER_SIZE 0x100000

// buffer stdin
char inputbuffer[BUFFER_SIZE];

template <typename T> inline void readn(T &x) {
  x = 0;
  register T c = getchar_unlocked();

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
}

inline void print(const char *str) {
  for (const char *c = str; *c; c++) {
    putchar_unlocked(*c);
  }
}

////////////////////////////// Task ////////////////////////

int main(int argc, char *argv[]) {
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  int topics_count, dependency_count;
  readn(topics_count);
  readn(dependency_count);

  int difficulties[topics_count];
  int dependencies[topics_count] = {};
  vector<int> enables[topics_count] {};

  rep(i, topics_count) {
    int difficulty;
    readn(difficulty);
    difficulties[i] = difficulty;
  }

  while(dependency_count--) {
    int from, to;
    readn(from);
    readn(to);
    from--;
    to--;
    enables[from].push_back(to);
    dependencies[to] += 1;
  }

  auto cmp = [](const pair<int, int> &a, const pair<int, int> &b) {
    return a.first > b.first;
  };

  // difficulty, topic
  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> least_difficult(cmp);

  rep(i, topics_count) {
    if (dependencies[i] > 0) continue;
    least_difficult.push(make_pair(difficulties[i], i));
  }

  rep(i, topics_count) {
    int diff, topic;
    tie(diff, topic) = least_difficult.top();
    least_difficult.pop();

    write(topic + 1);
    putchar_unlocked(' ');

    for(const auto &dependent : enables[topic]) {
      dependencies[dependent]--;
      if (dependencies[dependent] == 0) {
        least_difficult.push(make_pair(difficulties[dependent], dependent));
      }
    }
  }
  putchar_unlocked('\n');
  
  return 0;
}
