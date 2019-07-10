//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
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

const int nax = 5e6 + 10;
vector<int> dp(nax);

void pre()
{
	for (int i = 2; i < nax; i += 2)
	{
		int a = i;
		while (a % 2 == 0)
		{
			dp[i]++;
			a /= 2;
		}
	}
	for (int i = 3; i < nax; i += 2)
	{
		if (dp[i] == 0)
		{
			for (int j = i; j < nax; j += i)
			{
				int a = j;
				while (a % i == 0)
				{
					dp[j]++;
					a /= i;
				}
			}
		}
	}
	for (int i = 2; i < nax; ++i)
		dp[i] += dp[i - 1];
}

void solve()
{
	int a, b;
	cin >> a >> b;
	db(a, b, dp[a], dp[b]);
	cout << dp[a] - dp[b] << '\n';
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	pre();
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