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

const int nax = 1e3 + 10;
vector<vector<int>> down(nax, vector<int>(nax, 1));
vector<vector<int>> up(nax, vector<int>(nax, 1));
vector<vector<int>> len(nax, vector<int>(nax, 1));
vector<vector<int>> len2(nax, vector<int>(nax, 1));
int n, m;

void solve()
{
	cin >> n >> m;
	vector<string> a(n);
	for (auto &x : a)
		cin >> x;
	for (int j = 0; j < m; ++j)
		for (int i = n - 2; i >= 0; --i)
			if (a[i][j] == a[i + 1][j])
				down[i][j] = 1 + down[i + 1][j]; // #####a###### count number of # Downard
	for (int i = 0; i < n; ++i)
		for (int j = m - 2; j >= 0; --j)
			if (a[i][j] == a[i][j + 1] && down[i][j] == down[i][j + 1]) // Downward is same for adjacent ones
				len[i][j] = 1 + len[i][j + 1];
	for (int j = 0; j < m; ++j)
		for (int i = 1; i < n; ++i)
			if (a[i][j] == a[i - 1][j]) // Downward
				up[i][j] = up[i - 1][j] + 1;
	for (int i = 0; i < n; ++i)
		for (int j = m - 2; j >= 0; --j)
			if (a[i][j] == a[i][j + 1] && up[i][j] == up[i][j + 1])
				len2[i][j] = len2[i][j + 1] + 1;
	ll ans = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{
			int w = len[i][j];
			int h = down[i][j];
			if (i + h + h < n)
				if (down[i + h][j] == h && down[i + h + h][j] >= h)
				{
					w = min(w, len[i + h][j]);
					w = min(w, len2[i + h + h + h - 1][j]);
					db(w, i, j);
					ans += w;
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
	cout << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}