//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
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
const long long mod = 10007;
auto TimeStart = chrono::steady_clock::now();

const int nax = 100020;
vector<int> Adj[nax];
int n, u, v;
int numOfOptimal[nax], numOfOptimalCnt[nax];
int numOfWithNode[nax], numOfWithNodeCnt[nax];

void add_self(int &a, int b)
{
	a += b;
	if (a >= mod)
		a -= mod;
}

int mul(int a, int b)
{
	return (ll)a * b % mod;
}

void dfs(int node, int p)
{
	int withNode = 1, withNodeCnt = 1;
	int withOutNode = 0, withOutNodeCnt = 1;
	for (int child : Adj[node])
	{
		if (child == p)
			continue;
		dfs(child, node);
		withNode += numOfOptimal[child];
		withNodeCnt = mul(withNodeCnt, numOfOptimalCnt[child]);
		withOutNode += numOfWithNode[child];
		withOutNodeCnt = mul(withOutNodeCnt, numOfWithNodeCnt[child]);
	}
	numOfWithNode[node] = withNode;
	numOfWithNodeCnt[node] = withNodeCnt;
	if (withNode < withOutNode)
	{
		numOfOptimal[node] = withNode;
		numOfOptimalCnt[node] = withNodeCnt;
	}
	else if (withNode > withOutNode)
	{
		numOfOptimal[node] = withOutNode;
		numOfOptimalCnt[node] = withOutNodeCnt;
	}
	else
	{
		numOfOptimal[node] = withOutNode;
		numOfOptimalCnt[node] = withOutNodeCnt;
		add_self(numOfOptimalCnt[node], withNodeCnt);
	}
	db(node, numOfOptimal[node], numOfOptimalCnt[node]);
}

void solve()
{
	db("Here");
	cin >> n;
	for (int i = 1; i <= n; ++i)
		Adj[i].clear();
	for (int i = 1; i < n; ++i)
	{
		cin >> u >> v;
		Adj[u].pb(v);
		Adj[v].pb(u);
	}
	db("Input");
	dfs(1, 0);
	db("Dfs");
	cout << numOfOptimal[1] << ' ' << numOfOptimalCnt[1] << '\n';
	db("Output");
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
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}