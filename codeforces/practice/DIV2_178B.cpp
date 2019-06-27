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
	int t, x, w;
	vector<int> one, two;
	for (int i = 0; i < n; ++i)
	{
		cin >> t >> w;
		if (t == 1)
			one.pb(w);
		else
			two.pb(w);
	}
	int ans = 1e9;
	sort(one.begin(), one.end());
	sort(two.begin(), two.end());
	for (int i = 0; i <= one.size(); i++)
		for (int j = 0; j <= two.size(); ++j)
		{
			if (ans > i + 2 * j)
			{
				int s = 0;
				for (int i1 = 0; i1 < one.size() - i; ++i1)
					s += one[i1];
				for (int i1 = 0; i1 < two.size() - j; ++i1)
					s += two[i1];
				if (i + 2 * j >= s)
					ans = i + 2 * j;
			}
		}
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