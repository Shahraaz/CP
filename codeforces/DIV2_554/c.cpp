//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
#define multitest 1
#define Debug
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

ll gcd(ll a, ll b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

ll lcm(ll a, ll b)
{
	return a * b / gcd(a, b);
}

void solve()
{
	ll a, b;
	// cin >> a >> b;
	a = rand() % 100;
	b = rand() % 100;
	if (a < b)
		swap(a, b);
	// cout << "INPUT " << a << ' ' << b << ' ' << abs(a-b) << '\n';
	// cout << gcd(a,b) << ' ' << gcd(a,abs(a-b)) << ' ' << gcd(b,abs(a-b)) << '\n';
	ll curr = lcm(a, b), K = 0;
	for (int i = 0; i < 1000; ++i)
	{
		ll t = lcm(i + a, i + b);
		if (curr > t)
		{
			curr = t;
			K = i;
			// cout << curr << ' ' << i << '\n';
		}
	}
	ll d = abs(a - b);
	if (d == 0)
	{
		cout << (K == 0) << '\n';
	}
	else
	{
		ll x = ceil(max(a, b) / (1.0 * d));
		// cout << abs(max(a, b) - x * d);
		if (K != abs(max(a, b) - x * d))
		{
			cout << (a >= d && b <= d) << ' ';
			cout << abs(a - b) << ' ' << K << ' ' << abs(max(a, b) - x * d) << ' ' << a << ' ' << b << '\n';
		}
		// cout << (K == abs(max(a, b) - x * d)) << '\n';
	}
}

int32_t main()
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
