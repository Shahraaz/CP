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

vector<int> lazy(16e5);

void shift(int node)
{
	db(node,lazy[node]);
	if (!lazy[node << 1])
		lazy[node << 1] = lazy[node];
	if (!lazy[(node << 1) + 1])
		lazy[(node << 1) + 1] = lazy[node];
}

void modify(int node, int start, int end, int qstart, int qend, int val)
{
	if (lazy[node])
		return;
	if (qstart > end || qend < start)
		return;
	if (qstart<=start && end <= qend)
	{
		lazy[node] = val;
		return;
	}
	int mid = (start + end) / 2;
	shift(node);
	modify(node << 1, start, mid, qstart, qend, val);
	modify((node << 1) + 1, mid + 1, end, qstart, qend, val);
}

int get(int node, int start, int end, int idx)
{
	if (idx > end || idx < start)
		return -1;
	if (start == end)
		return lazy[node];
	shift(node);
	int mid = (start + end) / 2;
	return max(get(node << 1, start, mid, idx), get((node << 1) + 1, mid + 1, end, idx));
}

void solve()
{
	int n, m, l, r, x;
	cin >> n >> m;
	while (m--)
	{
		cin >> l >> r >> x;
		--x;
		--l;
		--r;
		if (x != l)
			modify(1, 0, n - 1, l, x - 1, x + 1);
		if (x != r)
			modify(1, 0, n - 1, x + 1, r, x + 1);
	}
	// cout << (3 << 1 + 1) << '\n';
	for (int i = 0; i < n; ++i)
		cout << get(1, 0, n - 1, i) << ' ';
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