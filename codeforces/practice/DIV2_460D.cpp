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

const int nax = 3e5 + 10;
int n, m;
vector<int> Adj[nax];
vector<int> vis(nax), seq, dp(nax);
string key;

bool findLoop(int node)
{
	if (vis[node] == 2)
		return false;
	if (vis[node] == 1)
		return true;
	vis[node] = 1;
	for (auto child : Adj[node])
		if (findLoop(child))
			return true;
	vis[node] = 2;
	seq.pb(node);
	return false;
}

void solve()
{
	cin >> n >> m;
	cin >> key;
	key = '$' + key;
	int u, v;
	for (int i = 0; i < m; ++i)
	{
		cin >> u >> v;
		Adj[u].pb(v);
	}
	for (int i = 1; i <= n; ++i)
		if (!vis[i])
			if (findLoop(i))
			{
				cout << -1;
				return;
			}
	int ret = 0;
	for (int i = 'a'; i <= 'z'; ++i)
		for (int j = 0; j < seq.size(); ++j)
		{
			int v = seq[j];
			int my = key[v] == i;
			dp[v] = my;
			for (auto child : Adj[v])
				dp[v] = max(dp[v], dp[child] + my);
			ret = max(ret, dp[v]);
		}
	cout << ret << '\n';
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
	cout << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}