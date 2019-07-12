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

const int nax = 2e5 + 10;

void solve()
{
	int x;
	cin >> x;
	x %= 4;
	map<int, char> Rank;
	Rank[1] = 'A';
	Rank[2] = 'C';
	Rank[3] = 'B';
	Rank[0] = 'D';
	char minRank = 100;
	int cnt = 0;
	for (int i = 0; i < 3; ++i)
	{
		char temp = Rank[x];
		db(Rank[x], minRank, temp < minRank);
		if (temp < minRank)
		{
			cnt = i;
			minRank = temp;
		}
		x++;
		x %= 4;
	}
	cout << cnt << ' ' << minRank << '\n';
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