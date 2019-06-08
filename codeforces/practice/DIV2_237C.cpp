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
typedef pair<int, int> pii;

void solve()
{
	int n, k;
	cin >> n >> k;
	vector<vector<int>> Adj(n);
	vector<pii> atDist(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> atDist[i].f;
		atDist[i].s = i;
	}
	sort(atDist.begin(), atDist.end());
	priority_queue<pii, vector<pii>, greater<pii>> Heap;
	vector<queue<int>> Q(n);
	int root = -1;
	for (int i = 0; i < n; ++i)
	{
		Heap.push(atDist[i]);
		Q[atDist[i].f].push(atDist[i].s);
		if (atDist[i].f == 0)
		{
			if (root != -1)
			{
				cout << -1 << '\n';
				return;
			}
			root = atDist[i].s;
		}
	}
	if ((max_element(atDist.begin(), atDist.end())->f) > 1 && k == 1)
	{
		cout << -1 << '\n';
		return;
	}
	int e = 0;
	while (!Heap.empty())
	{
		auto top = Heap.top();
		Heap.pop();
		int level = top.f;
		int index = top.s;
		if (level == 0)
			continue;
		if (Q[level - 1].empty())
		{
			cout << -1 << '\n';
			return;
		}
		int index2 = Q[level - 1].front();
		Q[level - 1].pop();
		++e;
		Adj[index].pb(index2);
		Adj[index2].pb(index);
		if (Adj[index2].size() < k)
			Q[level - 1].push(index2);
	}
	cout << e << '\n';
	for (int i = 0; i < n; ++i)
		for (int j : Adj[i])
		{
			if (i < j)
				cout << i + 1 << ' ' << j + 1 << '\n';
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
	{
		solve();
		db("output");
	}
	return 0;
}