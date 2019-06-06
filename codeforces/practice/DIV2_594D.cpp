//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

vector<ll> Ssum;
int _n;
void Sum(vector<int> &v)
{
	_n = v.size();
	Ssum.resize(_n);
	Ssum[0] = v[0];
	for (int i = 1; i < _n; ++i)
		Ssum[i] = Ssum[i - 1] + v[i];
}
ll IntervalSum(int start, int end)
{
	if (start < 0 || end >= _n || end < 0)
		return 0;
	if (start == 0)
		return Ssum[end];
	return Ssum[end] - Ssum[start - 1];
}

void solve()
{
	vector<int> Intrest(26);
	for (auto &x : Intrest)
		cin >> x;
	string str;
	cin >> str;
	vector<vector<int>> Pos(26);
	int n = str.size();
	vector<int> ValueOfChar(n);
	for (int i = 0; i < n; ++i)
	{
		Pos[str[i] - 'a'].pb(i);
		ValueOfChar[i] = Intrest[str[i] - 'a'];
	}
	Sum(ValueOfChar);
	ll ans = 0;
	for (int i = 0; i < 26; ++i)
	{
		map<ll, int> Map;
		int n = Pos[i].size();
		for (int j = 0; j < n; ++j)
		{
			int p = Pos[i][j];
			ans += Map[IntervalSum(0, p - 1)];
			Map[IntervalSum(0, p)]++;
		}
	}
	cout << ans;
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