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

vector<ll> T, G, H;

int cnt = 1;
void solve()
{
	int n;
	cin >> n;
	cout << cnt++ << ' ';
	cout << T[n] << '\n';
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
	T.resize(1004);
	G.resize(1004);
	H.resize(1004);
	T[1] = 1;
	T[2] = 5;
	T[3] = 11;
	G[1] = 1;
	G[2] = 1;
	G[3] = 6;
	H[1] = 1;
	H[2] = 2;
	H[3] = 7;
	for (int i = 4; i < 1004; ++i)
	{
		T[i] = T[i - 1] + T[i - 2] + G[i - 1] + 2 * H[i - 1];
		G[i] = T[i - 1] + G[i - 2];
		H[i] = T[i - 1] + H[i - 1];
	}
	while (t--)
		solve();
	return 0;
}