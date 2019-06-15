//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define multitest 1
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
	ll n, m, k, l, r, d;
	cin >> n >> m >> k;
	vector<ll> A(n);
	for (auto &x : A)
		cin >> x;
	vector<pair<pair<ll, ll>, ll>> Q(m);
	for (int i = 0; i < m; ++i)
		cin >> Q[i].f.f >> Q[i].f.s >> Q[i].s;
	vector<ll> Inc(m + 1);
	while (k--)
	{
		cin >> l >> r;
		Inc[l - 1]++;
		Inc[r]--;
	}
	d = 0;
	vector<ll> IncArr(n + 1);
	for (int i = 0; i < m; ++i)
	{
		d += Inc[i];
		Q[i].s *= d;
		IncArr[Q[i].f.f - 1] += Q[i].s;
		IncArr[Q[i].f.s] -= Q[i].s;
	}
	d = 0;
	for (int i = 0; i < n; ++i)
	{
		d += IncArr[i];
		cout << d + A[i] << ' ';
	}
	cout << '\n';
	db("ou");
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
	return 0;
}