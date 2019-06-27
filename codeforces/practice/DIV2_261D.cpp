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

vector<int> Tree(4e6);

void add(int node, int start, int end, int idx)
{
	if (start == end)
	{
		Tree[node]++;
		return;
	}
	int mid = (start + end) / 2;
	if (idx <= mid)
		add(2 * node, start, mid, idx);
	else
		add(2 * node + 1, mid + 1, end, idx);
	Tree[node] = Tree[2 * node] + Tree[2 * node + 1];
}

int get(int node, int start, int end, int qstart, int qend)
{
	if (start == qstart && end == qend)
		return Tree[node];
	int mid = (start + end) / 2;
	int sum = 0;
	if (qstart <= mid)
		sum += get(2 * node, start, mid, qstart, min(mid, qend));
	if (qend > mid)
		sum += get(2 * node + 1, mid + 1, end, max(mid + 1, qstart), qend);
	return sum;
}

void solve()
{
	int n;
	cin >> n;
	// n = 658;
	vector<int> a(n), tot(n), cnt(n + 5), r(n + 5);
	for (int i = 0; i < a.size(); ++i)
	{
		cin >> a[i];
		// a[i] = i;
		tot[i] = a[i];
	}
	sort(tot.begin(), tot.end());
	int s = unique(tot.begin(), tot.end()) - tot.begin();
	tot.resize(s);
	for (int i = 0; i < n; ++i)
		a[i] = lower_bound(tot.begin(), tot.end(), a[i]) - tot.begin();
	for (int i = n - 1; i >= 0; --i)
	{
		cnt[a[i]]++;
		r[i] = cnt[a[i]];
	}
	fill(cnt.begin(), cnt.end(), 0);
	ll ans = 0;
	for (int i = 0; i < n; ++i)
	{
		if (r[i] != n)
			ans += get(1, 1, n, r[i] + 1, n);
		cnt[a[i]]++;
		add(1, 1, n, cnt[a[i]]);
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