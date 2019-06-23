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

const int maxN = 1e5, maxBits = 60;
ll trie[2][maxN * maxBits];
int sz = 1;

void add(ll n)
{
	ll node = 0;
	for (int i = maxBits; i >= 0; --i)
	{
		bool b = !(n & (1LL << i));
		if (trie[b][node] == -1)
			trie[b][node] = sz++;
		node = trie[b][node];
	}
}

ll query(ll x)
{
	ll node, ans;
	node = ans = 0;
	for (int i = maxBits; i >= 0; --i)
	{
		bool b = !(x & (1LL << i));
		if (trie[!b][node] == -1)
			node = trie[b][node];
		else
		{
			ans |= (1LL << i);
			node = trie[!b][node];
		}
	}
	return ans;
}

void solve()
{
	memset(trie, -1, sizeof(trie));
	int n;
	cin >> n;
	vector<ll> a(n + 2), pre(n + 2), suf(n + 2);
	for (int i = 1; i <= n; ++i)
	{
		cin >> a[i];
		pre[i] = pre[i - 1] ^ a[i];
	}
	db("one");
	for (int i = n; i >= 1; --i)
		suf[i] = suf[i + 1] ^ a[i];
	ll ans = -1;
	for (int i = 1; i <= n; ++ i)
		ans = max(ans, max(suf[i], pre[i]));
	for (int i = 2; i <= n; ++i)
	{
		db("one",i);
		add(pre[i - 1]);
		ans = max(ans, query(suf[i]));
	}
	cout << ans << '\n';
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