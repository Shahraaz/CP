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

int dp[10][100][100];
string cad;

int rec(int remain, int odd, int even)
{
	if (remain == 0)
		return (even - odd) == 1;
	int &ret = dp[remain][odd][even];
	if (ret >= 0)
		return ret;
	ret = 0;
	for (int i = 0; i <= 9; ++i)
		if (remain % 2)
			ret += rec(remain - 1, odd + i, even);
		else
			ret += rec(remain - 1, odd, even + i);
	return ret;
}

int solve(int x)
{
	memset(dp, -1, sizeof(dp));
	cad = to_string(x);
	int len = cad.length();
	int remain = len;
	int ret = 0;
	int odd = 0, even = 0;
	for (int i = 0; i < len; ++i)
	{
		int digit = cad[i] - '0';
		remain--;
		for (int j = 0; j < digit; ++j)
		{
			if ((len - i) % 2)
				ret += rec(remain, odd + j, even);
			else
				ret += rec(remain, odd, even + j);
		}
		if ((len - i) % 2)
			odd += digit;
		else
			even += digit;
	}
	return ret;
}

void solve()
{
	int a, b;
	cin >> a >> b;
	cout << solve(b + 1) - solve(a) << '\n';
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