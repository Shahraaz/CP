//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
// #define multitest 1
// #define Debug 1
void ControlIO();
void TimerStart();
void TimerStop();
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

typedef complex<ll> point;
bool cmp(point a, point b)
{
	if (real(a) == real(b))
		return imag(a) < imag(b);
	return real(a) < real(b);
}

bool cmpy(point a, point b)
{
	if (imag(a) == imag(b))
		return real(a) < real(b);
	return imag(a) < imag(b);
}

ll DandC(vector<point> &Points, int begin, int end)
{
	if (begin == end)
		return 1e18;
	int m = (begin + end) / 2;
	ll d = min(DandC(Points, begin, m), DandC(Points, m + 1, end));
	vector<point> V;
	point mid = Points[m];
	for (int i = begin; i <= end; ++i)
	{
		auto x = Points[i];
		if (norm(point(real(x - mid), 0)) < d)
			V.pb(x);
	}
	sort(V.begin(),V.end(),cmpy);
	int s = V.size();
	for (int i = 0; i < s; ++i)
		for (int j = i + 1; j < s; ++j)
		{
			db(i, j, V[i], V[j], V[i] - V[j], norm(V[i] - V[j]), d);
			if (norm(V[i] - V[j]) < d)
				d = norm(V[i] - V[j]);
			else break;
		}
	return d;
}

void solve()
{
	int n, x, y;
	cin >> n;
	vector<point> Points(n);
	ll prevsum = 0;
	for (int i = 0; i < n; ++i)
	{
		cin >> x;
		prevsum += x;
		Points[i] = point(i, prevsum);
	}
	sort(Points.begin(), Points.end(), cmp);
	cout << DandC(Points, 0, n - 1);
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