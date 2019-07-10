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
vector<int> dp(nax);
int n, x;

void add_self(int &a, int b)
{
	a += b;
	if (a >= mod)
		a -= mod;
}
void solve()
{
	db("Here");
	cin >> n;
	dp[0] = 1;
	for (int i = 1; i <= n; ++i)
	{
		db(i);
		cin >> x;
		vector<int> factors;
		for (int i = 1; i * i <= x; ++i)
			if (x % i == 0)
			{
				factors.pb(i);
				if (x != i * i)
					factors.pb(x / i);
			}
		sort(factors.begin(), factors.end());
		for (int i = factors.size() - 1; i >= 0; --i)
			add_self(dp[factors[i]], dp[factors[i] - 1]);
	}
	int ans = 0;
	for (int i = 1; i < nax; ++i)
		add_self(ans, dp[i]);
	cout << ans;
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
	cout << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}