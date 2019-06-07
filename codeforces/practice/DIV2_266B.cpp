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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void solve()
{
	ll n, a, b;
	cin >> n >> a >> b;
	ll reqa = 6 * n;
	ll minarea = LLONG_MAX, a1 = a, b1 = b;
	bool flag = false;
	if (a > b)
	{
		flag = true;
		swap(a, b);
	} // cout << minarea << '\n';
	for (int i = a; i <= reqa; ++i)
	{
		ll atemp, btemp;
		atemp = i;
		btemp = ceill((ld)reqa / i);
		if (btemp < atemp)
			break;
		if (atemp < a)
			atemp = a;
		if (btemp < b)
			btemp = b;
		if ((atemp * btemp) < minarea)
		{
			minarea = atemp * btemp;
			a1 = atemp;
			b1 = btemp;
		}
	}
	if (flag)
		swap(a1, b1);
	cout << a1 * b1 << '\n';
	cout << a1 << ' ' << b1 << '\n';
	db("Output");
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