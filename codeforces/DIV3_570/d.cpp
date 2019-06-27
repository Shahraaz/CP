//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
// #define Debug 1
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

void solve()
{
	ll n, x;
	cin >> n;
	map<int, int> C;
	for (int i = 0; i < n; ++i)
	{
		cin >> x;
		C[x]++;
	}
	vector<ll> V;
	for (auto it = C.begin(); it != C.end(); ++it)
		V.pb(it->s);
	sort(V.rbegin(), V.rend());
	ll ans = 0;
	ll cnt = V[0];
	ll curcnt = cnt - 1;
	for (int i = 1; i < V.size(); ++i)
	{
		if (curcnt == 0)
			break;
		curcnt = min(curcnt, V[i]);
		cnt += curcnt;
		curcnt--;
	}
	cout << cnt << '\n';
}

int main()
{
#ifndef Debug
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#endif
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (t--)
		solve();
	return 0;
}