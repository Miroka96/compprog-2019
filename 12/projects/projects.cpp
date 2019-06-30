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

template <typename T> inline void readn(T &x) {
  x = 0;
  register char c = getchar_unlocked();

  for (; c >= '0' && c <= '9'; c = getchar_unlocked())
    x = (x << 3) + (x << 1) + (c & 15);
  // write(x);
}

inline void print(const char *str) {
  for (const char *c = str; *c; c++) {
    putchar_unlocked(*c);
  }
}

////////////////////////////// Task ////////////////////////

struct edge {
  int8_t costs;
  short capacity;
  uint8_t to;
};

int main(int argc, char *argv[]) {
  // disable for Angelika's Input
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  // disable for Mirko's Input
  // auto in = Input(1 << 28);

  uint8_t students_count;
  readn(students_count);
  uint8_t projects_count;
  readn(projects_count);
  uint8_t priorities_count;
  readn(priorities_count);
  uint8_t students_per_project;
  readn(students_per_project);

  vector<edge> graph[students_count + projects_count] = {};

  uint8_t project_priorities[projects_count] = {};

  rep(student, students_count) {
    uint8_t student_id;
    readn(student_id);

    for (int priority = 1; priority <= priorities_count; priority++) {
      uint8_t project_id;
      readn(project_id);
      project_priorities[project_id] = priority;
      edge e;
      e.costs = priority;
      e.to = students_count + project_id;
      e.capacity = 1;
      graph[student].push_back(e);
    }

    rep(project, projects_count) {
      if (project_priorities[project] == 0) {
        edge e;
        e.costs = 2 * priorities_count;
        e.to = students_count + project;
        e.capacity = 1; // not really necessary, maybe for later
        graph[student].push_back(e);
      } else {
        project_priorities[project] = 0;
      }
    }
  }

  uint8_t project_capacities[projects_count];
  fill_n(project_capacities, projects_count, students_per_project);

  rep(student, students_count) {
    // all projects sorted by priority
    // at least one directly reaches the sink

    for (edge &project_edge : graph[student]) {
      const auto &project = project_edge.to - students_count;
      if (project_capacities[project] == 0)
        continue;
      project_capacities[project]--;
      project_edge.capacity--;

      edge e;
      e.to = student;
      e.capacity = 1;
      e.costs = -project_edge.costs;
      graph[project_edge.to].push_back(e);
      break;
    }
  }

  bool found_neg_circle;
  do {
    // lets see, which negative circles exist
    found_neg_circle = false;
    // propagate costs n-1 times
    int costs[students_count + projects_count] = {};
    rep(iteration, students_count + projects_count - 1) {
      rep(vertex, students_count + projects_count) {
        const int &recent_costs = costs[vertex];

        for (edge &child_edge : graph[vertex]) {
          if (child_edge.capacity == 0)
            continue;
          int possible_costs = recent_costs + child_edge.costs;
          if (possible_costs < costs[child_edge.to]) {
            costs[child_edge.to] = possible_costs;
          }
        }
      }
    }

    vector<uint8_t> circle_sources;
    uint8_t parents[students_count + projects_count];
    int best_costs[students_count + projects_count];
    rep(i, students_count + projects_count) {
        parents[i] = i;
        best_costs[i] = costs[i];
      }

    rep(source, students_count + projects_count) {
      // vertex, costs
      queue<pair<uint8_t, int>> bfs;
      bool seen[students_count + projects_count] = {};
      bfs.push(make_pair(source, costs[source]));

      while (!bfs.empty()) {
        const auto [parent, cost] = bfs.front();
        bfs.pop();
        if (seen[parent]) continue;
        seen[parent] = true;
        if (cost > best_costs[parent])
          continue;

        for (const edge &child_edge : graph[parent]) {
          if (child_edge.capacity == 0)
            continue;
          const int possible_costs = cost + child_edge.costs;
          const uint8_t &child = child_edge.to;
          const int &old_costs = best_costs[child];

          if (possible_costs < old_costs) {
            best_costs[child] = possible_costs;
            parents[child_edge.to] = parent;
            if (child == source) {
              // found negative circle
              found_neg_circle = true;
              circle_sources.push_back(source);
              goto next_source;
            } else {
              bfs.push(make_pair(child, possible_costs));
            }
          }
        }
      }
      next_source:;
    }

    bool seen[students_count + projects_count] = {};
    for (const uint8_t &source : circle_sources) {
      stack<uint8_t> circle;
      uint8_t circle_node = source;
      while (!seen[circle_node]) {
        seen[circle_node] = true;
        circle.push(circle_node);
        circle_node = parents[circle_node];
      }
      if (circle.size() > 1 && parents[circle.top()] == source) {
        // found circle
        uint8_t parent = source;
        while (!circle.empty()) {
          uint8_t child = circle.top();
          circle.pop();
          edge *parent_edge;
          for (edge &e : graph[parent]) {
            if (e.to != child)
              continue;
            e.capacity--;
            parent_edge = &e;
          }
          bool updated_child = false;
          for (edge &e : graph[child]) {
            if (e.to != parent)
              continue;
            e.capacity++;
            updated_child = true;
          }
          if (!updated_child) {
            edge child_edge;
            child_edge.capacity = 1;
            child_edge.to = parent;
            child_edge.costs = -parent_edge->costs;
            graph[child].push_back(child_edge);
          }
          parent = child;
        }
      }
    }
  } while (found_neg_circle);

  uint8_t student_to_project[students_count];
  int priority_sum = 0;
  rep(project, projects_count) {
    for (const edge &e : graph[project + students_count]) {
      if (e.capacity == 0)
        continue;
      student_to_project[e.to] = project;
      priority_sum -= e.costs;
    }
  }

  write(priority_sum);
  putchar_unlocked('\n');
  rep(student, students_count) {
    write(student);
    putchar_unlocked(' ');
    write(student_to_project[student]);
    putchar_unlocked('\n');
  }

  return 0;
}
