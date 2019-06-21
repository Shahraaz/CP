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
	int n;
	cin >> n;
	vector<int> Mat(n);
	for (auto &x : Mat)
		cin >> x;
	sort(Mat.rbegin(), Mat.rend());
	ll sum = 0;
	vector<ll> Sum(n+1);
	for(int i=1;i<=n;++i)
		Sum[i] = Sum[i-1] + Mat[i-1];
	for(int  m =1;m<=n;m*=4)
		sum += Sum[m];
	cout << sum;
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