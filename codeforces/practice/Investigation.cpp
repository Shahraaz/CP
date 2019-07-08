// https://vjudge.net/problem/LightOJ-1068
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

int cnt = 1, a, b, k;
int dp[20][200][200];

void add_self(int &a, int b)
{
	a += b;
	if (a >= mod)
		a -= mod;
}

int solve(int rem, int prevSum, int prevRem)
{
	if (rem == 0)
		return prevSum == 0 && prevRem == 0;
	int &ret = dp[rem][prevSum][prevRem];
	if (ret >= 0)
		return ret;
	ret = 0;
	for (int dig = 0; dig < 10; ++dig)
	{
		int newSum = (prevSum + dig) % k;
		int newRem = (prevRem * 10 + dig) % k;
		add_self(ret, solve(rem - 1, newSum, newRem));
	}
	return ret;
}

int solve(int x)
{
	if (k > 120)
		return x > 0;
	auto s = to_string(x);
	int len = s.length();
	int rem = len, prevSum = 0, prevRem = 0;
	int ans = 0;
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < len; ++i)
	{
		int dig = s[i] - '0';
		rem--;
		for (int j = 0; j < dig; ++j)
		{
			int newSum = (prevSum + j) % k;
			int newRem = (prevRem * 10 + j) % k;
			add_self(ans, solve(rem, newSum, newRem));
		}
		prevSum = (prevSum + dig) % k;
		prevRem = (prevRem * 10 + dig) % k;
	}
	db(x, x % k, prevRem);
	return ans + (prevSum == 0 && prevRem == 0);
}

void solve()
{
	cin >> a >> b >> k;
	db("Start", a);
	a = solve(a - 1);
	db("DP result", a);
	db("Start", b);
	b = solve(b);
	db("DP result", b);
	cout << "Case " << cnt++ << ": " << b - a << '\n';
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