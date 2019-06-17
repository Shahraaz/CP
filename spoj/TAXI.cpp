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

typedef pair<int, int> point;
vector<point> Person(410), Taxi(410);
vector<vector<bool>> Adj;
vector<int> MatchR(410);
vector<bool> vis(410);
int p, t, s, c, x, y;

bool bpm(int u)
{
	for (int v = 0; v < t; ++v)
	{
		if (Adj[u][v] && !vis[v])
		{
			vis[v] = true;
			if (MatchR[v] < 0 || bpm(MatchR[v]))
			{
				MatchR[v] = u;
				return true;
			}
		}
	}
	return false;
}

int findMaxMatching()
{
	fill(MatchR.begin(), MatchR.end(), -1);
	// fill(right1.begin(), right1.end(), -1);
	int ret = 0;
	bool done;
	for (int u = 0; u < p; ++u)
	{
		fill(vis.begin(), vis.end(), false);
		if (bpm(u))
			ret++;
	}
	return ret;
}

int dist(point a, point b)
{
	return abs(a.f - b.f) + abs(a.s - b.s);
}

void solve()
{
	cin >> p >> t >> s >> c;
	Adj.clear();
	Adj.resize(p, vector<bool>(t));
	for (int i = 0; i < p; ++i)
	{
		cin >> x >> y;
		Person[i] = {x, y};
	}
	for (int i = 0; i < t; ++i)
	{
		cin >> x >> y;
		Taxi[i] = {x, y};
	}
	for (int i = 0; i < p; ++i)
		for (int j = 0; j < t; ++j)
			if ((200 * dist(Person[i], Taxi[j])) <= (s * c))
				Adj[i][j] = 1;
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