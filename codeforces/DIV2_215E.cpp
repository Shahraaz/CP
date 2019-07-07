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

int n, m, x;
int dp[100010 * 333];

void add_self(int &a, int b)
{
	a += b;
	if (a >= mod)
		a -= mod;
}

int solve(int i, int open, int rem)
{
	db(i, open, rem);
	if (i == m + 1)
		return (open == 0 && rem == 0);
	int &ans = dp[i * (n + 1) * (n + 1) + open * (n + 1) + rem];
	if (ans >= 0)
		return ans;
	ans = 0;
	if (i != x)
		// - Do nothin :p
		add_self(ans, solve(i + 1, open, rem)); // absolutely nothing
	if (rem > 0)
		// [ open an interval
		add_self(ans, solve(i + 1, open + 1, rem - 1));
	if (open > 0 && i != x)
		// ] close an interval
		add_self(ans, solve(i + 1, open - 1, rem));
	if (rem > 0)
		// ][ open and close an interval
		add_self(ans, solve(i + 1, open, rem - 1));
	db(ans, i, open, rem);
	return ans;
}

void solve()
{
	cin >> n >> m >> x;
	if (n > m)
	{
		cout << 0;
		return;
	}
	memset(dp, -1, sizeof(dp));
	ll ans = solve(1, 0, n);
	for (int i = 1; i <= n; ++i)
		ans = (ans * i) % mod;
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