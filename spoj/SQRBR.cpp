//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
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

using ll = long long;
#define f first
#define s second
#define pb push_back
const long long mod = 1000000007;
auto TimeStart = chrono::steady_clock::now();

const int nax = 100;
int Occu[nax];
ll dp[nax][nax][nax];
int n, k, x;

ll solve(int idx, int close, int open)
{
	if (idx == 2 * n + 1)
	{
		if (open == 0 && close == 0)
			return 1;
		return 0;
	}
	ll &ret = dp[idx][close][open];
	if (ret >= 0)
		return ret;
	ret = 0;
	int lOpen = n - open;
	int lClose = n - close;
	if (!Occu[idx])
	{
		if ((lOpen - lClose) > 0 && close > 0)
			ret += solve(idx + 1, close - 1, open);
	}
	if (open > 0)
		ret += solve(idx + 1, close, open - 1);
	db(ret, close, open);
	return ret;
}

void solve()
{
	cin >> n >> k;
	memset(Occu, 0, sizeof(Occu));
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < k; ++i)
	{
		cin >> x;
		Occu[x] = 1;
	}
	cout << solve(1, n, n) << '\n';
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (t--)
		solve();
#ifdef TIME
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}