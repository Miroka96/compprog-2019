
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

struct node
{
	int begin;
	int end;
};

int main()
{
	auto in = Input(1 << 28);

	int n = in;

	node nodeArray[n];

	auto cmp = [](node a, node b) { return a.begin < b.begin; };

	for (int i = 0; i < n; i++)
	{
		nodeArray[i].begin = in;
		nodeArray[i].end = in;
	}

	sort(nodeArray, nodeArray + n, cmp);

	// for (int i = 0; i < n; i++)
	// {
	// 	printf("begin: %d end: %d\n", nodeArray[i].begin, nodeArray[i].end);
	// }

	// map<int, int> raumMap = {};

	// auto raum = vector<int>(1, nodeArray[0].end);

	// priority_queue<int> pq; 
	priority_queue<int, std::vector<int>, std::greater<int> > pq;

	pq.push(nodeArray[0].end);
	// printf("%lu\n", pq.size());

	// nodeArray[0].k = 0;
	// raumMap[0] = nodeArray[0].end;
	// raum[0] = nodeArray[0].end;

	for (int j = 1; j < n; j++) {
		if(pq.top() < nodeArray[j].begin) {
			pq.pop();
		}
		pq.push(nodeArray[j].end);
	}

	printf("%lu\n", pq.size());


	// for (int j = 1; j < n; j++)
	// {
	// 	bool gefunden = false;

	// 	// printf("size: %lu\n", raumMap.size());
	// 	for (int i = 0; i < raum.size(); i++)
	// 	{
	// 		printf("if: %d > %d\n", nodeArray[j].begin, raum[i]);
	// 		if (nodeArray[j].begin > raum[i])
	// 		{
	// 			raum[i] = nodeArray[j].end;
	// 			gefunden = true;
	// 			break;
	// 		}
	// 	}

	// 	if (!gefunden)
	// 	{
	// 		raum.push_back(nodeArray[j].end);
	// 		// raum[raum.size()] = nodeArray[j].end;
	// 	}
	// }

	// // printf("\n");
	// printf("%lu\n", raum.size());
}
