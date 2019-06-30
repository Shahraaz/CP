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

struct Data
{
	int two, three, five;
	Data()
	{
		two = three = five = 0;
	}
	Data operator+(const Data &a) const
	{
		Data b = *this;
		b.two += a.two;
		b.three += a.three;
		b.five += a.five;
		return b;
	}
	int valueOf(int n)
	{
		while (two && n % 2 == 0)
		{
			n /= 2;
			two--;
		}
		while (three && n % 3 == 0)
		{
			n /= 3;
			three--;
		}
		while (five && n % 5 == 0)
		{
			n /= 5;
			five--;
		}
		return n;
	}
};

const int N = 1e5 + 10;
vector<Data> Tree(4 * N), Lazy(4 * N);
vector<bool> isLazy(4 * N);
vector<int> a;

void propagate(int node, int start, int end)
{
	if (isLazy[node])
	{
		Tree[node] = Tree[node] + Lazy[node];
		if (start != end)
		{
			Lazy[2 * node] = Lazy[2 * node] + Lazy[node];
			Lazy[2 * node + 1] = Lazy[2 * node + 1] + Lazy[node];
			isLazy[2 * node] = true;
			isLazy[2 * node + 1] = true;
		}
		Lazy[node] = Data();
		isLazy[node] = false;
	}
}

void update(int node, int start, int end, int qstart, int qend, int p)
{
	propagate(node, start, end);
	if (start > end || qend < start || qstart > end)
		return;
	if (qstart <= start && end <= qend)
	{
		isLazy[node] = true;
		Lazy[node].two = p == 2;
		Lazy[node].three = p == 3;
		Lazy[node].five = p == 5;
		propagate(node, start, end);
		return;
	}
	int mid = (start + end) / 2;
	update(2 * node, start, mid, qstart, qend, p);
	update(2 * node + 1, mid + 1, end, qstart, qend, p);
	Tree[node] = Tree[2 * node] + Tree[2 * node + 1];
}

void clearPos(int node, int start, int end, int pos, int d)
{
	propagate(node, start, end);
	if (start == end)
	{
		Tree[node] = Data();
		a[start] = d;
		return;
	}
	int mid = (start + end) / 2;
	if (pos <= mid)
		clearPos(2 * node, start, mid, pos, d);
	else
		clearPos(2 * node + 1, mid + 1, end, pos, d);
	Tree[node] = Tree[2 * node] + Tree[2 * node + 1];
}

int getpos(int node, int start, int end, int pos)
{
	propagate(node, start, end);
	if (start == end)
		return Tree[node].valueOf(a[start]);
	int mid = (start + end) / 2;
	if (pos <= mid)
		return getpos(2 * node, start, mid, pos);
	else
		return getpos(2 * node + 1, mid + 1, end, pos);
}

void solve()
{
	int n, type, l, r, p, d, m;
	cin >> n;
	a.resize(n);
	for (auto &x : a)
		cin >> x;
	cin >> m;
	while (m--)
	{
		cin >> type;
		switch (type)
		{
		case 1:
			cin >> l >> r >> p;
			update(1, 0, n - 1, l - 1, r - 1, p);
			break;

		default:
			cin >> l >> d;
			clearPos(1, 0, n - 1, l - 1, d);
			break;
		}
	}
	for (int i = 0; i < n; ++i)
		cout << getpos(1, 0, n - 1, i) << ' ';
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