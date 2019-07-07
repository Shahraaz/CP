//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define multitest 1
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

void add_self(int &a, int b)
{
	a += b;
	if (a >= mod)
		a -= mod;
}

int dp[2][204][1005];
void solve()
{
	int n, v;
	cin >> n >> v;
	vector<int> arr(n);
	for (int i = 0; i < n; ++i)
		cin >> arr[i];
	sort(arr.begin(), arr.end());
	dp[0][0][0] = 1;
	dp[0][1][0] = 1;
	for (int i = 1; i < n; ++i) // Numbers of numbers processed
	{
		int curr = i & 1;
		int prev = curr ^ 1;
		memset(dp[curr], 0, sizeof(dp[curr]));
		for (int j = 0; j <= i; ++j)	 // Number of Open Intervals Right Now
			for (int k = 0; k <= v; ++k) // Imbalance/Chaos upto here
			{
				ll val = dp[prev][j][k];
				int nval = k + j * (arr[i] - arr[i - 1]); // Imbalance of new State
				if (nval > v)
					continue;
				db(i, j, k, nval, val);
				add_self(dp[curr][j][nval], val);
				// Here [] number is its own group
				// []
				add_self(dp[curr][j + 1][nval], val);
				// Open a new group with minimum arr[i]
				// [
				if (j > 0)
					add_self(dp[curr][j - 1][nval], j * val % mod);
				// Here we insert arr[i] in one of the open groups
				// ]
				if (j > 0)
					add_self(dp[curr][j][nval], j * val % mod);
				// Close an open group by insertng arr[i] in one of them
				// defauly case
			}
	}
	int ans = 0;
	for (int i = 0; i <= v; ++i)
		add_self(ans, dp[(n % 2) == 0][0][i]);
	cout << ans;
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