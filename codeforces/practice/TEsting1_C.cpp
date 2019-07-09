//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define multitest 1
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

const int N = 200000 + 10;
vector<ll> Tree(4 * N, 1e18), Lazy(4 * N), a(N);

void build(int node, int start, int end)
{
	if (start == end)
	{
		Tree[node] = a[start];
		return;
	}
	int mid = (start + end) / 2;
	build(2 * node, start, mid);
	build(2 * node + 1, mid + 1, end);
	Tree[node] = min(Tree[2 * node], Tree[2 * node + 1]);
}

void propagate(int node)
{
	if (Lazy[node])
	{
		Tree[node] += Lazy[node];
		Lazy[2 * node] += Lazy[node];
		Lazy[2 * node + 1] += Lazy[node];
		Lazy[node] = 0;
	}
}

void update(int node, int start, int end, int qstart, int qend, int val)
{
	if (start > end || qstart > end || qend < start)
		return;
	if (qstart <= start && end <= qend)
	{
		Lazy[node] += val;
		propagate(node);
		return;
	}
	propagate(node);
	int mid = (start + end) / 2;
	update(2 * node, start, mid, qstart, qend, val);
	update(2 * node + 1, mid + 1, end, qstart, qend, val);
	Tree[node] = min(Tree[2 * node], Tree[2 * node + 1]);
}

ll query(int node, int start, int end, int qstart, int qend)
{
	if (start > end || qstart > end || qend < start)
		return 1e18;
	propagate(node);
	if (qstart <= start && end <= qend)
		return Tree[node];
	int mid = (start + end) / 2;
	return min(query(2 * node, start, mid, qstart, qend), query(2 * node + 1, mid + 1, end, qstart, qend));
}

void solve()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	build(1, 0, n - 1);
	int inp[3], cnt, l, r, k, m;
	cin >> m;
	getchar();
	string s;
	while (m--)
	{
		getline(cin, s);
		stringstream sin(s);
		cnt = 0;
		while (sin >> k)
			inp[cnt++] = k;
		l = inp[0];
		r = inp[1];
		//db(l, r, cnt, inp[2]);
		if (cnt == 3)
		{
			if (l <= r)
				update(1, 0, n - 1, l, r, inp[2]);
			else
			{
				update(1, 0, n - 1, 0, r, inp[2]);
				update(1, 0, n - 1, l, n - 1, inp[2]);
			}
		}
		else
		{
			db("Ou");
			if (l <= r)
				cout << query(1, 0, n - 1, l, r) << '\n';
			else
			{
				cout << min(query(1, 0, n - 1, 0, r),
							query(1, 0, n - 1, l, n - 1))
					 << '\n';
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