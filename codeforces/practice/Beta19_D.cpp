//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define multitest 1
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

const int N = 2e5 + 10;
vector<int> Tree(4 * N, -1), x(N), y(N);
vector<multiset<int>> st(N);

void add(int node, int start, int end, int pos, int val)
{
	if (start == end)
	{
		Tree[node] = val;
		return;
	}
	int mid = (start + end) / 2;
	if (pos <= mid)
		add(2 * node, start, mid, pos, val);
	else
		add(2 * node + 1, mid + 1, end, pos, val);
	Tree[node] = max(Tree[node * 2], Tree[node * 2 + 1]);
}

int get(int node, int start, int end, int qstart, int qend)
{
	// db(node, start, end);
	if (start > end || qstart > end || qend < start)
		return -1;
	if (qstart <= start && end <= qend)
		return Tree[node];
	int mid = (start + end) / 2, ret = -1;
	ret = max(ret, get(2 * node, start, mid, qstart, qend));
	ret = max(ret, get(2 * node + 1, mid + 1, end, qstart, qend));
	return ret;
}

int Get(int node, int start, int end, int idx, int val)
{
	db(node, start, end, idx, val);
	if (start == end)
		return start;
	int mid = (start + end) / 2;
	if (idx > mid)
		return Get(2 * node + 1, mid + 1, end, idx, val);
	if (get(1, 0, N, idx, mid) >= val)
		return Get(2 * node, start, mid, idx, val);
	return Get(2 * node + 1, mid + 1, end, idx, val);
}

void solve()
{
	int n;
	cin >> n;
	vector<string> S(n);
	vector<int> x(n), y(n), tot(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> S[i] >> x[i] >> y[i];
		tot[i] = x[i];
	}
	sort(tot.begin(), tot.end());
	tot.resize(unique(tot.begin(), tot.end()) - tot.begin());
	for (int i = 0; i < n; ++i)
		x[i] = lower_bound(tot.begin(), tot.end(), x[i]) - tot.begin();
	for (int i = 0; i < n; ++i)
	{
		db("one", i);
		if (S[i][0] == 'a')
		{
			st[x[i]].insert(y[i]);
			auto it = --st[x[i]].end();
			add(1, 0, N - 1, x[i], *it);
		}
		else if (S[i][0] == 'r')
		{
			st[x[i]].erase(st[x[i]].lower_bound(y[i]));
			if (st[x[i]].size())
			{
				auto it = --st[x[i]].end();
				add(1, 0, N - 1, x[i], *it);
			}
			else
				add(1, 0, N - 1, x[i], -1);
		}
		else
		{
			if (get(1, 0, N - 1, x[i] + 1, N - 1) < y[i] + 1)
				cout << -1 << '\n';
			else
			{
				db("Part 2 Start");
				int idx = Get(1, 0, N - 1, x[i] + 1, y[i] + 1);
				cout << tot[idx] << ' ' << (*st[idx].upper_bound(y[i])) << '\n';
				db("Part 2 End");
			}
		}
	}
}

int main()
{
#ifndef Debug
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#endif
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (t--)
		solve();
	return 0;
}