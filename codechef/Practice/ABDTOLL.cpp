//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
#define multitest 1
#define Debug 1
typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
const long long mod = 1000000007;
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

vector<vector<int>> Graph;
vector<ll> TollForThisCity, MaxCostToSolveThisSubTree;
ll answer;
ll n, x, k, u, v;

void DfsToCalculateMaxCostOfSolvingATree(int u, int parent)
{
	ll MaxCostForAnySubTree = 0;
	for (auto Child : Graph[u])
		if (Child != parent)
		{
			DfsToCalculateMaxCostOfSolvingATree(Child, u);
			MaxCostForAnySubTree = max(MaxCostForAnySubTree, MaxCostToSolveThisSubTree[Child]);
		}
	MaxCostToSolveThisSubTree[u] = TollForThisCity[u] + MaxCostForAnySubTree;
}

void dfsRefactor(int u, int parent, int CostPaidUpUntilHere)
{
	if (MaxCostToSolveThisSubTree[u] + CostPaidUpUntilHere > k)
	{
		ll temp = MaxCostToSolveThisSubTree[u] + CostPaidUpUntilHere - k;
		ll mn = min(TollForThisCity[u], temp);
		TollForThisCity[u] -= mn;
		answer += 2 * mn;
	}
	CostPaidUpUntilHere += TollForThisCity[u];
	for (auto Child : Graph[u])
		if (Child != parent)
			dfsRefactor(Child, u, CostPaidUpUntilHere);
}

void solve()
{
	cin >> n >> x >> k;
	x--;
	TollForThisCity.clear();
	Graph.clear();
	MaxCostToSolveThisSubTree.clear();
	TollForThisCity.resize(n);
	Graph.resize(n);
	MaxCostToSolveThisSubTree.resize(n);
	for (auto &Child : TollForThisCity)
		cin >> Child;
	for (int i = 1; i < n; ++i)
	{
		cin >> u >> v;
		u--;
		v--;
		Graph[u].pb(v);
		Graph[v].pb(u);
	}
	DfsToCalculateMaxCostOfSolvingATree(x, -1);
	answer = 0;
	dfsRefactor(x, -1, 0);
	cout << answer << '\n';
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