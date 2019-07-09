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

const int N = 1000000 + 10;
struct Data
{
	int n4, n7, n47, n74;
	Data(int a = 0, int b = 0, int c = 0, int d = 0) : n4(a), n7(b), n47(c), n74(d) {}
};

vector<Data> Tree(4 * N);
vector<bool> Lazy(4 * N);
string s;

void build(int node, int start, int end)
{
	if (start == end)
	{
		Tree[node] = Data(s[start] == '4', s[start] == '7', 1, 1);
		return;
	}
	int mid = (start + end) / 2;
	build(2 * node, start, mid);
	build(2 * node + 1, mid + 1, end);
	auto &l = Tree[node * 2];
	auto &r = Tree[node * 2 + 1];
	Tree[node].n4 = l.n4 + r.n4;
	Tree[node].n7 = l.n7 + r.n7;
	Tree[node].n47 = max(l.n4 + r.n7, l.n47 + r.n7);
	Tree[node].n47 = max(Tree[node].n47, l.n4 + r.n47);
	Tree[node].n74 = max(l.n7 + r.n4, l.n74 + r.n4);
	Tree[node].n74 = max(Tree[node].n74, l.n7 + r.n74);
}

void propagate(int node)
{
	if (Lazy[node])
	{
		swap(Tree[node].n4, Tree[node].n7);
		swap(Tree[node].n47, Tree[node].n74);
		Lazy[2 * node] = !Lazy[2 * node];
		Lazy[2 * node + 1] = !Lazy[2 * node + 1];
		Lazy[node] = 0;
	}
}

void update(int node, int start, int end, int qstart, int qend)
{
	if (start > end || qstart > end || qend < start)
		return;
	if (qstart <= start && end <= qend)
	{
		Lazy[node] = !Lazy[node];
		propagate(node);
		return;
	}
	propagate(node);
	int mid = (start + end) / 2;
	update(2 * node, start, mid, qstart, qend);
	update(2 * node + 1, mid + 1, end, qstart, qend);
	auto &l = Tree[node * 2];
	auto &r = Tree[node * 2 + 1];
	Tree[node].n4 = l.n4 + r.n4;
	Tree[node].n7 = l.n7 + r.n7;
	Tree[node].n47 = max(l.n4 + r.n7, l.n47 + r.n7);
	Tree[node].n47 = max(Tree[node].n47, l.n4 + r.n47);
	Tree[node].n74 = max(l.n7 + r.n4, l.n74 + r.n4);
	Tree[node].n74 = max(Tree[node].n74, l.n7 + r.n74);
}

Data query(int node, int start, int end, int qstart, int qend)
{
	if (start > end || qstart > end || qend < start)
		return Data();
	propagate(node);
	if (qstart <= start && end <= qend)
		return Tree[node];
	int mid = (start + end) / 2;
	auto l = query(2 * node, start, mid, qstart, qend);
	auto r = query(2 * node + 1, mid + 1, end, qstart, qend);
	Data ret;
	ret.n4 = l.n4 + r.n4;
	ret.n7 = l.n7 + r.n7;
	ret.n47 = max(l.n4 + r.n7, l.n47 + r.n7);
	ret.n47 = max(ret.n47, l.n4 + r.n47);
	ret.n74 = max(l.n7 + r.n4, l.n74 + r.n4);
	ret.n74 = max(ret.n74, l.n7 + r.n74);
	return ret;
}

void solve()
{
	int n, m, l, r;
	cin >> n >> m;
	cin >> s;
	build(1, 0, n - 1);
	string q;
	while (m--)
	{
		cin >> q;
		if (q[0] == 'c')
			cout << query(1, 0, n - 1, 0, n - 1).n47 << '\n';
		else
		{
			cin >> l >> r;
			update(1, 0, n - 1, l - 1, r - 1);
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