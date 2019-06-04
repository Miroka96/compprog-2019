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
#define BUFFER_SIZE 0x1000000

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
  int i = 0;
  do {
    outputbuffer[i++] = n % 10 + '0';
    n /= 10;
  } while (n);
  --i;

  while (i >= 0)
    putchar_unlocked(outputbuffer[i--]);
}

inline void print(const char *str) {
  for (const char *c = str; *c; c++) {
    putchar_unlocked(*c);
  }
}

////////////////////////////// Task ////////////////////////

struct member {
  char age;
  short skill;
  int id;
};

constexpr char min_age = 10;
constexpr char max_age = 105;
constexpr char age_span = max_age - min_age + 1;

int main(int argc, char *argv[]) {
  // disable for Angelika's Input
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

  // disable for Mirko's Input
  // auto in = Input(1 << 28);

  int members_count, contest_count;
  readn(members_count);
  readn(contest_count);

  struct member members[members_count];
  rep(i, members_count) {
    char age;
    short skill;
    readn(age);
    readn(skill);
    members[i] = member{age, skill, i + 1};
  }

  auto age_skill_cmp = [](const struct member &a, const struct member &b) {
    if (a.age != b.age) {
      return a.age < b.age;
    } else {
      return a.skill < b.skill;
    }
  };

  sort(members, members + members_count, age_skill_cmp);

  int st[max_age + 3 - min_age];
  int en[max_age + 2 - min_age];
  int *starts = st - min_age + 1;
  int *ends = en - min_age + 1;

  char age = min_age - 1;
	for (; age < members[0].age; age++) {
    ends[age] = 0;
    starts[age + 1] = 0;
  }
  for (int i = 0; i < members_count; i++) {
    if (members[i].age > age) {
      for (char j = age; j < members[i].age; j++) {
        ends[j] = i;
        starts[j + 1] = i;
      }
      age = members[i].age;
    }
  }
  for (; age <= max_age; age++) {
    ends[age] = members_count;
    starts[age + 1] = members_count;
  }

  int results[max_age + 1][max_age + 1][3];

  for (char age = min_age; age <= max_age; age++) {
    const int &start = starts[age];
    const int &end = ends[age];

    struct member recent_results[3] = {};
    for (int m = start; m < end; m++) {
      const struct member &member = members[m];
      for (int i = 0; i < 3; i++) {
        struct member &result_member = recent_results[i];
        if (member.skill > result_member.skill ||
            member.skill == result_member.skill &&
                result_member.id > member.id) {
          for (int j = 2; j > i; j--) {
            recent_results[j] = recent_results[j - 1];
          }
          result_member = member;
          break;
        }
      }
    }
    rep(i, 3) {
      if (recent_results[i].age == 0)
        break;
			// TODO this id should be the id in the sorted members list
      results[age][age][i] = recent_results[i].id;
    }
  }

  for (char diff = 1; diff < age_span; diff++) {
    for (char min = min_age; min <= max_age - diff; min++) {
      char max = min + diff;

      const int *max_results = results[min + diff][max];
      const int *min_results = results[min][max - diff];

      int min_id = 0;
      int max_id = 0;

      rep(i, 3) {
        const struct member &min_member = members[min_results[min_id]];
        const struct member &max_member = members[max_results[max_id]];

				if (min_member.id == max_member.id) {
					if (min_member.skill == 0) {
						break;
					} else {
						min_id++;
						max_id++;
						results[min+diff][max-diff][i] = min_member.id;
						continue;
					}
				}

        if (min_member.skill > max_member.skill ||
            min_member.skill == max_member.skill &&
						min_member.id < max_member.id) {
							min_id++;
							results[min+diff][max-diff][i] = min_member.id;
						} else {
							max_id++;
							results[min+diff][max-diff][i] = max_member.id;
						}
      }
    }
  }

  rep(i, contest_count) {
    char min, max;
    readn(min);
    readn(max);

		if (ends[max] - starts[min] < 3) {
			print("-1\n");
			continue;
		}

    int *contest_results = results[min][max];

    write(contest_results[0]);
    putchar_unlocked(' ');
    write(contest_results[1]);
    putchar_unlocked(' ');
    write(contest_results[2]);
    putchar_unlocked('\n');
  }

  return 0;
}
