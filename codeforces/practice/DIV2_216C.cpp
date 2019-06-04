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

typedef vector<pair<int, int>> vi;
typedef vector<vi> G;

G graph;
vector<int> answer;
int dfs(int node, int parent)
{
	int a = 0;
	for (auto child : graph[node])
	{
		if (child.f == parent)
			continue;
		auto b = dfs(child.f, node);
		// db(node,child.f,b);
		if (child.s)
		{
			if (b == 0)
			{
				a++;
				answer.pb(child.f);
			}
			else
				a += b;
		}
		else
			a += b;
	}
	return a;
}

void solve()
{
	int n, u, v, t;
	cin >> n;
	graph.resize(n);
	for (int i = 1; i < n; ++i)
	{
		cin >> u >> v >> t;
		u--;
		v--;
		t--;
		graph[u].pb({v, t});
		graph[v].pb({u, t});
	}
	dfs(0,-1);
	cout << answer.size() << '\n';
	for (auto x : answer)
		cout << x + 1 << ' ';
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