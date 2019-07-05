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

void addOne(string &num)
{
	reverse(num.begin(), num.end());
	int len = num.length();
	bool carry = 1;
	for (int i = 0; i < len; ++i)
	{
		int dig = num[i] - '0';
		dig += carry;
		carry = dig / 10;
		dig %= 10;
		num[i] = dig + '0';
	}
	if (carry)
		num.pb(49);
	reverse(num.begin(), num.end());
}

void add_self(int &a, int b)
{
	a += b;
	if (a >= mod)
		a -= mod;
}

void sub_self(int &a, int b)
{
	a -= b;
	if (a < 0)
		a += mod;
}

int dp[60][60][60][60];

int rec(int remain, int three, int six, int nine)
{
	if (remain < 0)
		return 0;
	if (remain == 0)
	{
		if (three == 0)
			return 0;
		return three == six && six == nine;
	}
	db(remain, three, six, nine);
	int &ret = dp[remain][three][six][nine];
	if (ret >= 0)
		return ret;
	ret = 0;
	for (int i = 0; i < 10; ++i)
	{
		switch (i)
		{
		case 3:
			add_self(ret, rec(remain - 1, three + 1, six, nine));
			break;
		case 6:
			add_self(ret, rec(remain - 1, three, six + 1, nine));
			break;
		case 9:
			add_self(ret, rec(remain - 1, three, six, nine + 1));
			break;
		default:
			add_self(ret, rec(remain - 1, three, six, nine));
			break;
		}
	}
	return ret;
}

int solve(string &a)
{
	int ans = 0;
	int len = a.length();
	int remain = len;
	int three, six, nine;
	three = six = nine = 0;
	for (int i = 0; i < len; ++i)
	{
		remain--;
		int dig = a[i] - '0';
		for (int j = 0; j < dig; ++j)
		{
			switch (j)
			{
			case 3:
				add_self(ans, rec(remain, three + 1, six, nine));
				break;
			case 6:
				add_self(ans, rec(remain, three, six + 1, nine));
				break;
			case 9:
				add_self(ans, rec(remain, three, six, nine + 1));
				break;
			default:
				add_self(ans, rec(remain, three, six, nine));
				break;
			}
		}
		switch (dig)
		{
		case 3:
			three++;
			break;
		case 6:
			six++;
			break;
		case 9:
			nine++;
			break;
		default:
			break;
		}
	}
	return ans;
}

void solve()
{
	db("Case :");
	string a, b;
	cin >> a >> b;
	addOne(b);
	cout << (solve(b) - solve(a) + mod) % mod << '\n';
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
	memset(dp, -1, sizeof(dp));
	while (t--)
		solve();
	return 0;
}