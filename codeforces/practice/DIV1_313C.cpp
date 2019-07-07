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

int _n = 2e5 + 10;
vector<ll> Fact(_n), Inv(_n);
int kmod = 1000000007;

ll mul(ll a, ll b)
{
	return a * b % kmod;
}

ll power(int base, int index)
{
	if (index == 0)
		return 1;
	ll temp = power(base, index / 2);
	temp = mul(temp, temp);
	if (index & 1)
		temp = mul(temp, base);
	return temp;
}

void pre()
{
	Fact[0] = 1;
	for (int i = 1; i < _n; ++i)
		Fact[i] = mul(Fact[i - 1], i);
	Inv[_n - 1] = power(Fact[_n - 1], kmod - 2);
	for (int i = _n - 2; i >= 0; --i)
		Inv[i] = mul(Inv[i + 1], (1 + i));
}

ll ncr(int n, int r)
{
	if (n < 0 || r < 0 || n - r < 0)
		return 0;
	// db(n, r, n - r);
	return mul(Fact[n], mul(Inv[r], Inv[n - r]));
}

void sub_self(ll &a, ll b)
{
	a -= b;
	if (a < 0)
		a += mod;
}

void solve()
{
	pre();
	int h, w, n;
	cin >> h >> w >> n;
	vector<pair<int, int>> Blocked(n);
	for (int i = 0; i < n; ++i)
		cin >> Blocked[i].f >> Blocked[i].s;
	Blocked.emplace_back(h, w);
	sort(Blocked.begin(), Blocked.end());
	vector<ll> dp(n + 1);
	for (int i = 0; i <= n; ++i)
	{
		dp[i] = ncr(Blocked[i].f - 2 + Blocked[i].s, Blocked[i].s - 1);
		for (int j = 0; j < i; ++j)
			if (Blocked[j].f <= Blocked[i].f && Blocked[j].s <= Blocked[i].s)
				sub_self(dp[i], mul(dp[j], ncr(Blocked[i].f - Blocked[j].f + Blocked[i].s - Blocked[j].s, Blocked[i].s - Blocked[j].s)));
		db(dp[i]);
	}
	cout << dp[n];
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