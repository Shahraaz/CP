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

const int N = 2e6, Log = 30;
const int V = N * Log;

int sz, nt[2][V], cnt[V];

void clear()
{
	for (int i = 0; i < V; ++i)
	{
		cnt[i] = 0;
		nt[1][i] = nt[0][i] = -1;
	}
	sz = 1;
}

void add(int x)
{
	int v = 0;
	cnt[v]++;
	for (int i = Log; i >= 0; --i)
	{
		bool b = x & (1 << i);
		if (nt[b][v] == -1)
			nt[b][v] = sz++;
		v = nt[b][v];
		cnt[v]++;
	}
}

int getCnt(int v)
{
	if (v == -1)
		return 0;
	return cnt[v];
}

int calc(int x, int k)
{
	int v = 0;
	int ans = 0;
	int cur = 0;
	for (int i = Log; i >= 0; --i)
	{
		if (v == -1)
			break;
		bool b = x & (1 << i);
		if ((cur | (1 << i)) >= k)
		{
			ans += getCnt(nt[!b][v]);
			v = nt[b][v];
		}
		else
		{
			v = nt[!b][v];
			cur |= (1 << i);
		}
	}
	if (cur >= k)
		ans += getCnt(v);
	return ans;
}

void solve()
{
	clear();
	int n, k;
	cin >> n >> k;
	add(0);
	int s = 0, x;
	ll ans = 0;
	for (int i = 0; i < n; ++i)
	{
		cin >> x;
		s ^= x;
		ans += calc(s, k);
		add(s);
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