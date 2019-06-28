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

ll solve(ll a, ll b)
{
	if (a == 0 || b == 0)
		return 0;
	if (a == 1)
		return (b + 1) / 3;
	if (b == 1)
		return (a + 1) / 2;
	if ((b) % 3 == 2)
		return (b + 1) / 3 * (a + 1) / 2;
	if ((b) % 3 == 0)
		return solve(a, b - 1);
	else
		return solve(a, b - 1) + solve(1, a);
}

void solve()
{
	int n, m;
	cin >> n >> m;
	int a = min(n, m);
	int b = max(n, m);
	cout << max(solve(a, b), solve(b, a));
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