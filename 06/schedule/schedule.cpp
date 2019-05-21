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

constexpr static int mod = 1000000007;

template <typename R, typename T>
inline R modpow(T base, T exp, const T& modulus) {
  base %= modulus;
  R result = 1;
  while (exp > 0) {
    if (exp & 1) result = (result * (R) base) % (R) modulus;
    base = (((R) base) * (R) base) % (R)modulus;
    exp >>= 1;
  }
  return result;
}

template <typename R, typename T>
inline T mulpow(const T& a, const T& b, const T& modulus) {
  return (((R) a) * ((R) b)) % ((R) modulus);
}

typedef uint64_t mul_t;

int main(int argc, char *argv[]) {
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  short week_count;
  readn(week_count);

  vector<int> faculties = {};
  faculties.push_back(1);

  while(week_count--) {
    int available_time;
    readn(available_time);

    faculties.reserve(available_time + 1);

    char task_count;
    readn(task_count);

    int times[task_count];

    int needed_time = 0;
    rep(i, task_count) {
      int t;
      readn(t);
      needed_time += t;
      times[i] = t;
    }

    int time_left = available_time - needed_time;

    int possibilities = 1;
    
    int faculty = faculties.back();
    for(int t = faculties.size(); t <= available_time; t++) {
      faculty = mulpow<mul_t>(faculty, t, mod);
      faculties.push_back(faculty);
    }

    possibilities = faculties[available_time];

    rep(i, task_count) {
      int inverse = modpow<mul_t>(faculties[times[i]], mod - 2, mod);
      possibilities = mulpow<mul_t>(possibilities, inverse, mod);
    }

    if (time_left > 1) {
      int inverse = modpow<mul_t>(faculties[time_left], mod - 2, mod);
      possibilities = mulpow<mul_t>(possibilities, inverse, mod);
    }

    write(possibilities);
  }



  return 0;
}
