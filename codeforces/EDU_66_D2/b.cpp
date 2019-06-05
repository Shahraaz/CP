//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
// #define multitest 1
#define Debug 1
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
	string str;
	ll n, x;
	cin >> n;
	ll ans = 0;
	stack<ll> Inc, st2;
	Inc.push(0);
	ll limit = (1LL << 32) - 1;
	while (n--)
	{
		cin >> str;
		if (str[0] == 'f')
		{
			cin >> x;
			st2.push(x);
			Inc.push(0);
		}
		else if (str[0] == 'a')
		{
			Inc.top()++;
		}
		else
		{
			x = st2.top();
			st2.pop();
			int y = Inc.top();
			Inc.pop();
			if (y < 0 || x < 0)
			{
				cout << "OVERFLOW!!!";
				return;
			}
			if (y * x < 0)
			{
				cout << "OVERFLOW!!!";
				return;
			}
			if (y * x > limit)
			{
				cout << "OVERFLOW!!!";
				return;
			}
			Inc.top() += y * x;
			if (Inc.top() < 0)
			{
				cout << "OVERFLOW!!!";
				return;
			}
			if (Inc.top() > limit)
			{
				cout << "OVERFLOW!!!";
				return;
			}
		}
		if (Inc.top() > limit)
		{
			cout << "OVERFLOW!!!";
			return;
		}
	}
	if (Inc.top() < 0)
	{
		cout << "OVERFLOW!!!";
		return;
	}
	if (Inc.top() > limit)
	{
		cout << "OVERFLOW!!!";
		return;
	}
	cout << Inc.top();
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#ifndef Online
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	auto TimeStart = chrono::steady_clock::now();
	auto TimeEnd = chrono::steady_clock::now();
#endif
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (t--)
		solve();
#ifndef Online
	TimeEnd = chrono::steady_clock::now();
	auto ElapsedTime = TimeEnd - TimeStart;
	cout << "\n\nTime elapsed: " << chrono::duration<double>(ElapsedTime).count() << " seconds.\n";
#endif
	return 0;
}