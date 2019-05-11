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

uint64_t prices[1000001];

int main()
{
	auto in = Input(1 << 28);

	int t = in; // length
	int k = in; // angebote

	vector<pair<int, uint32_t>> angebote;
	angebote.reserve(k);

	for (int i = 0; i < k; i++)
	{
		int m = in;
		uint32_t p = in;

		angebote.push_back(make_pair(m, p));

		if (m <= t)
		{
			prices[m] = p;
		}
	}

	for (int i = 0; i <= t; i++)
	{
		uint64_t min = prices[i];
		for (const auto [length, price] : angebote)
		{
			if (i < length) continue;
			uint64_t possible_price = prices[i - length] + price;
			if (min < possible_price)
			{
				min = possible_price;
			}
		}
		prices[i] = min;
	}
	printf("%llu\n", prices[t]);
}