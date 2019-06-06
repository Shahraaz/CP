//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
// #define multitest 1
#define Debug 1
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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int n, d;
vector<vector<int>> Graph;
vector<int> a;

ll dfs(int u, int p, int root)
{
	ll res = 1;
	for (auto v : Graph[u])
	{
		if (v == p)
			continue;
		if ((a[v] <= (a[root] + d) && a[v] > a[root]) || (a[v] == a[root] && v <= root))
			res = (res * (1 + dfs(v, u, root))) % mod;
	}
	return res;
}

void solve()
{
	cin >> d >> n;
	Graph.resize(n);
	a.resize(n);
	for (auto &x : a)
		cin >> x;
	int u, v;
	for (int i = 1; i < n; ++i)
	{
		cin >> u >> v;
		u--;
		v--;
		Graph[u].pb(v);
		Graph[v].pb(u);
	}
	ll ans = 0;
	for (int i = 0; i < n; ++i)
	{
		ans += dfs(i, -1, i);
		// db(ans);
		ans %= mod;
	}
	cout << ans << '\n';
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#ifndef Online
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	auto TimeStart = chrono::steady_clock::now();
	auto TimeEnd = chrono::steady_clock::now();
#endif
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (t--)
		solve();
#ifndef Online
	TimeEnd = chrono::steady_clock::now();
	auto ElapsedTime = TimeEnd - TimeStart;
	cout << "\n\nTime elapsed: " << chrono::duration<double>(ElapsedTime).count() << " seconds.\n";
#endif
	return 0;
}