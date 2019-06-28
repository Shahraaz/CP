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

const int N = 1e6 + 6;

vector<vector<int>> Tree(4 * N);
vector<ll> a(N);
int x, y;

vector<int> getFactors(int num)
{
	db("Start", num);
	vector<int> ret;
	while (num % 2 == 0)
	{
		ret.pb(2);
		num /= 2;
		db(2);
	}
	for (int i = 3; i * i <= num; i += 2)
		while (num % i == 0)
		{
			ret.pb(i);
			num /= i;
			db(i);
		}
	if (num != 1)
	{
		ret.pb(num);
		db(num);
	} 
	db("End", ret.size());
	return ret;
}

int cnt(int node)
{
	return upper_bound(Tree[node].begin(), Tree[node].end(), y) - lower_bound(Tree[node].begin(), Tree[node].end(), x);
}

vector<int> merge(vector<int> &l, vector<int> &r)
{
	vector<int> temp;
	int i = 0, j = 0;
	while (i < l.size() && j < r.size())
	{
		if (l[i] < r[j])
			temp.pb(l[i++]);
		else
			temp.pb(r[j++]);
	}
	while (i < l.size())
		temp.pb(l[i++]);
	while (j < r.size())
		temp.pb(r[j++]);
	return temp;
}

void build(int node, int start, int end)
{
	// db(node, start, end);
	if (start > end)
		return;
	if (start == end)
	{
		Tree[node] = getFactors(a[start]);
		db("Singular", node, Tree[node].size());
		return;
	}
	int mid = (start + end) / 2;
	build(node * 2, start, mid);
	build(node * 2 + 1, mid + 1, end);
	auto &l = Tree[node * 2];
	auto &r = Tree[node * 2 + 1];
	db("Merging start");
	Tree[node] = merge(l, r);
	db("Merging end");
	db("Merged", node, Tree[node].size());
}

int query(int node, int start, int end, int qstart, int qend)
{
	if (start > end || qend < start || qstart > end)
		return 0;
	if (qstart <= start && end <= qend)
		return cnt(node);
	int mid = (start + end) / 2;
	return query(2 * node, start, mid, qstart, qend) + query(2 * node + 1, mid + 1, end, qstart, qend);
}

void solve()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	build(1, 0, n - 1);
	int q, l, r;
	cin >> q;
	while (q--)
	{
		cin >> l >> r >> x >> y;
		cout << query(1, 0, n - 1, l - 1, r - 1) << '\n';
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