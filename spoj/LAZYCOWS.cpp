//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
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

const int nax = 1e4 + 10;
vector<pair<int, int>> Vect;
int n;
int dp[nax][4][nax];

int solve(int i, int mask, int k)
{
	if (i == n)
		return 0;
	if (k < 0)
		return mod;
	int &ret = dp[i][mask][k];
	if (ret >= 0)
		return ret;
	ret = 0;
	if (mask == 0) // No barn Existed before Here, But we have to create something to cover the cows
	{
		if (Vect[i] == 3) // Two Cows one up one Down
		{
			if (k == 1) // Only one Barn Can be made
			{
				
			}
		}
	}
}

void solve()
{
	int x, y;
	map<int, int> M;
	for (int i = 0; i < n; ++i)
	{
		cin >> x >> y;
		M[y] |= (1 << (x - 1));
	}
	n = M.size();
	Vect.resize(n);
	for (auto it = M.begin(); it != M.end(); ++it)
		Vect[it - M.begin()] = make_pair(it->f, it->s);
	memset(dp, -1, sizeof(dp));
	cout << solve(0, 0) << '\n';
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