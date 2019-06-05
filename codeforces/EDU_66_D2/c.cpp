//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
#define multitest 1
#define Debug 1
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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll f(vector<ll> &v, int k, ll X)
{
	vector<ll> d;
	for (auto x : v)
		d.pb(abs(x - X));
	sort(d.begin(), d.end());
	return d[k - 1];
}

int n, k;
ll brute(vector<ll> &v, ll mini, ll maxi)
{
	db(mini, maxi);
	ll a = 1e18;
	for (; mini <= maxi; ++mini)
		a = min(a, f(v, k, mini));
	return a;
}

void solve()
{
	cin >> n >> k;
	vector<ll> v(n);
	ll mini = mod;
	ll maxi = -1;
	for (auto &x : v)
	{
		cin >> x;
		mini = min(mini, (ll)x);
		maxi = max(maxi, (ll)x);
	}
	ll a = 1e18;
	int t = 250;
	while (t--)
	{
		db(mini, maxi);
		if (maxi - mini < 200)
		{

			a = min(a, brute(v, mini, maxi));
			break;
		}
		ll l1 = (2 * mini + maxi) / 3;
		ll l2 = (mini + 2 * maxi) / 3;
		ll f1 = f(v, k, l1);
		ll f2 = f(v, k, l2);
		if (f1 < f2)
		{
			a = l1;
			maxi = l2;
		}
		else
		{
			a = l2;
			mini = l1;
		}
	}
	cout << "Answer ";
	cout << a << '\n';
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#ifndef Online
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	auto TimeStart = chrono::steady_clock::now();
	auto TimeEnd = chrono::steady_clock::now();
#endif
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (t--)
		solve();
#ifndef Online
	TimeEnd = chrono::steady_clock::now();
	auto ElapsedTime = TimeEnd - TimeStart;
	cout << "\n\nTime elapsed: " << chrono::duration<double>(ElapsedTime).count() << " seconds.\n";
#endif
	return 0;
}