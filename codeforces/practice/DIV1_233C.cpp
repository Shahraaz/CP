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
	int perfect, left, right;
	Data(int p = 0, int l = 0, int r = 0)
	{
		perfect = p;
		left = l;
		right = r;
	}
};

vector<Data> Tree(4e6 + 10);

Data calculate(Data l, Data r)
{
	int t = min(l.left, r.right);
	return Data(l.perfect + r.perfect + t, l.left + r.left - t, l.right + r.right - t);
}

void update(int node, int start, int end, int pos, bool type)
{
	// db(node, start, end, pos);
	if (start == end)
	{
		switch (type)
		{
		case 0:
			Tree[node] = Data(0, 1, 0);
			break;
		case 1:
			Tree[node] = Data(0, 0, 1);
			break;
		default:
			Tree[node] = Data(0, 0, 0);
			break;
		}
		return;
	}
	int mid = (start + end) / 2;
	if (pos <= mid)
		update(2 * node, start, mid, pos, type);
	else
		update(2 * node + 1, mid + 1, end, pos, type);
	Tree[node] = calculate(Tree[node * 2], Tree[node * 2 + 1]);
}

Data query(int node, int start, int end, int qstart, int qend)
{
	if (qstart > end || qend < start)
		return Data();
	if (qstart <= start && end <= qend)
		return Tree[node];
	int mid = (start + end) / 2;
	return calculate(query(2 * node, start, mid, qstart, qend), query(2 * node + 1, mid + 1, end, qstart, qend));
}

void solve()
{
	string s;
	cin >> s;
	int n = s.length();
	for (int i = 0; i < n; ++i)
		update(1, 0, n - 1, i, s[i] == ')');
	int m, l, r;
	cin >> m;
	while (m--)
	{
		cin >> l >> r;
		cout << 2*query(1, 0, n - 1, l - 1, r - 1).perfect << '\n';
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