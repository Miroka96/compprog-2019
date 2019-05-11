
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

struct road
{
	int a;
	int b;
};

struct node
{
	bool is_ingoing = false;
	bool is_known = false;
	vector<int> roads;
};

int
main()
{
	auto in = Input(1 << 28);

	int crossroads_count = in;
	int roads_count = in;

	struct road roads[roads_count];
	struct node nodes[crossroads_count];
	for (int i = 0; i < crossroads_count; i++) {
		nodes[i].is_known = false;
		nodes[i].is_ingoing = false;
		nodes[i].roads = {};
	}

	for (int i = 0; i < roads_count; i++)
	{
		int a = in;
		int b = in;
		a--;
		b--;
		roads[i].a = a;
		roads[i].b = b;
		nodes[a].roads.push_back(i);
		nodes[b].roads.push_back(i);
	}

	queue<pair<int, int>> bfs;
	// node, level
	bfs.push(make_pair(0, 0));
	bool ingoing = true;
	nodes[0].is_ingoing = true;
	nodes[0].is_known = true;
	int level = 0;

	while (!bfs.empty())
	{
		auto p = bfs.front();

		int recent = p.first;
		int recent_level = p.second;

		if (recent_level > level) {
			level = recent_level;
			ingoing = !ingoing;
		}

		bfs.pop();
		//printf("recent %d\n", recent);

		for (auto &road_i : nodes[recent].roads) {
			struct road &road = roads[road_i];
			
			int other_node_i = road.a == recent ? road.b : road.a;
			struct node &other_node = nodes[other_node_i];
			if (!other_node.is_known) {
				other_node.is_known = true;
				bfs.push(make_pair(other_node_i, recent_level + 1));
				other_node.is_ingoing = !ingoing;
			} else {
				if(other_node.is_ingoing == ingoing) {
					printf("impossible!\n");
					return 0;
				}
			}
		}
		
	}

	for(int i = 0; i < roads_count; i++) {
		if (nodes[roads[i].a].is_ingoing) {
			printf("0\n");
		} else {
			printf("1\n");
		}
	}
}
