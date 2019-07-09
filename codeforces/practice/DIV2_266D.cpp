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

ll dp[2005][2005], a[2005];
void add_self(ll &a, ll b)
{
	a += b;
	if (a >= mod)
		a -= mod;
}

void solve()
{
	ll n, h;
	cin >> n >> h;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	dp[1][0] = (a[1] == h) || (a[1] + 1 == h);
	dp[1][1] = a[1] + 1 == h;
	for (ll i = 2; i <= n; ++i)
		for (int open = max(0LL, h - a[i] - 1); open <= min(h - a[i], i); ++open)
		{
			if (a[i] + open == h)
			{
				add_self(dp[i][open], dp[i - 1][open]); // - Do nothing :P
				if (open > 0)
					add_self(dp[i][open], dp[i - 1][open - 1]); // [ Open a new Segment
			}
			else if (a[i] + open + 1 == h)
			{
				add_self(dp[i][open], dp[i - 1][open + 1] * (open + 1) % mod);
				// ] Close one of the opened segments
				add_self(dp[i][open], dp[i - 1][open]);
				// [] creating one length segment
				add_self(dp[i][open], dp[i - 1][open] * open % mod);
				// ][  choose one to close and opena new here
			}
		}
	cout << dp[n][0];
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