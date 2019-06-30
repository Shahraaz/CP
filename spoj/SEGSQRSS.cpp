//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
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

const int N = 1e5 + 10;
vector<ll> sum(4 * N), sumSq(4 * N), Lazy(4 * N), a;
vector<bool> isLazy(4 * N), ReSet(4 * N);

void build(int node, int start, int end)
{
	if (start == end)
	{
		sum[node] = a[start];
		sumSq[node] = a[start] * a[start];
		return;
	}
	int mid = (start + end) / 2;
	build(2 * node, start, mid);
	build(2 * node + 1, mid + 1, end);
	sum[node] = sum[2 * node] + sum[2 * node + 1];
	sumSq[node] = sumSq[2 * node] + sumSq[2 * node + 1];
}

void propagate(int node, int start, int end)
{
	if (isLazy[node])
	{
		if (!ReSet[node])
		{
			sumSq[node] += 2 * sum[node] * Lazy[node] + (end - start + 1) * Lazy[node] * Lazy[node];
			sum[node] += (end - start + 1) * Lazy[node];
			if (start != end)
			{
				ReSet[2 * node] = ReSet[2 * node + 1] = false;
				isLazy[2 * node + 1] = isLazy[2 * node] = true;
				Lazy[2 * node + 1] = Lazy[2 * node] = Lazy[node];
			}
		}
		else
		{
			sumSq[node] = (end - start + 1) * Lazy[node] * Lazy[node];
			sum[node] = (end - start + 1) * Lazy[node];
			if (start != end)
			{
				ReSet[2 * node] = ReSet[2 * node + 1] = true;
				isLazy[2 * node + 1] = isLazy[2 * node] = true;
				Lazy[2 * node + 1] = Lazy[2 * node] = Lazy[node];
			}
		}
		ReSet[node] = 0;
		Lazy[node] = 0;
		isLazy[node] = false;
	}
}

void Set(int node, int start, int end, int qstart, int qend, int v)
{
	propagate(node, start, end);
	if (start > end || qend < start || qstart > end)
		return;
	if (qstart <= start && end <= qend)
	{
		ReSet[node] = true;
		Lazy[node] = v;
		isLazy[node] = true;
		propagate(node, start, end);
		return;
	}
	int mid = (start + end) / 2;
	Set(2 * node, start, mid, qstart, qend, v);
	Set(2 * node + 1, mid + 1, end, qstart, qend, v);
	sum[node] = sum[2 * node] + sum[2 * node + 1];
	sumSq[node] = sumSq[2 * node] + sumSq[2 * node + 1];
}

void add(int node, int start, int end, int qstart, int qend, int v)
{
	propagate(node, start, end);
	if (start > end || qend < start || qstart > end)
		return;
	if (qstart <= start && end <= qend)
	{
		Lazy[node] = v;
		isLazy[node] = true;
		propagate(node, start, end);
		return;
	}
	int mid = (start + end) / 2;
	add(2 * node, start, mid, qstart, qend, v);
	add(2 * node + 1, mid + 1, end, qstart, qend, v);
	sum[node] = sum[2 * node] + sum[2 * node + 1];
	sumSq[node] = sumSq[2 * node] + sumSq[2 * node + 1];
}

ll query(int node, int start, int end, int qstart, int qend)
{
	propagate(node, start, end);
	if (start > end || qend < start || qstart > end)
		return 0;
	if (qstart <= start && end <= qend)
		return sumSq[node];
	int mid = (start + end) / 2;
	return query(2 * node, start, mid, qstart, qend) +
		   query(2 * node + 1, mid + 1, end, qstart, qend);
}

int cnt = 1;
void solve()
{
	int n, q, type, st, nd, x;
	cin >> n >> q;
	a.resize(n);
	fill(isLazy.begin(), isLazy.end(), false);
	fill(ReSet.begin(), ReSet.end(), false);
	fill(Lazy.begin(), Lazy.end(), 0);
	for (auto &x : a)
		cin >>
			x;
	build(1, 0, n - 1);
	cout << "Case " << cnt << ":\n";
	while (q--)
	{
		cin >> type >> st >> nd;
		switch (type)
		{
		case 0:
			cin >> x;
			Set(1, 0, n - 1, st - 1, nd - 1, x);
			break;
		case 1:
			cin >> x;
			add(1, 0, n - 1, st - 1, nd - 1, x);
			break;
		case 2:
			cout << query(1, 0, n - 1, st - 1, nd - 1) << '\n';
			break;
		default:
			break;
		}
	}
	cnt++;
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