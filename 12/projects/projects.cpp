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

using namespace std;

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
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  uint8_t students_count;
  readn(students_count);
  uint8_t projects_count;
  readn(projects_count);
  uint8_t priorities_count;
  readn(priorities_count);
  uint8_t students_per_project;
  readn(students_per_project);

  const uint8_t node_count = students_count + projects_count;

  vector<edge> graph[node_count] = {};

  uint8_t project_priorities[projects_count];
  uninitialized_fill_n(project_priorities, projects_count, 0);

  // read student priorities
  rep(student, students_count) {
    uint8_t student_id;
    readn(student_id);

    for (int priority = 1; priority <= priorities_count; priority++) {
      uint8_t project_id; // 0-initialized
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
  uninitialized_fill_n(project_capacities, projects_count,
                       students_per_project);

  // choose for all students the first available project, going through the
  // projects in decreasing priority (increasing costs)
  rep(student, students_count) {
    // all projects sorted by priority
    // at least one directly reaches the sink

    for (edge &project_edge : graph[student]) {
      const auto &project = project_edge.to - students_count;
      if (project_capacities[project] == 0)
        continue;
      project_capacities[project]--;
      project_edge.capacity--;

      // add reverse edge
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
    int costs[node_count];
    uninitialized_fill_n(costs, node_count, 0);

    uint8_t last_decreased_vertex;
    uint8_t parents[node_count];
    uninitialized_fill_n(parents, node_count, 255);
    rep(iteration, node_count) {
      last_decreased_vertex = 255;
      rep(vertex, node_count) {
        const int &recent_costs = costs[vertex];
        for (edge &child_edge : graph[vertex]) {
          if (child_edge.capacity == 0)
            continue;
          const int possible_costs = recent_costs + child_edge.costs;
          if (possible_costs < costs[child_edge.to]) {
            costs[child_edge.to] = possible_costs;
            last_decreased_vertex = child_edge.to;
            parents[child_edge.to] = vertex;
          }
        }
      }
    }

    if (last_decreased_vertex != 255) {
      found_neg_circle = true;

      uint8_t vertex_on_circle = last_decreased_vertex;
      rep(i, node_count) { vertex_on_circle = parents[vertex_on_circle]; }

      vector<uint8_t> circle;
      for (uint8_t vertex = vertex_on_circle;
           vertex != vertex_on_circle || circle.size() == 0;
           vertex = parents[vertex]) {
        circle.push_back(vertex);
      }

      uint8_t child = circle[circle.size() - 1];
      for(uint8_t parent : circle) {
        edge *child_edge;
        for (edge &e : graph[parent]) {
          if (e.to != child)
            continue;
          e.capacity--;
          child_edge = &e;
          break;
        }
        bool updated_child = false;
        for (edge &e : graph[child]) {
          if (e.to != parent)
            continue;
          e.capacity++;
          updated_child = true;
          break;
        }
        if (!updated_child) {
          edge parent_edge;
          parent_edge.capacity = 1;
          parent_edge.to = parent;
          parent_edge.costs = -child_edge->costs;
          graph[child].push_back(parent_edge);
        }
        child = parent;
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
