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

const int nax = 1 << 19;
using ld = long double;
ld prob[nax];
ld ar[20][20];

void solve()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> ar[i][j];
	prob[(1 << n) - 1] = 1;
	for (int mask = (1 << n) - 1; mask > 0; --mask)
	{
		int cnt = __builtin_popcount(mask);
		ld p = cnt * (cnt - 1) / 2;
		p = 1 / p;
		for (int i = 0; i < n; ++i)
			if (mask & (1 << i))
				for (int j = 0; j < n; ++j)
					if (i != j)
						if (mask & (1 << j))
							prob[mask ^ (1 << j)] += prob[mask] * p * ar[i][j];
	}
	cout << fixed << setprecision(10);
	for (int i = 0; i < n; ++i)
		cout << prob[1 << i] << ' ';
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