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

vector<vector<int>> Adj;
vector<ll> add, sub, val;

void dfs(int node, int parent)
{
	ll &p = add[node], &m = sub[node];
	for (auto child : Adj[node])
		if (child != parent)
		{
			dfs(child, node);
			p = max(p, add[child]);
			m = max(m, sub[child]);
		}
	ll delta = val[node] + p - m;
	if (delta >= 0)
		m += delta;
	else
		p += -delta;
	db(p,m,node);
}

void solve()
{
	int n, u, v;
	cin >> n;
	Adj.resize(n);
	add.resize(n);
	sub.resize(n);
	val.resize(n);
	for (int i = 1; i < n; ++i)
	{
		cin >> u >> v;
		u--;
		v--;
		Adj[u].pb(v);
		Adj[v].pb(u);
	}
	for (int i = 0; i < n; ++i)
		cin >> val[i];
	dfs(0, -1);
	cout << add[0] + sub[0] << '\n';
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