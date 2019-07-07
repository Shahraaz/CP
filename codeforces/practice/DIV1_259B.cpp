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

const int maxN = 101;
int n, cnt;
int a[maxN], sieve[maxN], numMask[maxN];
int cache[maxN][1 << 17];

int dp(int i, int mask)
{
	// db(i, mask, mask < (1 << 17));
	if (i == n + 1)
		return 0;
	int &ret = cache[i][mask];
	if (ret >= 0)
		return ret;
	ret = abs(a[i] - 1) + dp(i + 1, mask);
	for (int j = 2; j <= 60; ++j)
		if (!(mask & numMask[j]))
			ret = min(ret, abs(a[i] - j) + dp(i + 1, mask | numMask[j]));
	return ret;
}

void path(int i, int mask)
{
	if (i == n + 1)
		return;
	int ans = dp(i, mask);
	if (ans == (abs(a[i] - 1) + dp(i + 1, mask)))
	{
		cout << 1 << ' ';
		path(i + 1, mask);
	}
	else
	{
		for (int j = 2; j <= 60; ++j)
			if (!(mask & numMask[j]) && ans == (abs(a[i] - j) + dp(i + 1, mask | numMask[j])))
			{
				db(mask, mask & numMask[j]);
				cout << j << ' ';
				path(i + 1, mask | numMask[j]);
				return;
			}
	}
}

void solve()
{
	memset(cache, -1, sizeof(cache));
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	fill(sieve, sieve + maxN, 1);
	for (int i = 2; i < 61; ++i)
	{
		if (sieve[i])
		{
			for (int j = i; j < 61; j += i)
			{
				sieve[j] = 0;
				numMask[j] |= (1LL << cnt);
			}
			cnt++;
		}
	}
	dp(1, 0);
	path(1, 0);
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