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
}

inline void print(const char *str) {
  for (const char *c = str; *c; c++) {
    putchar_unlocked(*c);
  }
}

////////////////////////////// Task ////////////////////////

#define max_colour_count 50

int main(int argc, char *argv[]) {
	// disable for Angelika's Input
  setvbuf(stdin, inputbuffer, _IOFBF, BUFFER_SIZE);

	// disable for Mirko's Input
	//auto in = Input(1 << 28);

	int beads_count;
	readn(beads_count);

	// colour, count
	uint16_t edges[max_colour_count][max_colour_count] = {};

	int colour_counts[max_colour_count] = {};	

	rep(i, beads_count) {
		char a;
		char b;
		readn(a);
		readn(b);
		a--;
		b--;
		colour_counts[a]++;
		colour_counts[b]++;
		edges[a][b]++;
		edges[b][a]++;
	}

	rep(i, max_colour_count) {
		if (colour_counts[i] % 2 != 0) {
			print("beads lost\n");
			return 0;
		}
	}

	pair<char, int> result_list[beads_count+1] = {};
	int colour_pointer[max_colour_count] = {};
	fill_n(colour_pointer, max_colour_count, -1);

	rep(colour, max_colour_count) {
		if (colour_counts[colour] > 0) {
			result_list[0].first = colour;
			break;
		}
	}
	
	int recent_bracelet_end = -1;

	rep(i, beads_count) {
		auto& recent_item = result_list[i];
		auto& next_item = result_list[i+1];

		char recent_colour = recent_item.first;
		colour_pointer[recent_colour] = i;

		char next_colour = -1;

		if (edges[recent_colour][recent_colour] > 0) {
			next_colour = recent_colour;
			recent_item.second = i+1;
			next_item.first = next_colour;
		} else {
			rep(colour, max_colour_count) {
				if (edges[recent_colour][colour] > 0) {
					next_colour = colour;
					break;
				}
			}

			if (next_colour != -1) {
				recent_item.second = i+1;
				next_item.first = next_colour;
			} else {
				if (recent_bracelet_end != -1) {
					result_list[i].second = recent_bracelet_end;
				}

				recent_colour = -1;
				rep(colour, max_colour_count) {
					if (colour_counts[colour] > 0 && colour_pointer[colour] != -1) {
						recent_colour = colour;
						break;
					}
				}
				//assert(recent_colour != -1);
				if (recent_colour == -1) {
					print("beads lost\n");
					return 0;
				}

				int recent_bracelet_start = colour_pointer[recent_colour];
				auto& start_item = result_list[recent_bracelet_start];
				recent_bracelet_end = start_item.second;
				
				rep(colour, max_colour_count) {
					if (edges[recent_colour][colour] > 0) {
						next_colour = colour;
						break;
					}
				}

				next_item.first = next_colour;
				start_item.second = i+1;
			}
		}
		
		colour_counts[recent_colour]--;
		colour_counts[next_colour]--;
		edges[recent_colour][next_colour]--;
		edges[next_colour][recent_colour]--;

		recent_colour = next_colour;
	}

	if (recent_bracelet_end != -1) {
		result_list[beads_count].second = recent_bracelet_end;
	}

	int recent = 0;
	int next = result_list[recent].second;

	do {
		write(result_list[recent].first +1);
		putchar_unlocked(' ');
		write(result_list[next].first + 1);
		putchar_unlocked('\n');
		recent = next;
		next = result_list[recent].second;
	} while(next != 0);

  return 0;
}
