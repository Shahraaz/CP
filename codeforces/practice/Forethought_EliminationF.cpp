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

const int nax = 2e5 + 10;
vector<int> Adj[nax];
vector<vector<int>> dp(nax, vector<int>(3));

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
	int n, i, p;
	cin >> n;
	for (int i = 1; i < n; ++i)
	{
		cin >> p;
		--p;
		Adj[p].pb(i);
	}
	vector<int> aux(3);
	for (int i = n - 1; i >= 0; --i) // We will literally make the Partitions
	// Intlligently
	{
		if (Adj[i].size() == 0) // We got a leaft
		{
			dp[i][2] = 1;
		}
		else
		{
			dp[i][0] = 1;
			for (int j : Adj[i])
			{
				aux[0] = (mul(dp[i][0], dp[j][0]) + mul(dp[i][0], dp[j][2])) % mod;
				aux[1] = ((mul(dp[i][0], dp[j][1]) + mul(dp[i][0], dp[j][2])) % mod +
						  (mul(dp[i][1], dp[j][0]) + mul(dp[i][1], dp[j][2])) % mod) %
						 mod;
				aux[2] = mul(dp[i][1], dp[j][1]);
				add_self(aux[2], mul(dp[i][1], dp[j][2]));
				add_self(aux[2], mul(dp[i][2], dp[j][0]));
				add_self(aux[2], mul(dp[i][2], dp[j][1]));
				add_self(aux[2], mul(dp[i][2], dp[j][2]));
				add_self(aux[2], mul(dp[i][2], dp[j][2]));
				dp[i] = aux;
			}
		}
	}
	cout << (dp[0][0] + dp[0][2]) % mod << '\n';
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