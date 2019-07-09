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

const int nax = 5e4 + 10;
int n, k, a, b, ans,
	tempDp[101], subsize[nax], treeSize[nax],
	cost[nax], dp[nax][101];
vector<vector<int>> Adj(nax);

void add_self(int &a, int b)
{
	a += b;
	if (a >= mod)
		a -= mod;
}

int mul(int a, int b)
{
	return (ll)a * b % mod;
}

void dfs(int node, int parent)
{
	subsize[node] = cost[node];
	treeSize[node] = cost[node];
	dp[node][cost[node]] = 1;
	for (int child : Adj[node])
	{
		if (child == parent)
			continue;
		dfs(child, node);
		memset(tempDp, 0, sizeof(tempDp));
		for (int i = 0; i <= k && i <= subsize[node]; ++i)
			tempDp[i] = dp[node][i];
		for (int i = 0; i <= k && i <= subsize[node]; ++i)
			for (int j = 0; j + i <= k && j <= subsize[child]; ++j)
				add_self(tempDp[i + j], mul(dp[node][i], dp[child][j]));
		for (int i = 0; i <= k && i <= subsize[node] + subsize[child]; ++i)
			dp[node][i] = tempDp[i];
		subsize[node] += subsize[child];
		treeSize[node] += treeSize[child];
	}
}

void solve()
{
	cin >> n >> k;
	memset(dp, 0, sizeof(dp));
	memset(tempDp, 0, sizeof(tempDp));
	memset(subsize, 0, sizeof(subsize));
	memset(treeSize, 0, sizeof(treeSize));
	memset(cost, 0, sizeof(cost));
	for (int i = 1; i <= n; ++i)
	{
		cin >> cost[i];
		Adj[i].clear();
	}
	for (int i = 1; i < n; ++i)
	{
		cin >> a >> b;
		Adj[a].pb(b);
		Adj[b].pb(a);
	}
	dfs(1, 0);
	ans = 0;
	for (int i = 1; i <= n; ++i)
		if (treeSize[i] >= k)
			add_self(ans, dp[i][k]);
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