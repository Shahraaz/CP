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

void solve()
{
	int n, m, u, v;
	cin >> n >> m;
	vector<vector<bool>> Adj(n + 1, vector<bool>(n + 1));
	for (int i = 0; i < m; ++i)
	{
		cin >> u >> v;
		u--;
		v--;
		Adj[u][v] = Adj[v][u] = true;
	}
	vector<vector<ll>> Dp(1 << 20, vector<ll>(20));
	ll ans = 0;
	for (int a = 1; a < (1 << n); ++a)
	{
		int sm = __builtin_popcountl(a);
		db(a, sm);
		if (sm == 1)
			Dp[a][__builtin_ffsl(a) - 1] = 1;
		else
		{
			bool flag = false;
			for (int bit = 0; bit < n; ++bit)
				if (a & (1 << bit))
				{
					if (flag)
					{
						for (int bit2 = 0; bit2 < n; ++bit2)
							if (bit2 != bit && Adj[bit][bit2])
								Dp[a][bit] += Dp[a ^ (1 << bit)][bit2];
					}
					flag = 1;
				}
			if (sm >= 3)
			{
				int bit, bit2;
				bit = __builtin_ffsl(a) - 1;
				db(bit);
				for (bit2 = bit + 1; bit2 < n; ++bit2)
					if ((a & (1 << bit2)) && Adj[bit][bit2])
						ans += Dp[a][bit2];
			}
		}
	}
	db("Finish");
	cout << ans / 2;
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