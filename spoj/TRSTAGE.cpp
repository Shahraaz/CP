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

const int nax = 10;
int n, m, p, a, b;
using ld = long double;
vector<vector<pair<int, ld>>> Adj;
vector<int> Ticket;
ld dp[1 << nax][nax];
pair<pair<int, int>, pair<int, int>> pad[1 << nax][nax];

ld solve(int curr, int mask)
{
	db(curr, mask);
	if (curr == b)
		return 0;
	int cnt = __builtin_popcount(mask);
	if (cnt == n)
	{
		if (curr == b)
			return 0;
		return 1e18;
	}
	ld &ret = dp[mask][curr];
	if (ret >= 0)
		return ret;
	ret = 1e18;
	for (int i = 0; i < n; ++i)
	{
		if (mask & (1 << i))
			continue;
		int nMask = mask | (1 << i);
		for (auto child : Adj[curr])
		{
			ld temp = (child.s) / (1.0 * Ticket[i]) + solve(child.f, nMask);
			if (temp < ret)
			{
				pad[mask][curr] = make_pair(make_pair(child.f, Ticket[i]), make_pair(nMask, child.s));
			}
			ret = min(ret, temp);
		}
	}
	return ret;
}

void print(int curr, int mask)
{
	if (curr == b)
	{
		cout << "reached " << curr << '\n';
		return;
	}
	int nMask = pad[mask][curr].s.f;
	cout << curr << " Src\n";
	cout << pad[mask][curr].f.s << " Ticket\n";
	cout << pad[mask][curr].s.s << " Way\n";
	cout << pad[mask][curr].s.s / (ld)pad[mask][curr].f.s << " Add\n";
	print(pad[mask][curr].f.f, nMask);
}

bool solve()
{
	cin >> n >> m >> p >> a >> b;
	if (n == 0 && m == 0 && p == 0 && a == 0 & b == 0)
		return false;
	Adj.clear();
	Adj.resize(m + 1);
	Ticket.resize(n);
	for (int i = 0; i < n; ++i)
		cin >> Ticket[i];
	int x, y;
	ld z;
	for (int i = 0; i < p; ++i)
	{
		cin >> x >> y >> z;
		Adj[x].pb({y, z});
		Adj[y].pb({x, z});
	}
	queue<pair<int, int>> Q;
	memset(dp, -1, sizeof(dp));
	ld a1 = solve(a, 0);
	if (a1 > 1e16)
		cout << "Impossible\n";
	else
		cout << fixed << setprecision(6) << a1 << '\n';
#ifdef Path
	// cout << a << ' ';
	print(a, 0);
#endif
	return true;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (solve())
		;
#ifdef TIME
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}