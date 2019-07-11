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

const int nax = 2e5 + 10;
int n;

ll dp[nax][10];
vector<ll> choice[nax][4];

ll solve(int i, int pos)
{
	if (i == n)
		return 0;
	ll &ret = dp[i][pos];
	if (ret >= 0)
		return ret;
	ret = solve(i + 1, pos);	  // No Play
	if (choice[i][1].size() >= 1) // Play 1 card of cost 1
	{
		int next = pos + 1;
		if (next == 10)
			ret = max(ret, choice[i][1][0] * 2 + solve(i + 1, 0));
		else
			ret = max(ret, choice[i][1][0] + solve(i + 1, next));
	}
	if (choice[i][1].size() >= 2) // Play 2 card of cost 1
	{
		int next = pos + 2;
		if (next > 9)
			ret = max(ret, choice[i][1][0] * 2 + choice[i][1][1] + solve(i + 1, next % 10));
		else
			ret = max(ret, choice[i][1][0] + choice[i][1][1] + solve(i + 1, next));
	}
	if (choice[i][1].size() >= 3) // Play 3 card of cost 1
	{
		int next = pos + 3;
		if (next > 9)
			ret = max(ret, choice[i][1][0] * 2 + choice[i][1][1] + choice[i][1][2] + solve(i + 1, next % 10));
		else
			ret = max(ret, choice[i][1][0] + choice[i][1][1] + choice[i][1][2] + solve(i + 1, next));
	}
	if (choice[i][2].size() >= 1) // Play 1 card of cost 2
	{
		int next = pos + 1;
		if (next == 10)
			ret = max(ret, choice[i][2][0] * 2 + solve(i + 1, 0));
		else
			ret = max(ret, choice[i][2][0] + solve(i + 1, next));
	}
	if (choice[i][1].size() >= 1 && choice[i][2].size() >= 1) // Play 2 card of cost 1 + 2
	{
		int next = pos + 2;
		ll maxi = max(choice[i][1][0], choice[i][2][0]);
		ll mini = min(choice[i][1][0], choice[i][2][0]);
		if (next > 9)
			ret = max(ret, maxi * 2 + mini + solve(i + 1, next % 10));
		else
			ret = max(ret, maxi + mini + solve(i + 1, next));
	}
	if (choice[i][3].size() >= 1) // Play 1 card of cost 3
	{
		int next = pos + 1;
		if (next == 10)
			ret = max(ret, choice[i][3][0] * 2 + solve(i + 1, 0));
		else
			ret = max(ret, choice[i][3][0] + solve(i + 1, next));
	}
	db(i, pos, ret);
	return ret;
}

void solve()
{
	cin >> n;
	ll k, c, d;
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < n; ++i)
	{
		cin >> k;
		for (int j = 0; j < k; ++j)
		{
			cin >> c >> d;
			choice[i][c].pb(d);
		}
		sort(choice[i][1].rbegin(), choice[i][1].rend());
		sort(choice[i][2].rbegin(), choice[i][2].rend());
		sort(choice[i][3].rbegin(), choice[i][3].rend());
	}
	cout << solve(0, 0) << '\n';
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