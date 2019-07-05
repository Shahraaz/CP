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

ll mul(ll a, ll b, ll p)
{
	return a * b % p;
}

void solve()
{
	ll n, p, k;
	cin >> n >> p >> k;
	ll ans = 0, x;
	vector<ll> a(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> x;
		ll temp = mul(x, x, p);
		temp = mul(temp, temp, p);
		temp -= mul(k, x, p);
		if (temp < 0)
			temp += p;
		a[i] = temp;
	}
	sort(a.begin(), a.end());
	for (auto it = a.begin(); it != a.end();)
	{
		auto up = upper_bound(it, a.end(), *it);
		ans += (up - it) * (up - it - 1) / 2;
		it = up;
	}
	cout << ans;
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