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
const long long mod = 10007;

struct Data
{
	ll a, b, c;
	Data(ll a = 0, ll b = 0, ll c = 0) : a(a), b(b), c(c) {}
	Data operator+(const Data &a) const
	{
		Data temp = *this;
		temp.a += a.a;
		temp.b += a.b;
		temp.c += a.c;
		temp.a %= mod;
		temp.b %= mod;
		temp.c %= mod;
		return temp;
	}
};

ll x2(ll n)
{
	return n * (n + 1) * (2 * n + 1) / 6;
}

ll x2(int start, int end)
{
	return x2(end) - x2(start - 1);
}

ll x(ll n)
{
	return n * (n + 1) / 2;
}

ll x(int start, int end)
{
	return x(end) - x(start - 1);
}

const int N = 1e5 + 10;
vector<ll> Tree(4 * N);
vector<bool> isLazy(4 * N);
vector<Data> Lazy(4 * N);

void propagate(int node, int start, int end)
{
	if (isLazy[node])
	{
		ll temp = Lazy[node].a * x2(start, end) % mod;
		temp += Lazy[node].b * x(start, end);
		temp %= mod;
		temp += Lazy[node].c * (end - start + 1);
		temp %= mod;
		Tree[node] += temp;
		Tree[node] %= mod;
		if (start != end)
		{
			Lazy[2 * node] = Lazy[2 * node] + Lazy[node];
			Lazy[2 * node + 1] = Lazy[2 * node + 1] + Lazy[node];
			isLazy[2 * node] = true;
			isLazy[2 * node + 1] = true;
		}
		isLazy[node] = false;
		Lazy[node] = Data();
	}
}

void update(int node, int start, int end, int qstart, int qend, int a, int b, int c)
{
	propagate(node, start, end);
	if (start > end || qend < start || qstart > end)
		return;
	if (qstart <= start && end <= qend)
	{
		isLazy[node] = true;
		Lazy[node] = Data(a, b, c);
		propagate(node, start, end);
		return;
	}
	int mid = (start + end) / 2;
	update(2 * node, start, mid, qstart, qend, a, b, c);
	update(2 * node + 1, mid + 1, end, qstart, qend, a, b, c);
	Tree[node] = Tree[2 * node] + Tree[2 * node + 1];
}

ll query(int node, int start, int end, int qstart, int qend)
{
	propagate(node, start, end);
	if (start > end || qend < start || qstart > end)
		return 0;
	if (qstart <= start && end <= qend)
		return Tree[node];
	int mid = (start + end) / 2;
	return (query(2 * node, start, mid, qstart, qend) +
			query(2 * node + 1, mid + 1, end, qstart, qend)) %
		   mod;
}

void solve()
{
	int n, m, type, x0, x1, a, b, c;
	cin >> n >> m;
	while (m--)
	{
		cin >> type >> x0 >> x1;
		if (type)
			cout << query(1, 0, n - 1, x0, x1) << '\n';
		else
		{
			cin >> a >> b >> c;
			update(1, 0, n - 1, x0, x1, a, b, c);
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