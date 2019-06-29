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

const int N = 1e5 + 10;

struct segmentTree
{
	int n;
	vector<int> tree, lazy;
	segmentTree(int n = 1e5 + 10) : n(n)
	{
		tree.resize(4 * n);
		lazy.resize(4 * n, -1);
	}
	void push(int l, int r, int node)
	{
		if (lazy[node] != -1)
		{
			tree[node] = (r - l + 1) * lazy[node];
			if (l != r)
				lazy[2 * node] = lazy[2 * node + 1] = lazy[node];
			lazy[node] = -1;
		}
	}
	void update(int node, int start, int end, int qstart, int qend, bool val)
	{
		push(start, end, node);
		if (start > end || qstart > end || qend < start)
			return;
		if (qstart <= start && end <= qend)
		{
			lazy[node] = val;
			push(start, end, node);
			return;
		}
		int mid = (start + end) / 2;
		update(2 * node, start, mid, qstart, qend, val);
		update(2 * node + 1, mid + 1, end, qstart, qend, val);
		tree[node] = tree[2 * node] + tree[2 * node + 1];
	}
	int query(int node, int start, int end, int qstart, int qend)
	{
		push(start, end, node);
		if (start > end || qstart > end || qend < start)
			return 0;
		if (qstart <= start && end <= qend)
			return tree[node];
		int mid = (start + end) / 2;
		return query(2 * node, start, mid, qstart, qend) +
			   query(2 * node + 1, mid + 1, end, qstart, qend);
	}
	void update(int l, int r, bool val)
	{
		update(1, 1, n, l, r, val);
	}
	int query(int l, int r)
	{
		return query(1, 1, n, l, r);
	}
};

void solve()
{
	int n, q, x, y, k;
	cin >> n >> q;
	vector<segmentTree> Tree(26, n);
	string s;
	cin >> s;
	s = " " + s;
	for (int i = 1; i <= n; ++i)
		Tree[s[i] - 'a'].update(i, i, 1);
	while (q--)
	{
		cin >> x >> y >> k;
		if (!k)
		{
			int cur = x;
			for (int i = 25; i >= 0; --i)
			{
				int cnt = Tree[i].query(x, y);
				Tree[i].update(x, y, 0);
				if (cnt > 0)
					Tree[i].update(cur, cur + cnt - 1, 1);
				cur += cnt;
			}
		}
		else
		{
			int cur = x;
			for (int i = 0; i < 26; ++i)
			{
				int cnt = Tree[i].query(x, y);
				Tree[i].update(x, y, 0);
				if (cnt > 0)
					Tree[i].update(cur, cur + cnt - 1, 1);
				cur += cnt;
			}
		}
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < 26; ++j)
			if (Tree[j].query(i, i))
			{
				cout << char(j + 'a');
				break;
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

