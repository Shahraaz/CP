//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
// #define multitest 1
// #define Debug 1
typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
#define mp make_pair
const long long mod = 1000000007;
const long long High = 1e16;
void ControlIO();
void TimerStart();
void TimerStop();
#ifdef Debug
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__)
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

auto TimeStart = chrono::steady_clock::now();
auto TimeEnd = chrono::steady_clock::now();
typedef pair<long long, int> pil;
typedef vector<pair<int, long long>> __vil;
typedef vector<int> __vi;
typedef vector<__vil> __Graph;

pair<long long, __vi> Dijkstart(__Graph input, int src, int dest)
{
	int n = input.size();
	vector<long long> Dist(n, LLONG_MAX), prev(n, -1);
	Dist[src] = 0;
	priority_queue<pil, vector<pil>, greater<pil>> Q;
	Q.push({src, 0});
	while (!Q.empty())
	{
		auto t = Q.top();
		Q.pop();
		if (Dist[t.s] != t.f)
			continue;
		if (t.s == dest)
			break;
		int u = t.s;
		for (auto v : input[u])
			if (Dist[v.f] > (Dist[u] + v.s))
			{
				// db(v.f);
				prev[v.f] = u;
				Dist[v.f] = Dist[u] + v.s;
				Q.push({Dist[v.f], v.f});
			}
	}
	vector<int> Path;
	if (prev[dest] == (-1))
		;
	else
	{
		int u = dest;
		stack<int> S;
		S.push(u);
		while (prev[u] != (-1))
		{
			u = prev[u];
			S.push(u);
		}
		while (!S.empty())
		{
			Path.push_back(1 + S.top());
			S.pop();
		}
	}
	db(Dist[dest]);
	return {Dist[dest], Path};
}

typedef vector<pair<int, ll>> _vi;
typedef vector<_vi> Graph;
void solve()
{
	ll n, m, u, v, w;
	cin >> n >> m;
	Graph G(n), FullG(n);
	while (m--)
	{
		cin >> u >> v >> w;
		u--;
		v--;
		G[u].pb(mp(v, w));
		FullG[u].pb(mp(v, w));
		FullG[u].pb(mp(v, w));
		//G[v].pb(mp(u, w));
	}
	auto Dir = Dijkstart(G, 0, n - 1);
	auto UnDir = Dijkstart(FullG, 0, n - 1);
	if (rand() % 2)
		swap(Dir, UnDir);
	if (Dir.s.size() == 0)
	{
		cout << 0;
		return;
	}
	cout << 1 << '\n';
	cout << Dir.s.size() << ' ';
	for (auto x : Dir.s)
		cout << x << ' ';
}

int main()
{
	srand(time(NULL));
	TimeStart = chrono::steady_clock::now();
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