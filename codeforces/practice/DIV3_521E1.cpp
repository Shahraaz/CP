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
int Left[nax][nax], Right[nax][nax], up[nax][nax], down[nax][nax];
struct element
{
	int x, y, z;
	element(int x, int y, int z) : x(x), y(y), z(z) {}
};

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<string> Grid(n + 1);
	for (int i = 1; i <= n; ++i)
	{
		cin >> Grid[i];
		Grid[i] = '$' + Grid[i];
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (Grid[i][j] == '*')
				Left[i][j] = Left[i][j - 1] + 1;
			else
				Left[i][j] = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = m; j > 0; --j)
			if (Grid[i][j] == '*')
				Right[i][j] = Right[i][j + 1] + 1;
			else
				Right[i][j] = 0;
	for (int j = 1; j <= m; ++j)
		for (int i = 1; i <= n; ++i)
			if (Grid[i][j] == '*')
				up[i][j] = up[i - 1][j] + 1;
			else
				up[i][j] = 0;
	for (int j = m; j > 0; --j)
		for (int i = n; i >= 1; --i)
		{
			if (Grid[i][j] == '*')
				down[i][j] = down[i + 1][j] + 1;
			else
				down[i][j] = 0;
			db(j, i, down[i][j]);
		}
	auto Spare = Grid;
	vector<element> Ans;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
		{
			if (Grid[i][j] == '.')
				continue;
			int go = min(Left[i][j], Right[i][j]);
			go = min(up[i][j], go);
			go = min(down[i][j], go);
			db(i, j, Left[i][j], Right[i][j], up[i][j], down[i][j]);
			if (go > 1)
			{
				Ans.pb(element(i, j, go - 1));
				db(i, j, go - 1, i - go, i + go, j - go, j + go);
				for (int i1 = i - go + 1; i1 < i + go; ++i1)
					Spare[i1][j] = '.';
				for (int i1 = j - go + 1; i1 < j + go; ++i1)
					Spare[i][i1] = '.';
			}
		}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			if (Spare[i][j] == '*')
			{
				cout << "-1";
				return;
			}
	cout << Ans.size() << '\n';
	for (auto x : Ans)
		cout << x.x << ' ' << x.y << ' ' << x.z << '\n';
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