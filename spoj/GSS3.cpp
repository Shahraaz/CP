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

vector<int> data;
struct Data
{
	int sum, maxLsum, maxRsum, maxSum;
	Data(int val = 0)
	{
		sum = maxLsum = maxRsum = maxSum = val;
	}
};

vector<Data> Tree;

void calc(int node)
{
	auto &par = Tree[node], &l = Tree[2 * node], &r = Tree[2 * node + 1];
	par.sum = l.sum + r.sum;
	par.maxLsum = max(l.maxLsum, l.sum + r.maxLsum);
	par.maxRsum = max(r.maxRsum, r.sum + l.maxRsum);
	par.maxSum = max(l.maxSum, r.maxSum);
	par.maxSum = max(par.maxSum, l.maxRsum + r.maxLsum);
	db(node, par.sum, par.maxLsum, par.maxRsum, par.maxSum);
}

void build(int node, int start, int end)
{
	if (start == end)
	{
		Tree[node] = Data(data[start]);
		return;
	}
	int mid = (start + end) / 2;
	build(2 * node, start, mid);
	build(2 * node + 1, mid + 1, end);
	calc(node);
}

void update(int node, int start, int end, int p, int newVal)
{
	if (start == end)
	{
		Tree[node] = Data(newVal);
		return;
	}
	int mid = (start + end) / 2;
	if (p <= mid)
		update(2 * node, start, mid, p, newVal);
	else
		update(2 * node + 1, mid + 1, end, p, newVal);
	calc(node);
}

vector<int> nodeList;

void query(int node, int start, int end, int left, int right)
{
	db(start, end, left, right);
	if (left <= start && end <= right)
	{
		nodeList.pb(node);
		return;
	}
	int mid = (start + end) / 2;
	if (left <= mid && start <= right)
		query(2 * node, start, mid, left, right);
	if (left <= end && (mid + 1) <= right)
		query(2 * node + 1, mid + 1, end, left, right);
}

int Query(int start, int end, int left, int right)
{
	nodeList.clear();
	query(1, start, end, left, right);
	int res = -2e9, t = -2e9;
	db(nodeList.size());
	for (int i = 0; i < nodeList.size(); ++i)
	{
		auto T = Tree[nodeList[i]];
		res = max(res, T.maxSum);
		res = max(res, t + T.maxLsum);
		t = max(t + T.sum, T.maxRsum);
	}
	return res;
}

void solve()
{
	int n;
	cin >> n;
	data.resize(n);
	Tree.resize(4 * n);
	for (auto &x : data)
		cin >> x;
	build(1, 0, n - 1);
	int m, c, x, y;
	cin >> m;
	while (m--)
	{
		cin >> c >> x >> y;
		if (c)
			cout << Query(0, n - 1, x - 1, y - 1) << '\n';
		else
			update(1, 0, n - 1, x - 1, y);
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