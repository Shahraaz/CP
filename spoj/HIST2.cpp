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

const int nax = 17;
int n;
int Vect[nax];
ll dp[nax][1 << nax], ways[nax][1 << nax];

ll solve(int idx, int mask)
{
	int cnt = __builtin_popcount(mask);
	if (cnt == n)
	{
		// db(cnt, idx, mask);
		ways[idx][mask] = 1;
		return dp[idx][mask] = Vect[idx];
	}
	ll &ret = dp[idx][mask];
	if (ret >= 0)
		return ret;
	ret = 0;
	ways[idx][mask] = 0;
	for (int j = 0; j < n; ++j)
	{
		if (mask & (1 << j))
			continue;
		ll area = abs(Vect[idx] - Vect[j]) + solve(j, mask | (1 << j));
		if (area == ret)
			ways[idx][mask] += ways[j][mask | (1 << j)];
		else if (area > ret)
		{
			ret = area;
			ways[idx][mask] = ways[j][mask | (1 << j)];
		}
	}
	db(ret, ways[idx][mask], idx, cnt, mask);
	return ret;
}

void solve()
{
	for (int i = 0; i < n; ++i)
		cin >> Vect[i];
	ll area, cnt;
	area = cnt = 0;
	memset(dp, -1, sizeof(dp));
	memset(ways, 0, sizeof(ways));
	for (int i = 0; i < n; ++i)
	{
		int mask = (1 << i);
		ll currArea = Vect[i] + solve(i, mask);
		if (area == currArea)
		{
			db(i, area, ways[i][mask]);
			cnt += ways[i][mask];
		}
		else if (currArea > area)
		{
			area = currArea;
			cnt = ways[i][mask];
			db(i, area, ways[i][mask]);
		}
	}
	cout << 2 * n + area << ' ' << cnt << '\n';
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (cin >> n, n > 0)
		solve();
#ifdef TIME
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}