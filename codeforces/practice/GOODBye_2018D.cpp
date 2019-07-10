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

using ll = long long;
#define f first
#define s second
#define pb push_back
const long long mod = 998244353;
auto TimeStart = chrono::steady_clock::now();

const int nax = 1e6 + 10;
int _n = 1e6 + 10;
vector<ll> Fact(_n), Inv(_n);
int kmod = 998244353;

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
	int n;
	cin >> n;
	ll res = mul(n, Fact[n]);
	for (int i = 1; i < n; ++i)
		sub_self(res, mul(Fact[n], Inv[i]));
	cout << res;
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
	cout << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}