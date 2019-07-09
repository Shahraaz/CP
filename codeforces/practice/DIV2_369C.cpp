//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define multitest 1
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

int n, m, k;
const int nax = 109;
int c[nax], p[nax][nax];
ll dp[nax][nax][nax];

ll solve(int i, int K, int prev)
{
	if (i == n)
	{
		if (K == 0)
			return 0;
		return 1e18;
	}
	if (K == 0)
		return 1e18;
	ll &ret = dp[i][k][prev];
	if (ret >= 0)
		return ret;
	ret = 1e18;
	if (c[i] == 0)
	{
		for (int k = 1; k <= m; ++k)
			if (k == prev)
				continue;
			else
			{
				ll temp = p[i][k] + solve(i + 1, K - 1, k);
				ret = min(ret, temp);
				for (int j = i + 1; j < n; ++j)
					if (c[j] == 0)
					{
						temp += p[j][k];
						ret = min(ret, temp + solve(j + 1, K - 1, k));
					}
					else if (c[j] == k)
						ret = min(ret, temp + solve(j + 1, K - 1, k));
					else
					{
						ret = min(ret, temp + solve(j, K - 1, k));
						break;
					}
			}
	}
	else
	{
		for (int k = c[i]; k <= c[i]; ++k)
			if (k == prev)
				ret = 1e18;
			else
			{
				ll temp = solve(i + 1, K - 1, k);
				ret = temp;
				for (int j = i + 1; j < n; ++j)
					if (c[j] == 0)
					{
						temp += p[j][k];
						ret = min(ret, temp + solve(j + 1, K - 1, k));
					}
					else if (c[j] == k)
						ret = min(ret, temp + solve(j + 1, K - 1, k));
					else
					{
						ret = min(ret, temp + solve(j, K - 1, k));
						break;
					}
			}
	}
	db(ret, i, K, prev);
	return ret;
}

void solve()
{
	cin >> n >> m >> k;
	for (int i = 0; i < n; ++i)
		cin >> c[i];
	for (int i = 0; i < n; ++i)
		for (int j = 1; j <= m; ++j)
			cin >> p[i][j];
	memset(dp, -1, sizeof(dp));
	ll temp = solve(0, k, 0);
	if (temp >= 1e16)
		cout << -1;
	else
		cout << temp << '\n';
}

int main()
{
#ifdef LOCAL
	auto TimeStart = chrono::steady_clock::now();
#endif
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
#ifdef LOCAL
	cout << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}