// not working yet

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
