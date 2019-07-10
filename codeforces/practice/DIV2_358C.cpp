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

typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
const long long mod = 1000000007;
auto TimeStart = chrono::steady_clock::now();

const int nax = 1e5 + 10;
vector<int> Size(nax), Vertex(nax);
vector<pair<int, int>> Adj[nax];
int n, a, b;

int solve(int node, int parent, int dist)
{
	int toremove = 0;
	for (auto child : Adj[node])
	{
		if (child.f == parent)
			continue;
		db(child.s, Vertex[child.f]);
		int virtualDist = max(child.s, dist + child.s);
		if (virtualDist > Vertex[child.f])
		// Cut the sub Tree Off
		{
			db("Cutting SUbTree Off", child.f, Size[child.f]);
			toremove += Size[child.f];
		}
		else
			toremove += solve(child.f, node, virtualDist); // Check if there is need to cut
	}
	db(node, toremove);
	return toremove;
}

int dfs(int node, int parent)
{
	Size[node] = 1;
	for (auto child : Adj[node])
		if (child.f != parent)
			Size[node] += dfs(child.f, node);
	// db(node, Size[node]);
	return Size[node];
}

void solve()
{
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> Vertex[i];
	for (int i = 1; i < n; ++i)
	{
		cin >> a >> b;
		// db(a, i + 1, b);
		Adj[a].emplace_back(i + 1, b);
		Adj[i + 1].emplace_back(a, b);
	}
	dfs(1, 0);
	cout << solve(1, 0, 0) << '\n';
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