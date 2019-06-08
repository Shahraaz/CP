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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

bool ok(ll x, vector<int> a, int w, int m)
{
	db(x,w,m);
	int n = a.size();
	vector<ll> toadd(n + 10 + w);
	ll used = 0, addedEveryWhere = 0;
	for (int i = 0; i < n; ++i)
	{
		addedEveryWhere += toadd[i];
		// db(i, a[i], used);
		a[i] += addedEveryWhere;
		if (a[i] < x)
		{
			used += x - a[i];
			addedEveryWhere += x - a[i];
			toadd[i + w] -= x - a[i];
		}
		if (used > m)
			return false;
		// db(i, a[i], used);
	}
	return used <= m;
}

void solve()
{
	int n, m, w;
	cin >> n >> m >> w;
	vector<int> a(n);
	for (auto &x : a)
		cin >> x;
	ll low = 0, high = 1e12;
	ll answer = 0;
	while (low <= high)
	{
		ll mid = (low + high) / 2;
		if (ok(mid, a, w, m))
		{
			answer = mid;
			low = mid + 1;
		}
		else
			high = mid - 1;
	}
	cout << answer << '\n';
	db("ou")
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
	return 0;
}