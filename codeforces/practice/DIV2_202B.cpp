//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define multitest 1
#define Debug 1
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

void solve()
{
	vector<int> Paint(10);
	int v, mincost = INT_MAX, minidx;
	cin >> v;
	for (int i = 1; i <= 9; ++i)
	{
		cin >> Paint[i];
		if (mincost >= Paint[i])
		{
			mincost = Paint[i];
			minidx = i;
		}
	}
	// cout << mincost;
	int maxlen = v / mincost;
	if (maxlen == 0)
		cout << -1;
	else
	{
		vector<int> ToPrint(maxlen, minidx);
		int rem = v % mincost, len = 0;
		for (int high = 9; high > minidx && len < maxlen; --high)
		{
			int extraneeded = Paint[high] - Paint[minidx];
			while (rem>=extraneeded && len < maxlen)
			{
				ToPrint[len++] = high;
				rem -= extraneeded;
			}
		}
		for (auto x : ToPrint)
			cout << x;
	}
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