//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
// #define multitest 1
// #define Debug 1
typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
#define mp make_pair
const long long mod = 1000000007;
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

vector<ll> LShift, RShift;
ll n, k;
void pre(vector<ll> &a)
{
	LShift.resize(n);
	RShift.resize(n);
	LShift[0] = 0;
	for (int i = 1; i < n; ++i)
		LShift[i] = (a[i]) * 1LL * i + LShift[i - 1];
	RShift[n - 1] = 0;
	for (int i = n - 2; i >= 0; --i)
		RShift[i] = (n - 1LL * i - 1) * (a[i + 1]) + RShift[i + 1];
}

void solve()
{
	cin >> n >> k;
	vector<pair<ll, ll>> V(n);
	ll i = 0;
	for (auto &x : V)
	{
		cin >> x.f;
		x.s = i++;
	}
	sort(V.begin(), V.end());
	vector<ll> A(n);
	A[0] = 0;
	for (int i = 1; i < n; ++i)
		A[i] = V[i].f - V[i - 1].f;
	ll sum;
	ll index = LLONG_MAX;
	pre(A);
	sum = LLONG_MAX;
	for (int i = 0; i < n; ++i)
	{
		ll t = LShift[i] + RShift[i];
		// db(i, t);
		if(t>=k) t = t - k;
		else
		{
            t = k - t;
            t = (t&1);
    	}
		if (t < sum)
		{
			index = V[i].s;
			sum = t;
		}
		else if (t == sum)
			index = min(index, V[i].s);
	}
	cout << index + 1 << ' ' << sum << '\n';
}

// 1 2 3 4 5 6 7
// 1 1 1 1     1

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
