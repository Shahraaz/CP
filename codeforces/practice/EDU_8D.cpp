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

ll solve(ll end, ll start)
{
	string str = "";
	string e = to_string(end);
	string s = to_string(start);
	reverse(s.begin(), s.end());
	while (s.length() < e.length())
		s.push_back('0');
	reverse(s.begin(), s.end());
	bool allowed = false;
	for (int i = 0; i < s.length(); ++i)
	{
		if (!allowed)
		{
			if(s[0]=='1')
		}
	}
}

void solve()
{
	ll a, b;
	cin >> a >> b;
	cout << solve(b, a - 1) << '\n';
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