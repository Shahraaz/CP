//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
// #define multitest 1
#define Debug 1
void ControlIO();
void TimerStart();
void TimerStop();
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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

vector<vector<int>> G;
typedef complex<ll> point;
vector<pair<point, ll>> Circles;

bool contains(int i, int j)
{
	return norm(Circles[i].f - Circles[j].f) <= (Circles[i].s - Circles[j].s) * (Circles[i].s - Circles[j].s);
}

ll f[1004][2][2];

void dfs_dp(int u)
{
	ll g[2][2] = {{0}};
	for (int v : G[u])
	{
		dfs_dp(v);
		g[0][0] += f[v][0][0];
		g[0][1] += f[v][0][1];
		g[1][0] += f[v][1][0];
		g[1][1] += f[v][1][1];
	}
	f[u][0][0] = max(g[1][0] + Circles[u].s * Circles[u].s, g[0][1] + Circles[u].s * Circles[u].s);
	db(u, f[u][0][0])
		f[u][1][0] = max(g[0][0] - Circles[u].s * Circles[u].s, g[1][1] + Circles[u].s * Circles[u].s);
	db(u, f[u][1][0])
		f[u][0][1] = max(g[1][1] + Circles[u].s * Circles[u].s, g[0][0] - Circles[u].s * Circles[u].s);
	db(u, f[u][0][1])
		f[u][1][1] = max(g[0][1] - Circles[u].s * Circles[u].s, g[1][0] - Circles[u].s * Circles[u].s);
	db(u, f[u][1][1])
}

void solve()
{
	int n, x, y, r;
	cin >> n;
	G.resize(n);
	Circles.resize(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> x >> y >> r;
		Circles[i].f = point(x, y);
		Circles[i].s = r;
	}
	// db("input")
	queue<int> Q;
	for (int i = 0; i < n; ++i)
	{
		int par = -1;
		for (int j = 0; j < n; ++j)
			if (Circles[j].s > Circles[i].s && contains(i, j))
				if (par == -1 || Circles[par].s > Circles[j].s)
					par = j;
		if (par == -1)
			Q.push(i);
		else
			G[par].pb(i);
	}
	// db("graph making")
	ll ans = 0;
	while (!Q.empty())
	{
		auto u = Q.front();
		Q.pop();
		dfs_dp(u);
		ans += f[u][0][0];
	}
	// db("input")
	cout << fixed << setprecision(15) << acosl(-1) * ans << '\n';
}

int main()
{
	ControlIO();
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	TimerStart();
	while (t--)
		solve();
	TimerStop();
	return 0;
}

void ControlIO()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#ifndef Online
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
}

auto TimeStart = chrono::steady_clock::now();
auto TimeEnd = chrono::steady_clock::now();

void TimerStart()
{
#ifndef Online
	TimeStart = chrono::steady_clock::now();
#endif
}

void TimerStop()
{
#ifndef Online
	TimeEnd = chrono::steady_clock::now();
	auto ElapsedTime = TimeEnd - TimeStart;
	cout << "\n\nTime elapsed: " << chrono::duration<double>(ElapsedTime).count() << " seconds.\n";
#endif
}