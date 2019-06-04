//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define int ll;
#define Online 1
// #define multitest 1
// #define Debug
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

vector<ll> Sum;
vector<ll> A;
ll n, k;
int _n;
void Pre(vector<ll> &a)
{
	int _n = a.size();
	Sum.resize(_n);
	Sum[0] = a[0];
	for (int i = 1; i < _n; ++i)
		Sum[i] = Sum[i - 1] + a[i];
}

ll sum(int start, int end)
{
	db(start,end);
	if (start > 0)
		return Sum[end] - Sum[start - 1];
	return Sum[end];
}

bool fun(int start, int end)
{
	if (end >= _n)
		return false;
	ll s = sum(start, end);
	// db(start, end, s, s + k, (ll)(end - start + 1) * A[end]);
	return (s + k) >= ((ll)(end - start + 1) * A[end]);
}
void solve()
{
	cin >> n >> k;
	A.resize(n);
	for (ll &x : A)
	{
		cin >> x;
		x += mod;
	}
	sort(A.begin(), A.end());
	Pre(A);
	int maxcnt = 1, value = A[0] - mod;
	for (int i = 0; i < n; ++i)
	{
		if (((i + maxcnt) < n) && fun(i, i + maxcnt))
		{
			while (((i + maxcnt) < n) && fun(i, i + maxcnt))
			{
				value = A[i + maxcnt] - mod;
				maxcnt++;
			}
		}
	}
	cout << maxcnt << ' ' << value << '\n';
}

signed main()
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
