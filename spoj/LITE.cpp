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
vector<int> Tree(4 * N);
vector<bool> isLazy(4 * N);

void propagate(int node, int l, int r)
{
	db(l, r, isLazy[node]);
	if (isLazy[node])
	{
		Tree[node] = r - l + 1 - Tree[node];
		db(l, r, Tree[node]);
		if (l != r)
		{
			isLazy[2 * node] = !isLazy[2 * node];
			isLazy[2 * node + 1] = !isLazy[2 * node + 1];
			db(isLazy[2 * node], isLazy[2 * node + 1]);
		}
		isLazy[node] = false;
	}
}

void update(int node, int start, int end, int qstart, int qend)
{
	propagate(node, start, end);
	if (start > end || qend < start || qstart > end)
		return;
	if (qstart <= start && end <= qend)
	{
		isLazy[node] = true;
		propagate(node, start, end);
		db(start, end, Tree[node]);
		return;
	}
	int mid = (start + end) / 2;
	update(2 * node, start, mid, qstart, qend);
	update(2 * node + 1, mid + 1, end, qstart, qend);
	Tree[node] = Tree[2 * node] + Tree[2 * node + 1];
}

int query(int node, int start, int end, int qstart, int qend)
{
	propagate(node, start, end);
	if (start > end || qend < start || qstart > end)
		return 0;
	if (qstart <= start && end <= qend)
	{
		db(start, end, Tree[node]);
		return Tree[node];
	}
	int mid = (start + end) / 2;
	return query(2 * node, start, mid, qstart, qend) +
		   query(2 * node + 1, mid + 1, end, qstart, qend);
}

void solve()
{
	int n, m, s, e, ch;
	cin >> n >> m;
	while (m--)
	{
		cin >> ch >> s >> e;
		if (!ch)
			update(1, 0, n - 1, s, e);
		else
			cout << query(1, 0, n - 1, s, e) << '\n';
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