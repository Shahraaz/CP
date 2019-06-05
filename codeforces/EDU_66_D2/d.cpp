//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
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

map<pair<int, int>, ll> DP;

vector<ll> Sum;
int _n;
void pre(vector<int> &v)
{
	int n = v.size();
	Sum.resize(n);
	_n = n;
	Sum[0] = v[0];
	for (int i = 1; i < n; ++i)
		Sum[i] = Sum[i - 1] + v[i];
}

ll sum(int start, int end)
{
	if (start == 0)
		return Sum[end];
	return Sum[end] - Sum[start - 1];
}

ll dp(vector<int> &v, int start, int end, int k)
{
	db(start, end, k);
	if (start > end)
		return -1e18;
	if (start == end)
	{
		if (k == 0)
		{
			db(start, end, k, 0);
			return 0;
		}
		db(start, end, k, 1e18);
		return -1e18;
	}
	if (k <= 0)
		return -1e18;
	if (DP.find({start, k}) != DP.end())
		return DP[{start, k}];
	ll ans = -1e18, s = 0;
	int cnt = end - start;
	for (int i = start; i < end; ++i)
	{
		s += v[i];
		cnt--;
		auto a = dp(v, i + 1, end, k - 1);
		if (i == (end - 1))
			ans = max(ans, s + a);
		else
			ans = max(ans, s + a + sum(i + 1, end - 1));
		if (cnt < (k - 1))
			break;
	}
	db(start, end, k, ans);
	return DP[{start, k}] = ans;
}



void solve()
{
	int k, n;
	cin >> n >> k;
	vector<int> V(n);
	for (auto &x : V)
		cin >> x;
	pre(V);
	cout << a(V,n-1,k);
	cout << dp(V, 0, n, k);
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