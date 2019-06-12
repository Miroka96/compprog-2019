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
  register char c = getchar_unlocked();

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

template <typename T, typename P = int> struct BTNode {
  T key;
  P value;
  P left;
  P right;
  P size;
  P max_value;

  static inline BTNode<T, P> makeBTNode(T k, P val = 0) {
    return {k, val, -1, -1, 1, val};
  }

  // added, updated
  tuple<bool, bool> insert(vector<BTNode<T, P>> &tree, const T &k,
                           const P &val) {
    bool added = false;
    bool updated = false;
    if (key == k) {
      if (val > max_value) {
        max_value = val;
        updated = true;
      }
    } else if (k < key) {
      if (left != -1) {
        tie(added, updated) = tree[left].insert(tree, k, val);
        if (added) {
          size++;
          if (updated) {
            max_value = max(max_value, val);
          }
        }
      } else {
        left = tree.size();
        tree.push_back(makeBTNode(k, val));
        if (val > max_value) {
          max_value = val;
          updated = true;
        }
        size++;
        added = true;
      }
    } else {
      if (right != -1) {
        tie(added, updated) = tree[right].insert(tree, k, val);
        if (added) {
          size++;
          if (updated) {
            max_value = max(max_value, val);
          }
        }
      } else {
        right = tree.size();
        tree.push_back(makeBTNode(k, val));
        if (val > max_value) {
          max_value = val;
          updated = true;
        }
        size++;
        added = true;
      }
    }
    return make_tuple(added, updated);
  }

  P values_below(vector<BTNode<T, P>> &tree, const T &k) {
    if (key < k) {
      P left_size = 0;
      if (left != -1) {
        left_size = tree[left].size;
      }
      P right_size = 0;
      if (right != -1) {
        right_size = tree[right].values_below(tree, k);
      }

      return left_size + 1 + right_size;
    } else {
      if (left != -1) {
        return tree[left].values_below(tree, k);
      } else {
        return 0;
      }
    }
  }

  P max_below(vector<BTNode<T, P>> &tree, const T &k) {
    if (key < k) {
      P m = 1;
      if (left != -1) {
        m += tree[left].max_value;
      }
      if (right != -1) {
        m += tree[right].max_below(tree, k);
      }
      return max(m, value);
    } else {
      if (left != -1) {
        return tree[left].max_below(tree, k);
      } else {
        return 0;
      }
    }
  }

  P max_above(vector<BTNode<T, P>> &tree, const T &k) {
    if (k < key) {
      P m = 1;
      if (left != -1) {
        m += tree[left].max_above(tree, k);
      }
      if (right != -1) {
        m += tree[right].max_value;
      }
      return max(m, value);
    } else {
      if (right != -1) {
        return tree[right].max_above(tree, k);
      } else {
        return 0;
      }
    }
  }
};

int main(int argc, char *argv[]) {
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);
  // disable for Mirko's Input
  // auto in = Input(1 << 28);

  char snippets_count;
  readn(snippets_count);

  rep(snippet, snippets_count) {
    short values_count;
    readn(values_count);

    vector<BTNode<uint, short>> left_tree;
    left_tree.reserve(values_count);
    vector<BTNode<uint, short>> right_tree;
    right_tree.reserve(values_count);

    // below, above
    pair<short, short> max_amounts[values_count];

    uint values[values_count];
    uint value;
    readn(value);
    values[0] = value;
    left_tree.push_back(BTNode<uint, short>::makeBTNode(value));
    max_amounts[0].first = 0;

    for (int i = 1; i < values_count; i++) {
      readn(value);
      values[i] = value;

      short max_below = left_tree[0].max_below(left_tree, value);
      max_amounts[i].first = max_below;
      left_tree[0].insert(left_tree, value, max_below);
    }

    right_tree.push_back(BTNode<uint, short>::makeBTNode(values[values_count - 1]));
    max_amounts[values_count - 1].second = 0;

    for (int i = values_count - 2; i >= 0; i--) {
      
      short max_above = right_tree[0].max_above(right_tree, values[i]);
      max_amounts[i].second = max_above;
      right_tree[0].insert(right_tree, values[i], max_above);
    }

    short max_amount = 0;
    rep(i, values_count) {
      short amount = max_amounts[i].first + max_amounts[i].second + 1;
      if (amount > max_amount) {
        max_amount = amount;
      }
    }

    write(max_amount);
  }

  return 0;
}
