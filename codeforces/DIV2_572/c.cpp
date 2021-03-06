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

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &x : a)
		cin >> x;
	vector<ll> s(n);
	s[0] = a[0];
	for (int i = 1; i < n; ++i)
		s[i] = s[i - 1] + a[i];
	int q, l, r;
	cin >> q;
	while (q--)
	{
		cin >> l >> r;
		l--;
		r--;
		ll a = s[r];
		if (l != 0)
			a -= s[l - 1];
		cout << a / 10 << '\n';
	}
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