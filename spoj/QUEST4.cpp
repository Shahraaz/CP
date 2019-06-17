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
vector<int> MatchR(121);
vector<bool> Vis(121);

bool bpm(int u)
{
	for (int v = 0; v <= 120; ++v)
		if (G[u][v] && !Vis[v])
		{
			Vis[v] = true;
			if (MatchR[v] < 0 || bpm(MatchR[v]))
			{
				MatchR[v] = u;
				return true;
			}
		}
	return false;
}

int findMaxMatching()
{
	fill(MatchR.begin(), MatchR.end(), -1);
	int ret = 0;
	for (int u = 0; u <= 120; ++u)
	{
		fill(Vis.begin(), Vis.end(), false);
		ret += bpm(u);
		// db(u,ret);
	}
	return ret;
}

void solve()
{
	int n, x, y;
	cin >> n;
	G.clear();
	G.resize(121, vector<int>(121));
	for (int i = 0; i < n; ++i)
	{
		cin >> x >> y;
		G[x][y] = 1;
	}
	cout << findMaxMatching() << '\n';
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