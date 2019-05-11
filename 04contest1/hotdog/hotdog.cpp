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

	int t = in; // length
	int k = in; // angebote

	uint64_t prices[t + 1];
	for (int i = 0; i < t + 1; i++)
	{
		prices[i] = 0;
	}

	pair<int, uint64_t> angebote[k];

	for (int i = 0; i < k; i++)
	{
		int m = in;
		uint64_t p = in;

		angebote[i] = make_pair(m, p);

		if (m <= t)
		{
			prices[m] = p;
		}
	}

	//auto cmp = [](const pair<int, uint64_t> &p, const pair<int, uint64_t> &q) { return p.first < q.first; };

	// length, price
	//sort(angebote, angebote + k, cmp);

	for (int i = 0; i <= t; i++)
	{
		for (int j = 0; j < k; j++)
		{
			if (i < angebote[j].first) continue;
			uint64_t possible_price = prices[i - angebote[j].first] + angebote[j].second;
			if (prices[i] < possible_price)
			{
				prices[i] = possible_price;
			}
		}
	}
	printf("%llu\n", prices[t]);
}