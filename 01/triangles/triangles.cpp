#include <bits/stdc++.h>

////////////////////////////// Helper //////////////////////

// disable debugging for submission
#define debug(x) x
// print value of debug variable
//#define debug(x)    clog << #x << " = " << x << endl

// print a debug string
#define debugs(str) clog << str << endl
#define rep(a, b) for (int a = 0; a < (b); ++a)
#define repd(a, b) for (int a = 0; a < (b); debug(++a))
#define all(a) (a).begin(), (a).end()

#define uint unsigned int
#define ulong unsigned long

using namespace std;

////////////////////////////// I/O /////////////////////////
#define BASE 10
#define OUTPUT_LENGTH 24
#define BUFFER_SIZE 1024

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

  putchar_unlocked('\n');
}

////////////////////////////// Task ////////////////////////

int main(int argc, char *argv[]) {
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  short triplesc;
  readn(triplesc);

  unordered_map<ulong, short> number_indices;
  number_indices.reserve(triplesc);

  short count = 0;
  vector<pair<ulong, short>> number_counts;
  number_counts.reserve(triplesc);

  rep(in, triplesc) {
    ulong input;
    readn(input);

    short &stored_val = number_indices[input];
    if (stored_val == 0) {
      stored_val = ++count;
      number_counts.push_back(make_pair(input, 1));
    } else {
      number_counts[stored_val - 1].second++;
    }
  }

  auto cmp = [](const pair<ulong, short> &a, const pair<ulong, short> &b) {
    return a.first < b.first;
  };
  sort(number_counts.begin(), number_counts.end(), cmp);

  ulong resultCount = 0;

  for (auto itsum = number_counts.begin(); itsum != number_counts.end();
       itsum++) {
    auto itfirst = number_counts.begin();
    auto itsecond = make_reverse_iterator(itsum)++;

    const auto sum = itsum->first;
    const auto sumc = itsum->second;

    while (itfirst->first < itsecond->first) {
      ulong possible_sum = itfirst->first + itsecond->first;
      if (possible_sum == sum) {
        resultCount += ((ulong)itfirst->second) * itsecond->second * sumc;
        itsecond++;
        itfirst++;
      } else if (possible_sum > sum) {
        itsecond++;
      } else if (possible_sum < sum) {
        itfirst++;
      }
    }
    if (sum == itfirst->first * 2 && itfirst->first == itsecond->first &&
        itfirst->second > 1) {
      resultCount +=
          ((ulong)itfirst->second) * (itfirst->second - 1) / 2 * sumc;
    }
  }

  write(resultCount);

  return 0;
}
