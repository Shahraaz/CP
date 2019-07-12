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
	ll n, m, k;
	cin >> n >> m >> k;
	vector<ll> p(m);
	for (int i = 0; i < m; ++i)
		cin >> p[i];
	ll cnt = 0, delcnt = 0;
	for (int i = 0; i < m;)
	{
		ll j, addi = (p[i] - delcnt - 1) / k;
		for (j = i + 1; j < m; ++j)
		{
			ll addj = (p[j] - delcnt - 1) / k;
			if (addj != addi)
			{
				break;
			}
		}
		db(i, j, addi, p[i]);
		delcnt += j - i;
		i = j;
		cnt++;
	}
	cout << cnt;
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