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
vector<ll> Tree(4 * N), extMul(4 * N, 1), extAdd(4 * N);
vector<bool> isLazy(4 * N);
vector<ll> a;

void build(int node, int start, int end)
{
	if (start == end)
	{
		Tree[node] = a[start];
		return;
	}
	int mid = (start + end) / 2;
	build(2 * node, start, mid);
	build(2 * node + 1, mid + 1, end);
	Tree[node] = (Tree[node * 2] + Tree[node * 2 + 1]) % mod;
}

void propagate(int node, int start, int end)
{
	if (isLazy[node])
	{
		Tree[node] = (Tree[node] * extMul[node] + (end - start + 1) * extAdd[node]) % mod;
		if (start != end)
		{
			isLazy[2 * node] = true;
			isLazy[2 * node + 1] = true;
			extMul[2 * node] = (extMul[2 * node] * extMul[node]) % mod;
			extAdd[2 * node] = ((extAdd[2 * node] * extMul[node]) % mod + extAdd[node]) % mod;
			extMul[2 * node + 1] = (extMul[2 * node + 1] * extMul[node]) % mod;
			extAdd[2 * node + 1] = ((extAdd[2 * node + 1] * extMul[node]) % mod + extAdd[node]) % mod;
		}
		extMul[node] = 1;
		extAdd[node] = 0;
		isLazy[node] = false;
	}
}

void add(int node, int start, int end, int qstart, int qend, int v)
{
	propagate(node, start, end);
	if (start > end || qstart > end || qend < start)
		return;
	if (qstart <= start && end <= qend)
	{
		isLazy[node] = true;
		extAdd[node] = v;
		propagate(node, start, end);
		return;
	}
	int mid = (start + end) / 2;
	add(2 * node, start, mid, qstart, qend, v);
	add(2 * node + 1, mid + 1, end, qstart, qend, v);
	Tree[node] = (Tree[2 * node] + Tree[2 * node + 1]) % mod;
}

void mul(int node, int start, int end, int qstart, int qend, int v)
{
	propagate(node, start, end);
	if (start > end || qstart > end || qend < start)
		return;
	if (qstart <= start && end <= qend)
	{
		isLazy[node] = true;
		extMul[node] = v;
		propagate(node, start, end);
		return;
	}
	int mid = (start + end) / 2;
	mul(2 * node, start, mid, qstart, qend, v);
	mul(2 * node + 1, mid + 1, end, qstart, qend, v);
	Tree[node] = (Tree[2 * node] + Tree[2 * node + 1]) % mod;
}

void equate(int node, int start, int end, int qstart, int qend, int v)
{
	propagate(node, start, end);
	if (start > end || qstart > end || qend < start)
		return;
	if (qstart <= start && end <= qend)
	{
		isLazy[node] = true;
		extMul[node] = 0;
		extAdd[node] = v;
		propagate(node, start, end);
		return;
	}
	int mid = (start + end) / 2;
	equate(2 * node, start, mid, qstart, qend, v);
	equate(2 * node + 1, mid + 1, end, qstart, qend, v);
	Tree[node] = (Tree[2 * node] + Tree[2 * node + 1]) % mod;
}

int query(int node, int start, int end, int qstart, int qend)
{
	propagate(node, start, end);
	if (start > end || qstart > end || qend < start)
		return 0;
	if (qstart <= start && end <= qend)
		return Tree[node];
	int mid = (start + end) / 2;
	return (query(2 * node, start, mid, qstart, qend) +
			query(2 * node + 1, mid + 1, end, qstart, qend)) %
		   mod;
}

void solve()
{
	int n, q, type, x, y, v;
	cin >> n >> q;
	a.resize(n);
	for (auto &x : a)
		cin >> x;
	build(1, 0, n - 1);
	while (q--)
	{
		cin >> type >> x >> y;
		switch (type)
		{
		case 1:
			cin >> v;
			add(1, 0, n - 1, x - 1, y - 1, v);
			break;

		case 2:
			cin >> v;
			mul(1, 0, n - 1, x - 1, y - 1, v);
			break;

		case 3:
			cin >> v;
			equate(1, 0, n - 1, x - 1, y - 1, v);
			break;

		case 4:
			cout << query(1, 0, n - 1, x - 1, y - 1) << '\n';
			break;

		default:
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