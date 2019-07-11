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
const long long mod = 998244353;
auto TimeStart = chrono::steady_clock::now();

const int nax = 5000 + 10;
int dp[nax][nax], sum[nax][nax], inv[nax], cnt[nax];

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

int power(int base, int index)
{
	if (index == 0)
		return 1;
	int temp = power(base, index / 2);
	temp = (temp * (ll)temp) % mod;
	if (index & 1)
		return (ll)temp * base % mod;
	return temp;
}

void solve()
{
	int n, x;
	cin >> n;
	for (int i = 1; i <= n; ++i)
		inv[i] = power(i, mod - 2);
	for (int i = 0; i < n; ++i)
	{
		cin >> x;
		++cnt[x];
	}
	cnt[0] = 1;
	for (int x = n; x >= 0; --x)
		for (int y = n; y >= 0; --y)
		{
			int s = n - y;
			if (cnt[x] == 0 || s <= 0)
			{
				add_self(sum[x][y], sum[x + 1][y]);
				continue;
			}
			add_self(dp[x][y], mul(cnt[x] - 1, inv[s]));
			add_self(dp[x][y], mul(sum[x + 1][y + 1], inv[s]));
			add_self(sum[x][y], sum[x + 1][y]);
			add_self(sum[x][y], mul(cnt[x], dp[x][y]));
		}
	cout << dp[0][0] << '\n';
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