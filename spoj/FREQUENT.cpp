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

vector<int> a(100005);

struct segment
{
	pair<int, int> M, left, right; // f for value, s for count
} Tree[4 * 100005];

void clear(int n)
{
	db(n);
	for (int i = 0; i < 4 * n; ++i)
		Tree[i].left.f = Tree[i].left.s = Tree[i].right.f = Tree[i].right.s = Tree[i].M.f = Tree[i].M.s = 0;
}

segment combine(segment a, segment b)
{
	db("Combine");
	segment res;
	if (a.left.f == b.right.f)
	{
		res.left.f = res.right.f = res.M.f = a.left.f;
		res.left.s = res.right.s = res.M.s = a.left.s + b.right.s;
		return res;
	}
	res.left = a.left;
	res.right = b.right;
	if (a.left.f == b.left.f)
		res.left.s += b.left.s;
	if (a.right.f == b.right.f)
		res.right.s += a.right.s;
	if (a.M.s > b.M.s)
		res.M = a.M;
	else
		res.M = b.M;
	if (a.right.f == b.left.f)
	{
		int cnt = a.right.s + b.left.s;
		if (cnt > res.M.s)
		{
			res.M.f = a.right.s;
			res.M.s = cnt;
		}
	}
	return res;
}

void build(int node, int start, int end)
{
	db("build");
	if (start == end)
	{
		Tree[node].left = {a[start], 1};
		Tree[node].right = {a[start], 1};
		Tree[node].M = {a[start], 1};
		return;
	}
	int mid = (start + end) / 2;
	build(2 * node, start, mid);
	build(2 * node + 1, mid + 1, end);
	Tree[node] = combine(Tree[2 * node], Tree[2 * node + 1]);
}

segment query(int node, int start, int end, int left, int right)
{
	db("Query");
	if (start == left && right == end)
		return Tree[node];
	int mid = (start + end) / 2;
	if (right <= mid)
		return query(node * 2, start, mid, left, right);
	if (left > mid)
		return query(1 + node * 2, mid + 1, end, left, right);
	return combine(query(node * 2, start, mid, left, mid), query(1 + node * 2, mid + 1, end, mid + 1, right));
}

void solve(int n, int q)
{
	db(n, q);
	if (n == 0)
		exit(0);
	// n = 1e5;
	// q = 1e5;
	for (int i = 0; i < n; ++i)
	{
		cin >> a[i];
		// a[i] = rand() % n;
	}
	clear(n);
	build(1, 0, n - 1);
	int x, y;
	while (q--)
	{
		cin >> x >> y;
		// x = 1 + abs(rand() % n);
		// y = 1 + abs(rand() % n);
		if (x > y)
			swap(x, y);
		cout << query(1, 0, n - 1, x - 1, y - 1).M.s << '\n';
	}
	db("End");
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
	int n, q;
	while (true)
	{
		cin >> n;
		if (n == 0)
			break;
		cin >> q;
		solve(n, q);
	}
	return 0;
}