//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
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
	int n, a, f;
	cin >> n;
	vector<int> cnt(n), cnt_good(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> a >> f;
		--a;
		cnt[a]++;
		if (f)
			cnt_good[a]++;
	}
	vector<vector<int>> types(n + 1);
	for (int i = 0; i < n; ++i)
		types[cnt[i]].pb(cnt_good[i]);
	int ans1, ans2;
	ans1 = ans2 = 0;
	multiset<int> curr;
	for (int i = n; i > 0; --i)
	{
		for (auto x : types[i])
			curr.insert(x);
		if (!curr.empty())
		{
			int z = *curr.rbegin();
			ans1 += i;
			ans2 += min(i, z);
			curr.erase(--curr.end());
		}
	}
	cout << ans1 << ' ' << ans2 << '\n';
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