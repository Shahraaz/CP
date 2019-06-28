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

vector<int> s;
vector<int> Tree(4e5 + 10);

int gcd(int a, int b)
{
	while (a > 0 && b > 0)
	{
		if (a > b)
			a %= b;
		else
			b %= a;
	}
	return a + b;
}

void update(int node, int start, int end, int pos, int val)
{
	if (start == end)
	{
		Tree[node] = val;
		return;
	}
	int mid = (start + end) / 2;
	if (pos <= mid)
		update(node + node, start, mid, pos, val);
	else
		update(node + node + 1, mid + 1, end, pos, val);
	Tree[node] = gcd(Tree[node * 2], Tree[node * 2 + 1]);
}

int query(int node, int start, int end, int qstart, int qend)
{
	if (qend < start || qstart > end)
		return 0;
	if (qstart <= start && end <= qend)
		return Tree[node];
	int mid = (start + end) / 2;
	return gcd(query(2 * node, start, mid, qstart, qend), query(2 * node + 1, mid + 1, end, qstart, qend));
}

void solve()
{
	int n;
	cin >> n;
	s.resize(n);
	vector<pair<int, int>> SS(n);
	int i = 0;
	for (auto &x : s)
	{
		cin >> x;
		SS[i] = {x, i};
		update(1, 0, n - 1, i, x);
		i++;
	}
	sort(SS.begin(), SS.end());
	int m, l, r;
	cin >> m;
	while (m--)
	{
		cin >> l >> r;
		int q = query(1, 0, n - 1, l - 1, r - 1);
		db(q);
		int cnt = upper_bound(SS.begin(), SS.end(), make_pair(q, r - 1)) - lower_bound(SS.begin(), SS.end(), make_pair(q, l - 1));
		cout << r - l + 1 - cnt << '\n';
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