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

const int N = 18;
ld p[N][N];
ld dp[N][1 << N];
int n;

ld solve(int mask, int winner)
{
	ld &ret = dp[winner][mask], curr;
	if (ret >= (-0.5))
		return ret;
	if (mask == (1 << n) - 1)
		return ret = winner == 0;
	ret = 0;
	for (int j = 0; j < n; ++j)
		if (!(mask & (1 << j)))
		{
			curr = 0;
			curr += p[winner][j] * solve(mask | (1 << j), winner);
			curr += p[j][winner] * solve(mask | (1 << j), j);
			ret = max(ret, curr);
		}
	return ret;
}

void solve()
{
	memset(dp, -1, sizeof(dp));
	cin >> n;
	if (n == 1)
	{
		cout << 1;
		return;
	}
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> p[i][j];
	ld ans = 0, curr;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < i; ++j)
		{
			curr = 0;
			curr += p[i][j] * solve((1 << i) | (1 << j), i);
			curr += p[j][i] * solve((1 << i) | (1 << j), j);
			ans = max(ans, curr);
		}
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