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

vector<vector<int>> Tree(2, vector<int>(4e6 + 10));

void update(bool ch, int node, int start, int end, int pos, int dx)
{
	// db(start, end);
	if (start == end)
	{
		Tree[ch][node] += dx;
		// db(ch, node, Tree[ch][node], pos);
		return;
	}
	int mid = (start + end) / 2;
	if (pos <= mid)
		update(ch, 2 * node, start, mid, pos, dx);
	else
		update(ch, 2 * node + 1, mid + 1, end, pos, dx);
	Tree[ch][node] = Tree[ch][2 * node] + Tree[ch][2 * node + 1];
	// db(ch, node, Tree[ch][node]);
}

int query(bool ch, int node, int start, int end, int qstart, int qend)
{
	if (qstart > qend)
		return 0;
	// db(ch, node, start, end, qstart, qend);
	if (qend < start || qstart > end)
		return 0;
	if (qstart <= start && end <= qend)
	{
		int ret = Tree[ch][node];
		// db(ch, node, ret, "UPD");
		return ret;
	}
	int mid = (start + end) / 2;
	int ret = query(ch, 2 * node, start, mid, qstart, qend) + query(ch, 1 + 2 * node, mid + 1, end, qstart, qend);
	// db(ch, node, start, end, qstart, qend, ret);
	return ret;
}

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &x : a)
		cin >> x;
	vector<int> tot = a;
	sort(tot.begin(), tot.end());
	tot.erase(unique(tot.begin(), tot.end()), tot.end());
	for (int i = 0; i < n; ++i)
	{
		a[i] = lower_bound(tot.begin(), tot.end(), a[i]) - tot.begin();
		update(1, 1, 0, n - 1, a[i], 1);
	}
	ll ans = 0;
	for (int i = 0; i < n; ++i)
	{
		update(1, 1, 0, n - 1, a[i], -1);
		ll left = query(0, 1, 0, n - 1, a[i] + 1, n - 1);
		ll right = query(1, 1, 0, n - 1, 0, a[i] - 1);
		db(a[i], left, right);
		ans += left * right;
		update(0, 1, 0, n - 1, a[i], 1);
	}
	cout << ans << '\n';
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