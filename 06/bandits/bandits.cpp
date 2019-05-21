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

  //putchar_unlocked('\n');
}

inline void print(const char *str) {
  for (const char *c = str; *c; c++) {
    putchar_unlocked(*c);
  }
}

////////////////////////////// Task ////////////////////////

constexpr static int mod = 1000000007;

typedef uint64_t mul_t;

template <typename R = mul_t, typename T>
inline R modpow(T base, T exp, const T& modulus = mod) {
  base %= modulus;
  R result = 1;
  while (exp > 0) {
    if (exp & 1) result = (result * (R) base) % (R) modulus;
    base = (((R) base) * (R) base) % (R)modulus;
    exp >>= 1;
  }
  return result;
}

int main(int argc, char *argv[]) {
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  int towns_count;
  readn(towns_count);

  int days_count;
  readn(days_count);
  
  vector<int> neighbors[towns_count] = {};

  rep(i, towns_count-1) {
    int from, to;
    readn(from);
    readn(to);
    from--;
    to--;
    bool safe = getchar_unlocked() == '0';
    getchar_unlocked();

    if (safe) {
      neighbors[from].push_back(to);
      neighbors[to].push_back(from);
    }
  }

  bool seen[towns_count] = {};
  vector<int> subtree_sizes;
  subtree_sizes.reserve(64);

  vector<int> stack;
  stack.reserve(towns_count/2);

  rep(i, towns_count) {
    if (seen[i]) continue;
    seen[i] = true;

    int subtree_size = 1;
    stack.push_back(i);
    while(!stack.empty()) {
      int parent = stack.back();
      stack.pop_back();

      for(const auto& child : neighbors[parent]) {
        if (seen[child]) continue;
        seen[child] = true;
        subtree_size++;
        stack.push_back(child);
      }
    }
    subtree_sizes.push_back(subtree_size);
  }

  int all_journeys = modpow(towns_count, days_count);

  int safe_journeys = 0;

  for(const auto& subtree : subtree_sizes) {
    safe_journeys += modpow(subtree, days_count);
    safe_journeys %= mod;
  }

  int dangerous_journeys = all_journeys - safe_journeys;
  if (dangerous_journeys < 0) dangerous_journeys += mod;

  write(dangerous_journeys);

  return 0;
}
