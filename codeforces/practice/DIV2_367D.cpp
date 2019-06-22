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

const int maxBits = 40;
const int maxN = 2e5 + 32;

int cnt[maxN * maxBits], sz;
int nxt[2][maxBits * maxN];

void insert(int x)
{
	int curr = 0;
	for (int i = 30; i >= 0; --i)
	{
		bool z = x & (1 << i);
		if (!nxt[z][curr])
			nxt[z][curr] = ++sz;
		curr = nxt[z][curr];
		cnt[curr]++;
	}
}

void remove(int x)
{
	int curr = 0;
	for (int i = 30; i >= 0; --i)
	{
		bool z = x & (1 << i);
		if (!nxt[z][curr])
			nxt[z][curr] = ++sz;
		curr = nxt[z][curr];
		cnt[curr]--;
	}
}

int query(int x)
{
	int curr = 0, ret = 0;
	for (int i = 30; i >= 0; --i)
	{
		bool z = x & (1 << i);
		if (cnt[nxt[!z][curr]])
		{
			ret |= 1 << i;
			curr = nxt[!z][curr];
		}
		else
			curr = nxt[z][curr];
	}
	return ret;
}

void solve()
{
	int q, x;
	cin >> q;
	char rc;
	insert(0);
	while (q--)
	{
		cin >> rc >> x;
		if (rc == '+')
			insert(x);
		else if (rc == '-')
			remove(x);
		else
			cout << query(x) << '\n';
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