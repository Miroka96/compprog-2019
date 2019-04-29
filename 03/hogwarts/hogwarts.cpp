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
  T c = getchar_unlocked();

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

typedef struct ASCIINode ASCIINode;

#define PRINTABLE_ASCII_COUNT 95
#define INVALID_VALUE -1

// printable ascii characters: 32-126 => 95 (PRINTABLE_ASCII_COUNT)
vector<char> string_values;
vector<ASCIINode> ascii_nodes;

inline int append_string(char str[]) {
  int ret = string_values.size();
  
  for(int i = 0; str[i]; i++) {
    string_values.push_back(str[i]);
  }
  string_values.push_back(0);
  return ret;
}

inline bool strings_equal(int idx, const char str[]) {
  int i;
  for (i = 0; str[i] && string_values[idx]; idx++, i++) {
    if (str[i] != string_values[idx]) return false;
  }
  return str[i] == string_values[idx];
}

struct ASCIINode {
  int value; // look up in string_values vector
  int* children; // size=95; look up in ascii_nodes vector
};

int make_ascii_node() {
  ascii_nodes.push_back(ASCIINode{INVALID_VALUE, 0});
  return ascii_nodes.size() - 1;
}

inline bool has_children(const ASCIINode& node) {
  return node.children == nullptr;
}

inline bool has_children(const ASCIINode* node) {
  return node->children == nullptr;
}

inline bool has_value(const ASCIINode* node) {
  return node->value == INVALID_VALUE;
}

inline bool has_value(const ASCIINode& node) {
  return node.value == INVALID_VALUE;
}

inline void make_children(ASCIINode* node) {
  node->children = new int[PRINTABLE_ASCII_COUNT];
}

inline void make_children(ASCIINode& node) {
  node.children = new int[PRINTABLE_ASCII_COUNT];
}

inline ASCIINode* get_node(int idx) {
  if (idx) return &ascii_nodes[idx];
  return 0;
}

inline int get_child(const ASCIINode* parent, char c) {
  return parent->children[c-' '];
}

inline int get_child(const ASCIINode& parent, char c) {
  return parent.children[c-' '];
}

inline int make_child(ASCIINode* parent, char c) {
  return parent->children[c-' '] = make_ascii_node();
}

inline int make_child(ASCIINode& parent, char c) {
  return parent.children[c-' '] = make_ascii_node();
}

ASCIINode* root = get_node(make_ascii_node());

int string_to_int(char str[]) {
  ASCIINode* recent = root;
  int last_index = 0;

  for(int i = 0; str[i]; i++) {
    if (has_value(recent) && strings_equal(recent->value + i, str + i)) {
      return last_index;
    }

    if (!has_children(recent)) {
      if (!has_value(recent)) {
        return recent->value = append_string(str);
      } else {
        make_children(recent);

        if (string_values[recent->value + i]) {
          // value must be moved down
          get_node(make_child(recent, string_values[recent->value + i]))->value = recent->value;
          recent->value = INVALID_VALUE;
        }
      }
    }
    // now definitely have children

    // traverse into child
    int child_i = get_child(recent, str[i]);
    if (!child_i) {
      child_i = make_child(recent, str[i]);
    }
    last_index = child_i;
    recent = get_node(child_i);
  }
  return recent->value = append_string(str);
}

int main(int argc, char *argv[]) {
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);


  write(string_to_int("abcde"));
  write(string_to_int("abcde"));
  write(string_to_int("abcde"));

  return 0;
}
