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

vector<int> a(3005), b(3005), c(3005);
vector<vector<ll>> dp(3004, vector<ll>(2, -1));

ll g0(int pos, bool fl)
{
	if (pos == 0)
		return fl ? b[0] : a[0];
	ll &ans = dp[pos][fl];
	if (ans != -1)
		return ans;
	ans = 0;
	if (!fl)
		ans = max(a[pos] + g0(pos - 1, 1), b[pos] + g0(pos - 1, 0));
	else
		ans = max(b[pos] + g0(pos - 1, 1), c[pos] + g0(pos - 1, 0));
	db(pos, fl, ans);
	return ans;
}

void solve()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	for (int i = 0; i < n; ++i)
		cin >> b[i];
	for (int i = 0; i < n; ++i)
		cin >> c[i];
	cout << g0(n - 1, 0) << '\n';
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