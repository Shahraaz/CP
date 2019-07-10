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

typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
const long long mod = 1000000007;
auto TimeStart = chrono::steady_clock::now();

const int nax = 2e5 + 10;
int n, k;
vector<ll> a(nax);

void solve()
{
	cin >> n >> k;
	map<ll, int> cntL, cntR;
	for (int i = 0; i < n; ++i)
	{
		cin >> a[i];
		cntR[a[i]]++;
	}
	ll ans = 0;
	for (int i = 0; i < n; ++i)
	{
		cntR[a[i]]--;
		if (a[i] % k == 0)
		{
			ans += (ll)cntL[a[i] / k] * cntR[a[i] * k];
			db(cntL[a[i] / k], cntR[a[i] * k]);
		}
		cntL[a[i]]++;
	}
	cout << ans;
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