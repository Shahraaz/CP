//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
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

vector<vector<int>> G;
int n, m;
vector<int> MatchR;
vector<bool> Vis;

bool bpm(int u)
{
	for (int v = 0; v < m; ++v)
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

int maxFlow()
{
	fill(MatchR.begin(), MatchR.end(), -1);
	int ret = 0;
	for (int i = 0; i < n; ++i)
	{
		fill(Vis.begin(), Vis.end(), false);
		ret += bpm(i);
	}
	return ret;
}

void solve()
{
	cin >> n >> m;
	G.clear();
	vector<string> GS(n);
	for (auto &x : GS)
		cin >> x;
	vector<vector<int>> V(n, vector<int>(m, -1));
	vector<vector<int>> H(n, vector<int>(m, -1));
	int v1, v2;
	v1 = v2 = -1;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if (GS[i][j] == '*')
			{
				if (j == 0 || H[i][j - 1] == -1)
					H[i][j] = ++v1;
				else
					H[i][j] = H[i][j - 1];
				if (i == 0 || V[i - 1][j] == -1)
					V[i][j] = ++v2;
				else
					V[i][j] = V[i - 1][j];
			}
	// db("here")
	if (v1 == -1)
		cout << 0 << '\n';
	else
	{
		v1++;
		v2++;
		G.resize(v1, vector<int>(v2));
		MatchR.resize(v2);
		Vis.resize(v2);
		db(v1, v2);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
			{
				if (GS[i][j] == '*')
				{
					// db(i, j, H[i][j], V[i][j]);
					G[H[i][j]][V[i][j]] = 1;
				}
			}
		n = v1;
		m = v2;
		cout << maxFlow() << '\n';
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
