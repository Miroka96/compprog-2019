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

////////////////////////////// I/O /////////////////////////
#define BASE 10
#define OUTPUT_LENGTH 24
#define BUFFER_SIZE 0x10000

// buffer stdin
char inputbuffer[BUFFER_SIZE];

template <typename T> inline void readn(T &x) {
  x = 0;
  bool neg = 0;
  register char c = getchar_unlocked();

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

struct parent_state {
  uint16_t state;
  int cost;
};

struct state {
  parent_state parents[16];
};

inline uint32_t permute(uint32_t v, uint32_t bitmask) {
  uint32_t t = v | (v - 1);
  t = t & bitmask;
  uint32_t w = (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(v) + 1));
  return w;
}

inline uint32_t clean_permutation(uint32_t v, uint32_t bitmask) {
  return ~v & bitmask;
}

int main(int argc, char *argv[]) {
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  /*
    uint32_t p = 0;
    int pc = 12;
    rep(i, (1u<<12) - 1) {
      p = permute(p, 0x7);
      printf("%x\n", ~p & 0x7);
      //assert(pc - __builtin_popcount((uint32_t) p) <= 1);
      //assert(pc - __builtin_popcount((uint32_t) p) >= 0);
      pc = __builtin_popcount((uint32_t) p);
    }
    */
  char players_count;
  readn(players_count);

  uint32_t bitmask = (1 << players_count) - 1;

  int holes_count;
  readn(holes_count);

  int needed_shots[players_count][holes_count];
  rep(player, players_count) {
    rep(hole, holes_count) {
      int shots;
      readn(shots);
      needed_shots[player][hole] = shots;
    }
  }

  int hole_differences[players_count][players_count];
  rep(player, players_count) { hole_differences[player][player] = 0; }

  for (int a = 0; a < players_count - 1; a++) {
    for (int b = a + 1; b < players_count; b++) {
      int max_difference = 0; // of shots
      rep(hole, holes_count) {
        int difference = abs(needed_shots[a][hole] - needed_shots[b][hole]);
        max_difference = max(max_difference, difference);
      }
      hole_differences[a][b] = max_difference;
      hole_differences[b][a] = max_difference;
    }
  }

  int new_hole_differences[players_count]
                          [players_count]; // b starts a new hole --> offset of
                                           // 1 between a and b

  rep(a, players_count) {
    rep(b, players_count) {
      if (a == b) {
        new_hole_differences[a][b] = 0;
        continue;
      }
      int max_difference = 0; // of shots
      rep(hole, holes_count - 1) {
        int difference = abs(needed_shots[a][hole] - needed_shots[b][hole + 1]);
        max_difference = max(max_difference, difference);
      }
      new_hole_differences[a][b] = max_difference;
    }
  }

  vector<int> costs;
  rep(final_player, players_count) {

    state best_parent_states[2 << (players_count - 1)];
    for (state &s : best_parent_states) {
      for (parent_state &p : s.parents) {
        p.state = -1;
        p.cost = -1;
      }
    }

    rep(first_player, players_count) {
      best_parent_states[first_player + 1].parents[first_player].cost =
          new_hole_differences[final_player][first_player];
    }

    uint32_t perm = 0;
    rep(i, players_count) { perm = permute(perm, bitmask); }
    do {
      perm = permute(perm, bitmask);
      uint32_t permutation = clean_permutation(perm, bitmask);

      state &current_state = best_parent_states[permutation];
      for (uint32_t current_mask = 1, current_player = 0;
           current_player < players_count;
           current_mask <<= 1, current_player++) {
        if ((permutation & current_mask) == 0) {
          continue;
        }

        uint16_t previous_permutation = permutation ^ current_mask;
        state &previous_state = best_parent_states[previous_permutation];

        int best_cost = INT32_MAX;
        uint16_t best_previous_player = -1;
        for (uint16_t previous_mask = 1, previous_player = 0;
             previous_player < players_count;
             previous_mask <<= 1, previous_player++) {
          if ((previous_permutation & previous_mask) == 0) {
            continue;
          }
          int possible_cost =
              max(previous_state.parents[previous_player].cost,
                  hole_differences[previous_player][current_player]);
          if (possible_cost < best_cost) {
            best_cost = possible_cost;
            best_previous_player = previous_player;
          }
        }
        current_state.parents[current_player].state = previous_permutation;
        if (best_previous_player != (uint16_t)-1) {
          current_state.parents[current_player].cost = best_cost;
        }
      }
    } while (clean_permutation(perm, bitmask) != bitmask);

    if (holes_count == 1) {
      for (parent_state p : best_parent_states[bitmask].parents) {
        if (p.state == (uint16_t)-1) {
          continue;
        }
        costs.push_back(p.cost);
      }
      break;
    } else {
      costs.push_back(best_parent_states[bitmask].parents[final_player].cost);
    }
  }

  int best_cost = INT32_MAX;
  for (int cost : costs) {
    best_cost = min(best_cost, cost);
  }
  write(best_cost);

  return 0;
}
