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
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= (n / 2); ++i)
		for (int j = 1; j <= m; ++ j)
		{
			cout << i << ' ' << j << '\n';
			cout << n - i + 1 << ' ' << m - j + 1 << '\n';
		}
	if (n & 1)
	{
		int x = n / 2 + 1;
		deque<int> Dq;
		for (int i = 1; i <= m; ++i)
			Dq.pb(i);
		while (Dq.size())
		{
			cout << x << ' ' << Dq.front() << '\n';
			Dq.pop_front();
			if (Dq.size())
			{
				cout << x << ' ' << Dq.back() << '\n';
				Dq.pop_back();
			}
		}
	}
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