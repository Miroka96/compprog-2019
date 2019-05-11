
#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

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

int main()
{
	auto in = Input(1 << 28);

	int n = in;

	pair<int, bool> times[2*n];

	auto cmp = [](pair<int, bool> &a, pair<int, bool> &b) { 
		if (a.first < b.first) {
			return true;
		} else {
			if (a.first == b.first) {
				if (a.second && !b.second) {
					return true;
				} else if (!a.second && b.second) {
					return false;
				} else {
					return false;
				}
			} else {
				return false;
			}
		}
	};

	for (int i = 0; i < 2*n; i+= 2)
	{
		int begin = in;
		int end = in;
		times[i] = make_pair(begin, true);
		times[i+1] = make_pair(end, false);
	}

	sort(times, times + 2*n, cmp);

	int max = 0;
	int places = 0;

	for (int j = 0; j < 2 * n; j++) {
		if (times[j].second) {
			places++;
			if (places > max) {
				max = places;
			}
		} else {
			places--;
		}
	}

	printf("%d\n", max);
}
