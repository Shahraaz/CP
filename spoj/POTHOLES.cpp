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

vector<vector<int>> G;
vector<int> P;
vector<bool> Vis;

int flow(int source, int sink)
{
	fill(P.begin(), P.end(), -1);
	fill(Vis.begin(), Vis.end(), false);
	queue<int> Q;
	Q.push(source);
	Vis[source] = true;
	while (!Q.empty())
	{
		auto t = Q.front();
		Q.pop();
		// db(t)
		if (t == sink)
			break;
		for (int i = 1; i <= sink; ++i)
		{
			if (!Vis[i] && G[t][i] > 0)
			{
				// db(t,i)
				Vis[i] = true;
				Q.push(i);
				P[i] = t;
			}
		}
	}
	int curr = sink, flow = INT_MAX;
	while (P[curr] != -1)
	{
		// cout << curr << ' ' << P[curr] << '\n';
		flow = min(flow, G[P[curr]][curr]);
		curr = P[curr];
	}
	curr = sink;
	while (P[curr] != -1)
	{
		G[P[curr]][curr] -= flow;
		G[curr][P[curr]] += flow;
		curr = P[curr];
	}
	return flow == INT_MAX ? 0 : flow;
}

void solve()
{
	int n, m, u;
	cin >> n;
	G.clear();
	G.resize(n + 1, vector<int>(n + 1));
	P.clear();
	P.resize(n + 1);
	Vis.clear();
	Vis.resize(n + 1);
	for (int i = 1; i < n; ++i)
	{
		cin >> m;
		while (m--)
		{
			cin >> u;
			// db(u)
			if (i == 1 || u == n)
				G[i][u] = 1;
			else
				G[i][u] = INT_MAX;
		}
		// db(i)
		// for(int j=1;j<=n;++j)
		// 	db(G[i][j]);	
	}
	int tot_flow = 0, curr_flow;
	while (curr_flow = flow(1, n))
	{
		// db(curr_flow)
		tot_flow += curr_flow;
	}
	cout << tot_flow << '\n';
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