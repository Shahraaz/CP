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

const int N = 1e5 + 10;
vector<int> max1(4 * N), max2(4 * N), a(N);
vector<bool> islazy(4 * N);

void build(int node, int start, int end)
{
	if (start == end)
	{
		max1[node] = a[start];
		return;
	}
	int mid = (start + end) / 2;
	build(2 * node, start, mid);
	build(2 * node + 1, mid + 1, end);
	vector<int> temp(4);
	temp[0] = max1[2 * node];
	temp[1] = max2[2 * node];
	temp[2] = max1[2 * node + 1];
	temp[3] = max2[2 * node + 1];
	sort(temp.begin(), temp.end());
	max1[node] = temp[3];
	max2[node] = temp[2];
}

void update(int node, int start, int end, int pos, int val)
{
	if (start == end)
	{
		max1[node] = val;
		max2[node] = 0;
		return;
	}
	int mid = (start + end) / 2;
	if (pos <= mid)
		update(2 * node, start, mid, pos, val);
	else
		update(2 * node + 1, mid + 1, end, pos, val);
	vector<int> temp(4);
	temp[0] = max1[2 * node];
	temp[1] = max2[2 * node];
	temp[2] = max1[2 * node + 1];
	temp[3] = max2[2 * node + 1];
	sort(temp.begin(), temp.end());
	max1[node] = temp[3];
	max2[node] = temp[2];
}

pair<int, int> query(int node, int start, int end, int qstart, int qend)
{
	if (start > end || qend < start || qstart > end)
		return make_pair(0, 0);
	if (qstart <= start && end <= qend)
		return make_pair(max1[node], max2[node]);
	int mid = (start + end) / 2;
	auto one = query(2 * node, start, mid, qstart, qend);
	auto two = query(2 * node + 1, mid + 1, end, qstart, qend);
	vector<int> temp(4);
	temp[0] = one.f;
	temp[1] = one.s;
	temp[2] = two.f;
	temp[3] = two.s;
	sort(temp.begin(), temp.end());
	return make_pair(temp[3], temp[2]);
}

void solve()
{
	int n, m, i, x, y;
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	build(1, 0, n - 1);
	cin >> m;
	char type;
	while (m--)
	{
		cin >> type;
		switch (type)
		{
		case 'U':
			cin >> i >> x;
			update(1, 0, n - 1, i - 1, x);
			break;

		default:
			cin >> x >> y;
			auto q = query(1, 0, n - 1, x - 1, y - 1);
			cout << q.f + q.s << '\n';
			break;
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