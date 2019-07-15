//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
#define multitest 1
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

int a, b, l, r;

ld f(ld x)
{
	// return x;
	ld temp = x / ld(a);
	// return temp;
	return b * sqrtl(1 - temp * temp);
}
ld eps = 1e-10;

ld simpson(ld fl, ld fr, ld fmid, ld l, ld r)
{
	return (fl + fr + 4 * fmid) * (r - l) / 6;
}

ld rsimpson(ld slr, ld fl, ld fr, ld fmid, ld l, ld r)
{
	ld mid = (l + r) / 2;
	ld fml = f((l + mid) / 2);
	ld fmr = f((r + mid) / 2);
	ld slm = simpson(fl, fmid, fml, l, mid);
	ld smr = simpson(fmid, fr, fmr, mid, r);
	db(l, r, mid, slr, slm, smr);
	if (fabs(slr - slm - smr) < eps)
		return slm + smr;
	return rsimpson(slm, fl, fmid, fml, l, mid) + rsimpson(smr, fmid, fr, fmr, mid, r);
}

ld Integral(ld start, ld end)
{
	ld mid = (start + end) / 2;
	ld fl = f(start);
	ld fr = f(end);
	ld fmid = f(mid);
	return rsimpson(simpson(fl, fr, fmid, start, end), fl, fr, fmid, start, end);
}

ld Area(int l, int r)
{
	return 2 * Integral(l, r);
}

void solve()
{
	cin >> a >> b >> l >> r;
	cout << fixed << setprecision(50) << Area(l, r) << '\n';
	cout << acosl(-1) << '\n';
	db("answer");
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