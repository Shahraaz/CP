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

void solve()
{
	int n;
	cin >> n;
	vector<vector<int>> Mat(n + 1, vector<int>(n + 1));
	vector<vector<ll>> Dp(n + 1, vector<ll>(1 << n));
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> Mat[i - 1][j - 1];
	Dp[0][0] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < (1 << n); ++j)
		{
			int cnt = __builtin_popcount(j);
			if (cnt == i - 1)
			{
				for (int k = 0; k < n; ++k)
				{
					if (j & (1 << k))
						continue;
					if (!Mat[i - 1][k])
						continue;
					int j1 = j | (1 << k);
					Dp[i][j1] += Dp[i - 1][j];
					db(Dp[i][j1], i, j1, j, Dp[i - 1][j]);
				}
			}
		}
	cout << Dp[n][(1 << n) - 1] << '\n';
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