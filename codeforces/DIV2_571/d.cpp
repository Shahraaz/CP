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
	vector<pair<ld, int>> a;
	ld x;
	ll sum = 0, min = 0;
	db(int(-1.5), int(2));
	vector<pair<int, int>> ans;
	for (int i = 0; i < n; ++i)
	{
		cin >> x;
		if (abs(x - floor(x)) < 1e-5)
		{
			db(1);
			ans.pb({i, floor(x)});
			sum += floor(x);
		}
		else if (abs(x - ceil(x)) < 1e-5)
		{
			db(2);
			ans.pb({i, ceil(x)});
			sum += ceil(x);
		}
		else
		{
			db(x, floor(x), ceil(x));
			min += floor(x);
			a.pb({x, i});
		}
	}
	sort(a.begin(), a.end());
	int ssum = sum + min;
	if (ssum <= 0)
	{
		int cnt = -ssum;
		db(cnt);
		for (auto x : a)
		{
			if (cnt)
			{
				cnt--;
				ans.pb({x.s, ceil(x.f)});
			}
			else
				ans.pb({x.s, floor(x.f)});
		}
	}
	sort(ans.begin(), ans.end());
	for (auto x : ans)
		cout << x.s << '\n';
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