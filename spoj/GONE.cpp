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

vector<bool> isPrime(101, true);
void seive()
{
	isPrime[0] = isPrime[1] = false;
	for (int i = 4; i < 101; i += 2)
		isPrime[i] = false;
	for (int i = 3; i * i < 101; i += 2)
		if (isPrime[i])
			for (int j = i * i; j <= 101; j += i)
				isPrime[j] = false;
}

string cad;
int dp[10][100];

int rec(int remain, int prevSum)
{
	if (remain == 0)
		return isPrime[prevSum];
	int &ret = dp[remain][prevSum];
	if (ret >= 0)
		return ret;
	ret = 0;
	for (int i = 0; i <= 9; ++i)
		ret += rec(remain - 1, prevSum + i);
	return ret;
}

int solve(int x)
{
	if (x < 0)
		return 0;
	memset(dp, -1, sizeof(dp));
	cad = to_string(x);
	int len = cad.length();
	int remain = len;
	int sumHere = 0, ret = 0;
	for (int i = 0; i < len; ++i)
	{
		int digit = cad[i] - '0';
		remain--;
		for (int j = 0; j < digit; ++j)
			ret += rec(remain, sumHere + j);
		sumHere += digit;
	}
	return ret + isPrime[sumHere];
}

void solve()
{
	int a, b;
	cin >> a >> b;
	--a;
	db(a, b);
	a = solve(a);
	b = solve(b);
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