//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
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

int n, m, u, v, dfstime;
vector<int> idx(1e5 + 5), low(1e5 + 5), Vis(1e5 + 5);
vector<vector<int>> cost(2, vector<int>(1e5 + 5)), G;
set<int> ap;

void dfs(int u, int p)
{
	idx[u] = low[u] = dfstime++;
	int childCnt = 0;
	for (int i = 0, v; i < G[u].size(); ++i)
	{
		v = G[u][i];
		if (idx[v] == -1)
		{
			childCnt++;
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if (p == -1 && childCnt > 1)
				ap.insert(u);
			else if (p != -1 && low[v] >= idx[u])
				ap.insert(u);
		}
		else if (p != v)
			low[u] = min(low[u], low[v]);
	}
}

void BFS(int src, int idx)
{
	fill(cost[idx].begin(), cost[idx].end(), 0);
	fill(Vis.begin(), Vis.end(), 0);
	queue<int> Q;
	Q.push(src);
	while (!Q.empty())
	{
		auto fr = Q.front();
		Q.pop();
		if (Vis[fr])
			continue;
		Vis[fr] = true;
		for (auto v : G[fr])
		{
			cost[idx][v] = cost[idx][fr] + 1;
			Q.push(v);
		}
	}
}

void solve()
{
	cin >> n >> m;
	G.clear();
	G.resize(n);
	for (int i = 0; i < m; ++i)
	{
		cin >> u >> v;
		--u;
		--v;
		G[u].pb(v);
		G[v].pb(u);
	}
	fill(idx.begin(), idx.end(), -1);
	ap.clear();
	dfstime = 0;
	dfs(0, -1);
	if (ap.empty())
		cout << n << '\n';
	else
	{
		BFS(0, 0);
		BFS(n - 1, 1);
		int v1 = 1e9, v2 = -1e9, i, v;
		for (auto it = ap.begin(); it != ap.end(); ++it)
		{
			v = *it;
			if (cost[0][v] < v1 && cost[1][v] > v2)
			{
				i = v;
				v1 = cost[0][v];
				v2 = cost[1][v];
			}
		}
		cout << i + 1 << '\n';
	}
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
	return 0;
}