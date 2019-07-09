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

const int nax = 1e3 + 10;
int arr[26], n, dp[nax];
string str;

void add_self(int &a, int b)
{
	a += b;
	if (a >= mod)
		a -= mod;
}

int solve1(int pos)
{
	if (pos > n)
		return 1;
	int &ret = dp[pos];
	if (ret >= 0)
		return ret;
	ret = 0;
	int mn = n + 1;
	for (int i = pos; i <= n; ++i)
	{
		mn = min(mn, arr[str[i] - 'a']);
		if (i - pos + 1 <= mn)
			add_self(ret, solve1(i + 1));
		else
			break;
	}
	return ret;
}

int solve2(int pos)
{
	if (pos > n)
		return 0;
	int &ret = dp[pos];
	if (ret >= 0)
		return ret;
	ret = 0;
	int mn = n + 1;
	for (int i = pos; i <= n; ++i)
	{
		mn = min(mn, arr[str[i] - 'a']);
		if (i - pos + 1 <= mn)
			ret = max(ret, max(i - pos + 1, solve2(i + 1)));
		else
			break;
	}
	return ret;
}

int solve3(int pos)
{
	if (pos > n)
		return 0;
	int &ret = dp[pos];
	if (ret >= 0)
		return ret;
	ret = n + 1;
	int mn = n + 1;
	for (int i = pos; i <= n; ++i)
	{
		mn = min(mn, arr[str[i] - 'a']);
		if (i - pos + 1 <= mn)
			ret = min(ret, 1 + solve3(i + 1));
		else
			break;
	}
	return ret;
}

void solve()
{
	cin >> n;
	cin >> str;
	str = '$' + str;
	for (int i = 0; i < 26; ++i)
		cin >> arr[i];
	memset(dp, -1, sizeof(dp));
	cout << solve1(1) << '\n';
	memset(dp, -1, sizeof(dp));
	cout << solve2(1) << '\n';
	memset(dp, -1, sizeof(dp));
	cout << solve3(1) << '\n';
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
#ifdef LOCAL
	auto TimeStart = chrono::steady_clock::now();
#endif
	while (t--)
		solve();
#ifdef LOCAL
	cout << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}