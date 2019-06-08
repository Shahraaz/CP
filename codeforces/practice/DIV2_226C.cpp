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
	int n, x;
	cin >> n;
	ll mx = 1e7 + 10;
	vector<int> cnt(mx), f(mx), isNotPrime(mx), forQuery(mx);
	for (int i = 0; i < n; ++i)
	{
		cin >> x;
		cnt[x]++;
	}
	isNotPrime[1] = true;
	for (int i = 2; i * i < mx; ++i)
		if (!isNotPrime[i])
			for (int j = i * i; j < mx; j += i)
				isNotPrime[j] = true;
	for (int i = 2; i < mx; ++i)
		if (!isNotPrime[i])
			for (int j = i; j < mx; j += i)
				f[i] += cnt[j];
	for (int i = 1; i < mx; ++i)
		forQuery[i] = forQuery[i - 1] + f[i];
	int m,l,r;
	cin >> m;
	while (m--)
	{
		cin >> l >> r;
		if(l>=mx)
			cout << 0 << '\n';
		else
			cout << forQuery[min((ll)r,mx-1)] - forQuery[l-1] << '\n';		
	}
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