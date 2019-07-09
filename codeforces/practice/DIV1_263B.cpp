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

const int nax = 1e5 + 10;
vector<int> Adj[nax], dp0(nax), dp1(nax), x(nax);

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

void dfs(int node)
{
	dp0[node] = 1;
	dp1[node] = 0;
	for (int child : Adj[node])
	{
		dfs(child);
		dp1[node] = mul(dp1[node], dp0[child]);
		add_self(dp1[node], mul(dp0[node], dp1[child]));
		dp0[node] = mul(dp0[node], dp0[child]);
	}
	if (x[node])
		dp1[node] = dp0[node];
	else
		add_self(dp0[node], dp1[node]);
}

void solve()
{
	int n, u, v;
	cin >> n;
	for (int i = 1; i < n; ++i)
	{
		cin >> v;
		Adj[v].pb(i);
	}
	for (int i = 0; i < n; ++i)
		cin >> x[i];
	dfs(0);
	cout << dp1[0] << '\n';
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

/* 
#include <bits/stdc++.h>
#define bs 1000000007
using namespace std;
int tests, n, k, a, b;
vector<int> g[1 << 20];
int cost[1 << 20];
int dp[55000][101];
int answ;
int used[55000];
long tdp[55000];
int subsize[55000];
int tsz[55000];
void dfs(int v)
{
	used[v] = 1;
	subsize[v] = cost[v];
	tsz[v] = cost[v];

	vector<int> sons;

	for (int i = 0; i < g[v].size(); i++)
	{
		int to = g[v][i];
		if (used[to])
			continue;
		dfs(to);
		sons.push_back(to);
		tsz[v] += tsz[to];
	}

	for (int i = 0; i <= tsz[v] && i <= k; i++)
		dp[v][i] = 0;

	dp[v][cost[v]] = 1;
	for (int ii = 0; ii < sons.size(); ii++)
	{
		int id = sons[ii];

		for (int i = 0; i <= k && i <= subsize[v] + subsize[id]; i++)
			tdp[i] = 0;

		for (int i = 0; i <= k && i <= subsize[v]; i++)
			tdp[i] = dp[v][i];

		for (int i = 0; i <= k && i <= subsize[v]; i++)
			for (int j = 0; j <= k - i && j <= subsize[id]; j++)
			{
				tdp[i + j] = tdp[i + j] + 1ll * dp[v][i] * dp[id][j];
				if (tdp[i + j] > 8e18)
					tdp[i + j] %= bs;
			}

		for (int i = 0; i <= subsize[v] + subsize[id] && i <= k; i++)
			dp[v][i] = tdp[i] % bs;
		subsize[v] += subsize[id];
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	//cin.tie(0);
	scanf("%d", &tests);
	for (; tests; --tests)
	{
		scanf("%d %d", &n, &k);

		for (int i = 1; i <= n; i++)
			used[i] = 0;

		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &cost[i]);
		}

		for (int i = 1; i <= n; i++)
			g[i].clear();

		for (int i = 1; i < n; i++)
		{
			scanf("%d %d", &a, &b);
			g[a].push_back(b);
			g[b].push_back(a);
		}

		dfs(1);
		answ = 0;

		for (int i = 1; i <= n; i++)
			if (tsz[i] >= k)
				answ = (answ + dp[i][k]) % bs;
		cout << answ << endl;
	}
	cin.get();
	cin.get();
	return 0;
}
*/