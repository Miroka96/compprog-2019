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

  int notes_count;
  readn(notes_count);

  bool possible_notes[notes_count][88] = {};

  rep(i, notes_count) {
    char note;
    readn(note);

    possible_notes[i][note-1] = true;
  }

  char wanted_notes[notes_count];
  bool achieved_notes[notes_count];

  int missing_notes = 0;

  rep(i, notes_count) {
    char note;
    readn(note);
    wanted_notes[i] = note;

    if (possible_notes[i][note-1]) {
      achieved_notes[i] = true;
    } else {
      achieved_notes[i] = false;
      missing_notes++;
    }
  }

  queue<pair<int, char>> changes;

  for(int i = 1; i < notes_count - 1; i++) {
    for (char left_note = 1; left_note <= 88; left_note++) {
      if (!possible_notes[i - 1][left_note - 1]) continue;

      for (char right_note = 1; right_note <= 88; right_note++) {
        if (!possible_notes[i + 1][right_note - 1]) continue;

        unsigned char outer_sum = left_note + right_note;
        for (char inner_note = 1; inner_note <= 88; inner_note++) {
          if (!possible_notes[i][inner_note - 1]) continue;

          char sum = outer_sum - inner_note;
          if (sum < 1 || sum > 88) continue;

          if (!possible_notes[i][sum-1]) {
            possible_notes[i][sum-1] = true;

            if(!achieved_notes[i] && sum == wanted_notes[i]) {
              achieved_notes[i] = true;
              missing_notes--;
              if (missing_notes == 0) {
                print("Yes\n");
                return 0;
              }
            }

            changes.push(make_pair(i, sum));
          }
        } 
      }
    }
  }


  do {
    int position = changes.front().first;
    char note = changes.front().second;
    changes.pop();

    if (position > 1) {
      for (char left_note = 1; left_note <= 88; left_note++) {
        if (!possible_notes[position - 2][left_note - 1]) continue;

        unsigned char outer_sum = left_note + note;
        for (char inner_note = 1; inner_note <= 88; inner_note++) {
          if (!possible_notes[position - 1][inner_note - 1]) continue;

          char sum = outer_sum - inner_note;
          if (sum < 1 || sum > 88) continue;

          if (!possible_notes[position - 1][sum-1]) {
            possible_notes[position - 1][sum-1] = true;

            if(!achieved_notes[position-1] && sum == wanted_notes[position-1]) {
              achieved_notes[position-1] = true;
              missing_notes--;
              if (missing_notes == 0) {
                print("Yes\n");
                return 0;
              }
            }

            changes.push(make_pair(position - 1, sum));
          }
        } 
      }
    }
    
    if (position < notes_count - 2) {
      for (char right_note = 1; right_note <= 88; right_note++) {
        if (!possible_notes[position + 2][right_note - 1]) continue;

        unsigned char outer_sum = right_note + note;
        for (char inner_note = 1; inner_note <= 88; inner_note++) {
          if (!possible_notes[position + 1][inner_note - 1]) continue;

          char sum = outer_sum - inner_note;
          if (sum < 1 || sum > 88) continue;

          if (!possible_notes[position + 1][sum-1]) {
            possible_notes[position + 1][sum-1] = true;

            if(!achieved_notes[position+1] && sum == wanted_notes[position+1]) {
              achieved_notes[position+1] = true;
              missing_notes--;
              if (missing_notes == 0) {
                print("Yes\n");
                return 0;
              }
            }

            changes.push(make_pair(position + 1, sum));
          }
        } 
      }
    }
  } while(!changes.empty());

  print("No\n");

  return 0;
}
