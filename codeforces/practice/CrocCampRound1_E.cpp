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
vector<int> a(N), b(N), lazyVal(4 * N);
vector<bool> isLazy(4 * N);

void propagate(int node)
{
	if (isLazy[node])
	{
		isLazy[node * 2] = isLazy[node * 2 + 1] = true;
		isLazy[node] = false;
		lazyVal[node * 2] = lazyVal[node * 2 + 1] = lazyVal[node];
	}
}

void update(int node, int start, int end, int qstart, int qend, int val)
{
	if (start > end || qend < start || qstart > end)
		return;
	if (qstart <= start && end <= qend)
	{
		isLazy[node] = true;
		lazyVal[node] = val;
		return;
	}
	propagate(node);
	int mid = (start + end) / 2;
	update(2 * node, start, mid, qstart, qend, val);
	update(2 * node + 1, mid + 1, end, qstart, qend, val);
}

int query(int node, int start, int end, int pos)
{
	if (start == end)
		return lazyVal[node];
	propagate(node);
	int mid = (start + end) / 2;
	if (pos <= mid)
		return query(2 * node, start, mid, pos);
	return query(2 * node + 1, mid + 1, end, pos);
}

void solve()
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	for (int i = 1; i <= n; ++i)
		cin >> b[i];
	update(1, 1, n, 1, n, mod);
	int q, x, y, k, type;
	while (m--)
	{
		cin >> type;
		switch (type)
		{
		case 1:
			cin >> x >> y >> k;
			update(1, 1, n, y, y + k - 1, x - y);
			break;

		default:
			cin >> x;
			q = query(1, 1, n, x);
			if (q == mod)
				cout << b[x] << '\n';
			else
				cout << a[q + x] << '\n';
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