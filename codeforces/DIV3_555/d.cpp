//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
// #define multitest 1
#define Debug 1
typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
#define mp make_pair
const long long mod = 1000000007;
const long long High = 1e16;
void ControlIO();
void TimerStart();
void TimerStop();
#ifdef Debug
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__)
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

ll po(int base, int idx)
{
	if (idx == 0)
		return 1;
	ll temp = po(base, idx / 2);
	temp = temp * temp;
	if (idx & 1)
		temp *= base;
	return temp;
}

ll fun(int k, int k1)
{
	return (ll)k1 * (k1 - 1) / 2 + k1 * (po(2, k - k1) - 1);
}

void solve()
{
	ll n, k;
	cin >> n >> k;
	int k1 = 64;
	while (k1--)
	{
		ll a = po(2, k - k1) - 1;
		ll num = n - k1 * (k1 - 1) / 2 - k1 * (a);
		ll den = k1 + a;
		db(num, den, k1);
		if (num>0 && num % den == 0)
		{
			cout << "YES\n";
			ll no = num / den;
			for (int i = 0; i < k1; ++i)
			{
				cout << no << ' ';
				no++;
			}
			for (int i = 0; i < (k - k1); ++i)
			{
				cout << no << ' ';
				no = no * 2;
			}
			return;
		}
	}
	cout << "NO";
}

int main()
{
	ControlIO();
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	TimerStart();
	while (t--)
		solve();
	TimerStop();
	return 0;
}

void ControlIO()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#ifndef Online
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
}

auto TimeStart = chrono::steady_clock::now();
auto TimeEnd = chrono::steady_clock::now();

void TimerStart()
{
#ifndef Online
	TimeStart = chrono::steady_clock::now();
#endif
}

void TimerStop()
{
#ifndef Online
	TimeEnd = chrono::steady_clock::now();
	auto ElapsedTime = TimeEnd - TimeStart;
	cout << "\n\nTime elapsed: " << chrono::duration<double>(ElapsedTime).count() << " seconds.\n";
#endif
}
