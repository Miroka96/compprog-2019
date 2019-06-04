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

struct Input
{
	char *buf;

	Input(size_t size) : buf((char *)malloc(size))
	{
		ios_base::sync_with_stdio(0);
		cin.tie(0);
		cout.precision(10);

		char *start = buf;
		int n = 0;
		do
		{
			buf += n;
			n = read(STDIN_FILENO, buf, size);
		} while (n > 0);
		assert(buf <= start + size);
		buf = start;
	}

	void skip_space()
	{
		while (*buf <= ' ')
			buf++;
	}

	operator char()
	{
		skip_space();
		return *buf++;
	}

	operator bool()
	{
		skip_space();
		return *buf++ != '0';
	}

	operator char *()
	{
		skip_space();
		char *s = buf;
		while (*buf++ > ' ')
			;
		buf[-1] = '\0';
		return s;
	}

	operator float()
	{
		return (double)*this;
	}

	operator double()
	{
		char *s = *this;
		return atof(s);
	}

	template <typename T>
	operator T()
	{
		skip_space();
		T n = 0;
		char c = *buf++;
		bool neg = c == '-';
		if (neg)
			c = *buf++;
		while (c > ' ')
		{
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

  //putchar_unlocked('\n');
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

int main(int argc, char *argv[]) {
	// disable for Angelika's Input
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

	// disable for Mirko's Input
	//auto in = Input(1 << 28);

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

	auto age_skill_cmp = [](const struct member& a, const struct member& b){
		if (a.age != b.age) {
			return a.age < b.age;
		} else {
			return a.skill < b.skill;
		}
	};

	sort(members, members + members_count, age_skill_cmp);

	auto age_cmp = [](const struct member& a, const struct member& b){
		return a.age < b.age;
	};

	auto skill_age_cmp = [](const struct member& a, const struct member& b){
		if (a.skill != b.skill) {
			return a.skill > b.skill;
		} else {
			return a.age < b.age;
		}
	};

	rep(i, contest_count) {
		char min, max;
		readn(min);
		readn(max);
		
		const auto start = lower_bound(members, members + members_count, member{min, 0, 0}, age_cmp);
		const auto end = upper_bound(start, members + members_count, member{max, 0, 0}, age_cmp);

		int results[3];

		int diff = end - start; 
		if (diff < 3) {
			write(-1);
			putchar_unlocked('\n');
			continue;
		} else {
			rep(res, 3){
				member max_member = member{0,-1,-1};
				for(auto it = start; it != end; it++) {
					if(it->skill > max_member.skill) {
						rep(j, res) {
							if (results[j] == it->id) goto iterate_members;
						} 
						max_member = *it;
					}
					iterate_members:;
				}
				results[res] = max_member.id;
			}
		}

		write(results[0]);
		putchar_unlocked(' ');
		write(results[1]);
		putchar_unlocked(' ');
		write(results[2]);
		putchar_unlocked('\n');
	}

  return 0;
}
