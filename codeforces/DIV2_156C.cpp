//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define multitest 1
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

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	// ll sum = 0;
	set<int> s;
	for (auto &x : a)
	{
		cin >> x;
		s.insert(x);
	}
	map<int, int> NewIndex;
	int k = 0;
	for (auto x : s)
		NewIndex[x] = k++;
	for (auto &x : a)
		x = NewIndex[x];
	vector<vector<int>> Dp(4005, vector<int>(4005));
	for (int i = 0; i < n; ++i)
	{
		bool flag = false;
		for (int j = i - 1; j >= 0; --j)
		{
			if (a[i] == a[j])
			{
				if (flag)
					continue;
				flag = true;
				Dp[a[i]][a[i]]++;
			}
			else
				Dp[a[i]][a[j]] = max(Dp[a[i]][a[j]], 1 + Dp[a[j]][a[i]]);
		}
	}
	int answer = 0;
	for (auto x : Dp)
		answer = max(answer, *max_element(x.begin(), x.end()));
	cout << 1 + answer << '\n';
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