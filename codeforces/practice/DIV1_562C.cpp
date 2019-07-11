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

const int nax = 3e5 + 10;
int nxt[nax][20], big_nxt[20];

void solve()
{
	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	for (int bit = 0; bit < 20; ++bit)
		big_nxt[bit] = n;
	for (int i = n - 1; i >= 0; --i)
	{
		for (int bit = 0; bit < 20; ++bit)
			nxt[i][bit] = n;
		for (int bit = 0; bit < 20; ++bit)
			if (a[i] & (1 << bit))
			{
				int who = big_nxt[bit];
				big_nxt[bit] = i;
				if (who == n)
					continue;
				nxt[i][bit] = who;
				for (int bit2 = 0; bit2 < 20; ++bit2)
					nxt[i][bit2] = min(nxt[i][bit2], nxt[who][bit2]);
			}
#ifdef Debug
		cout << i << '\n';
		for (int bit = 0; bit < 2; ++bit)
			cout << bit << ' ' << big_nxt[bit] << ' ' << nxt[i][bit] << '\n';
#endif
	}
	while (q--)
	{
		int x, y;
		cin >> x >> y;
		--x;
		--y;
		bool ok = false;
		for (int bit = 0; bit < 20; ++bit)
			if (a[y] & (1 << bit))
				if (nxt[x][bit] <= y)
				{
					ok = true;
					break;
				}
		if (ok)
			cout << "Shi\n";
		else
			cout << "Fou\n";
	}
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