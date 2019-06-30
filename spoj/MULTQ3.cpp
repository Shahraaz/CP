//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define multitest 1
// #define Debug 1
#ifdef Debug
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__);
template <typename Arg1>
void ZZ(const char *name, Arg1 &&arg1)
{
	std::cerr << name << " = " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void ZZ(const char *names, Arg1 &&arg1, Args &&... args)
{
	const char *comma = strchr(names + 1, ',');
	std::cerr.write(names, comma - names) << " = " << arg1;
	ZZ(comma, args...);
}
#else
#define db(...)
#endif

typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
const long long mod = 1000000007;

struct Data
{
	int zero, one, two;
	Data()
	{
		zero = one = two = 0;
	}
	Data operator+(Data const &l) const
	{
		auto temp = *this;
		temp.one += l.one;
		temp.two += l.two;
		temp.zero += l.zero;
		return temp;
	}
};
vector<Data> Tree;
vector<int> Lazy;

void propagate(int node, int l, int r)
{
	if (Lazy[node])
	{
		if (l != r)
		{
			Lazy[2 * node] += Lazy[node];
			Lazy[2 * node + 1] += Lazy[node];
			Lazy[2 * node] %= 3;
			Lazy[2 * node + 1] %= 3;
		}
		Lazy[node] %= 3;
		while (Lazy[node])
		{
			int zero = Tree[node].zero;
			int one = Tree[node].one;
			int two = Tree[node].two;
			Tree[node].one = zero;
			Tree[node].two = one;
			Tree[node].zero = two;
			Lazy[node]--;
		}
	}
}

void build(int node, int start, int end)
{
	if (start == end)
	{
		Tree[node].zero = 1;
		return;
	}
	int mid = (start + end) / 2;
	build(2 * node, start, mid);
	build(2 * node + 1, mid + 1, end);
	Tree[node] = Tree[2 * node] + Tree[node * 2 + 1];
}

void update(int node, int start, int end, int qstart, int qend)
{
	propagate(node, start, end);
	if (start > end || qend < start || qstart > end)
		return;
	if (qstart <= start && end <= qend)
	{
		Lazy[node] = 1;
		propagate(node, start, end);
		return;
	}
	int mid = (start + end) / 2;
	update(2 * node, start, mid, qstart, qend);
	update(2 * node + 1, mid + 1, end, qstart, qend);
	Tree[node] = Tree[node * 2] + Tree[2 * node + 1];
}

int query(int node, int start, int end, int qstart, int qend)
{
	propagate(node, start, end);
	if (start > end || qend < start || qstart > end)
		return 0;
	if (qstart <= start && end <= qend)
		return Tree[node].zero;
	int mid = (start + end) / 2;
	return query(2 * node, start, mid, qstart, qend) +
		   query(2 * node + 1, mid + 1, end, qstart, qend);
}

void solve()
{
	int n, m, ch, a, b;
	cin >> n >> m;
	Tree.resize(4 * n + 10);
	Lazy.resize(4 * n + 10);
	build(1, 0, n - 1);
	while (m--)
	{
		cin >> ch >> a >> b;
		if (ch)
			cout << query(1, 0, n - 1, a, b) << '\n';
		else
			update(1, 0, n - 1, a, b);
	}
}

int main()
{
#ifndef Debug
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#endif
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (t--)
		solve();
	return 0;
}