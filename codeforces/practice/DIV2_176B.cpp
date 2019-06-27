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

ll sum(ll a)
{
	if (a < 0)
		return -1;
	return (a + a * a) / 2;
}

ll solve(ll n, ll k)
{
	if (n == 0)
		return 0;
	if (n > sum(k))
		return -1;
	if (n == sum(k))
		return k;
	if (n <= k)
		return 1;
	ll lo = 0, high = k;
	while (lo <= high)
	{
		int mid = (lo + high) / 2;
		ll x = sum(k) - sum(mid - 1);
		ll y = sum(k) - sum(mid - 2);
		if (x <= n && y > n)
			return k + 1 - mid + solve(n - x, mid - 1);
		if (x < n)
			high = mid - 1;
		else
			lo = mid + 1;
	}
	return -1;
}

void solve()
{
	ll n, k;
	cin >> n >> k;
	cout << solve(n - 1, k - 1) << '\n';
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