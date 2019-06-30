//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
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
vector<ll> Tree(4 * N), Lazy(4 * N);

void propagate(int node, int l, int r)
{
	if (Lazy[node])
	{
		Tree[node] += (r - l + 1) * Lazy[node];
		if (l != r)
		{
			Lazy[2 * node] += Lazy[node];
			Lazy[2 * node + 1] += Lazy[node];
		}
		Lazy[node] = 0;
	}
}

void add(int node, int start, int end, int qstart, int qend, int val)
{
	propagate(node, start, end);
	if (start > end || qend < start || qstart > end)
		return;
	if (qstart <= start && end <= qend)
	{
		Lazy[node] += val;
		propagate(node, start, end);
		return;
	}
	int mid = (start + end) / 2;
	add(2 * node, start, mid, qstart, qend, val);
	add(2 * node + 1, mid + 1, end, qstart, qend, val);
	Tree[node] = Tree[2 * node] + Tree[2 * node + 1];
}

ll query(int node, int start, int end, int qstart, int qend)
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
	fill(Tree.begin(), Tree.end(), 0);
	fill(Lazy.begin(), Lazy.end(), 0);
	int n, c, p, q, v, ch;
	cin >> n >> c;
	while (c--)
	{
		cin >> ch;
		switch (ch)
		{
		case 0:
			cin >> p >> q >> v;
			add(1, 0, n - 1, p - 1, q - 1, v);
			break;

		default:
			cin >> p >> q;
			cout << query(1, 0, n - 1, p - 1, q - 1) << '\n';
			break;
		}
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