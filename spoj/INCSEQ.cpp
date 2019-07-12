//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define multitest 1
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

using ll = long long;
#define f first
#define s second
#define pb push_back
const long long mod = 1000000007;
auto TimeStart = chrono::steady_clock::now();

const int nax = 1e5 + 10;
vector<int> S(1e4 + 10);
int n, k;
int Tree[52][4 * nax];

int add(int a, int b)
{
	a += b;
	if (a >= 5000000)
		a -= 5000000;
	return a;
}

int query(int idx, int node, int start, int end, int qstart, int qend)
{
	if (start > end || qstart > end || qend < start)
		return 0;
	if (qstart <= start && end <= qend)
		return Tree[idx][node];
	int mid = (start + end) / 2;
	return add(query(idx, 2 * node, start, mid, qstart, qend), query(idx, 2 * node + 1, mid + 1, end, qstart, qend));
}

void update(int idx, int node, int start, int end, int pos, int nVal)
{
	if (start > end)
		return;
	if (start == end)
	{
		Tree[idx][node] = add(Tree[idx][node], nVal);
		return;
	}
	int mid = (start + end) / 2;
	if (pos <= mid)
		update(idx, 2 * node, start, mid, pos, nVal);
	else
		update(idx, 2 * node + 1, mid + 1, end, pos, nVal);
	Tree[idx][node] = add(Tree[idx][2 * node], Tree[idx][2 * node + 1]);
}

void solve()
{
	cin >> n >> k;
	int ans = 0;
	for (int i = 0; i < n; ++i)
	{
		cin >> S[i];
		S[i]++;
		for (int j = 1; j <= k; ++j)
		{
			int p = j == 1 ? 1 : query(j - 1, 1, 0, 1e5, 0, S[i] - 1);
			update(j, 1, 0, 1e5, S[i], p);
			if (j == k)
				ans = add(ans, p);
		}
	}
	cout << ans << '\n';
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (t--)
		solve();
#ifdef TIME
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}