//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define multitest 1
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

using ll = long long;
#define f first
#define s second
#define pb push_back
const long long mod = 1000000007;
auto TimeStart = chrono::steady_clock::now();

const int nax = 1e6 + 10;
int n, dp[nax][20][2];

int power(int base, int index)
{
	if (index == 0)
		return 1;
	ll temp = power(base, index / 2);
	temp *= temp;
	if (index & 1)
		return temp * base;
	return temp;
}
int f(int x, int y)
{
	return n / (1 << x) / (y == 0 ? 1 : 3);
}

int mul(int a, int b)
{
	return (ll)a * b % mod;
}

void add_self(int &a, int b)
{
	a += b;
	if (a >= mod)
		a -= mod;
}

void solve()
{
	cin >> n;
	int x1 = log2l(n);
	db(log2l(n));
	dp[1][x1][0] = 1;
	if ((1 << (x1 - 1)) * 3 <= n)
		dp[1][x1 - 1][1] = 1;
	for (int i = 1; i < n; ++i)
	{
		for (int x = 0; x <= x1; ++x)
			for (int y = 0; y <= 1; ++y)
			{
				add_self(dp[i + 1][x][y], mul(dp[i][x][y], f(x, y) - i));
				if (x > 0)
					add_self(dp[i + 1][x - 1][y], mul(dp[i][x][y], f(x - 1, y) - f(x, y)));
				if (y > 0)
					add_self(dp[i + 1][x][y - 1], mul(dp[i][x][y], f(x, y - 1) - f(x, y)));
			}
	}
	cout << dp[n][0][0] << '\n';
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (t--)
		solve();
#ifdef TIME
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}