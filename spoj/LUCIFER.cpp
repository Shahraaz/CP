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

string cad;
int dp[11][90][90];
vector<bool> isPrime(101, true);

void seive()
{
	isPrime[0] = isPrime[1] = false;
	for (int i = 4; i < 101; i += 2)
		isPrime[i] = false;
	for (int i = 3; i * i < 101; i += 2)
		if (isPrime[i])
			for (int j = i * i; j < 101; j += i)
				isPrime[j] = false;
}

int rec(int digit, int odd, int even)
{
	if (digit == 0)
	{
		if (even < odd)
			return 0;
		return isPrime[even - odd];
	}
	int &ret = dp[digit][odd][even];
	if (ret >= 0)
		return ret;
	ret = 0;
	for (int i = 0; i <= 9; ++i)
		if (digit % 2)
			ret += rec(digit - 1, odd + i, even);
		else
			ret += rec(digit - 1, odd, even + i);
	return ret;
}

int solve(int x)
{
	memset(dp, -1, sizeof(dp));
	int ret = 0;
	int even = 0;
	int odd = 0;
	cad = to_string(x);
	int len = cad.length();
	int remain = len;
	for (int i = 0; i < len; ++i)
	{
		int digit = cad[i] - '0';
		remain--;
		for (int j = 0; j < digit; ++j)
			if ((len - i) % 2)
				ret += rec(remain, odd + j, even);
			else
				ret += rec(remain, odd, even + j);
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
	db(a, b);
	a = solve(a);
	b = solve(b + 1);
	db(a, b);
	cout << b - a << '\n';
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
	seive();
	while (t--)
		solve();
	return 0;
}