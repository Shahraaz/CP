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

void add_self(ll &a, ll b)
{
	a += b;
	if (a >= mod)
		a -= mod;
}

vector<pair<int, int>> Forbidden;
vector<vector<ll>> ways(20003, vector<ll>(20));
int r, n, c, charge;

ll noOfWays(pair<int, int> a, pair<int, int> b) // ways from a to b
{
	if (a.f <= b.f && a.s <= b.s)
		return ncr((b.f - a.f + b.s - a.s) % mod, b.f - a.f);
	return 0;
}

void solve()
{
	pre();
	cin >> r >> c >> n >> charge;
	Forbidden.resize(n);
	bool src_ana, dest_ana;
	src_ana = dest_ana = false;
	for (int i = 0; i < n; ++i)
	{
		cin >> Forbidden[i].f >> Forbidden[i].s;
		if (Forbidden[i].f == 1 && Forbidden[i].s == 1)
			src_ana = true;
		else if (Forbidden[i].f == r && Forbidden[i].s == c)
			dest_ana = true;
	}
	if (!src_ana)
	{
		Forbidden.emplace_back(1, 1);
		++n;
	}
	sort(Forbidden.begin(), Forbidden.end());
	if (dest_ana)
	{
		Forbidden.pop_back();
		--n;
	}
	pair<int, int> dest = make_pair(r, c);
	pair<int, int> src = make_pair(1, 1);
	for (int i = n - 1; i >= 0; --i)
	{
		ways[i][0] = noOfWays(Forbidden[i], dest);
		db("Start", i, ways[i][0]);
		// db(Forbidden[i].f, Forbidden[i].s);
		for (int j = i + 1; j < n; ++j)
			sub_self(ways[i][0], mul(noOfWays(Forbidden[i], Forbidden[j]), ways[j][0]));
		db("Final", i, ways[i][0]);
	}
	for (int j = 1; j < 20; ++j)
		for (int i = n - 1; i >= 0; --i)
		{
			ways[i][j] = noOfWays(Forbidden[i], dest);
			for (int k = i + 1; k < n; ++k)
				sub_self(ways[i][j], mul(noOfWays(Forbidden[i], Forbidden[k]), ways[k][j]));
			for (int k = 0; k < j; ++k)
				sub_self(ways[i][j], ways[i][k]);
		}
	ll tot = noOfWays(src, dest), ans = 0;
	ll currCharge = charge;
	for (int j = 0; j < 20; ++j)
	{
		ll val = currCharge;
		currCharge = (currCharge + 1) / 2;
		if (src_ana)
			val = (val + 1) / 2;
		if (dest_ana)
			val = (val + 1) / 2;
		db(ways[0][j], tot);
		add_self(ans, mul(val, ways[0][j]));
		sub_self(tot, ways[0][j]);
	}
	add_self(ans, tot);
	ans = mul(ans, power(noOfWays(src, dest), mod - 2));
	db("Output is");
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