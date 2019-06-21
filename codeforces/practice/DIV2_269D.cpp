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

vector<ll> CalZ(vector<ll> str)
{
	int n = str.size();
	vector<ll> z(n);
	int l, r;
	l = r = 0;
	// cout << str[0] << ' ';
	for (int i = 1; i < n; ++i)
	{
		// cout << str[i] << ' ';
		if (i > r)
		{
			l = r = i;
			db(str[r],str[r-l],r,r-l);
			while (r < n && str[r] == str[r - l])
				r++;
			z[i] = r - l;
			r--;
		}
		else
		{
			int k = i - l;
			if (z[k] < (r - i + 1))
				z[i] = z[k];
			else
			{
				l = i;
				db(str[r], str[r - l], r, r - l);
				while (r < n && str[r] == str[r - l])
					r++;
				z[i] = r - l;
				r--;
			}
		}
	}
	// cout << '\n';
	return z;
}

void solve()
{
	int n, w;
	cin >> n >> w;
	if (w > n)
	{
		cout << 0 << '\n';
		return;
	}
	vector<int> a(n);
	for (auto &x : a)
		cin >> x;
	vector<int> b(w);
	for (auto &x : b)
		cin >> x;
	vector<ll> str;
	for (int i = 0; i < w - 1; ++i)
		str.pb(b[i + 1] - b[i]);
	str.pb(1e18);
	for (int i = 0; i < n - 1; ++i)
		str.pb(a[i + 1] - a[i]);
	auto z = CalZ(str);
	int ans = 0;
	for (auto x : z)
	{
		// cout << x << ' ';
		if (x == (w - 1))
			ans++;
	}
	// cout << '\n';
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