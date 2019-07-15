//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
// #define multitest 1
#define Debug 1
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

typedef complex<int> point;
typedef vector<point> Polygon;

bool cmp(point a, point b)
{
	if (real(a) == real(b))
		return imag(a) < imag(b);
	return real(a) < real(b);
}

ll cross(point o, point a, point b)
{
	a = a - o;
	b = b - o;
	return (ll)real(a) * imag(b) - (ll)imag(a) * real(b);
}

void PrintPolygon(Polygon P)
{
	return;
	cout << "Polygon Details: ";
	for (auto x : P)
		cout << x << ' ';
	cout << '\n';
}

void PrintPolygon(Polygon P, int n,string msg="")
{
	return;
	P.resize(n);
	cout << "Polygon Details: " << msg << ' ';
	for (auto x : P)
		cout << x << ' ';
	cout << '\n';
}

Polygon convexHull(Polygon Input)
{
	int k = 0, n = Input.size();
	if (n <= 1)
		return Input;
	Polygon H(2 * n);
	sort(Input.begin(), Input.end(), cmp);
	for (int i = 0; i < n; ++i)
	{
		while (k >= 2 && cross(H[k - 2], H[k - 1], Input[i]) < 0)
			k--;
		H[k++] = Input[i];
		// PrintPolygon(H, k,"down");
	}
	int t = k + 1;
	for (int i = n - 1; i > 0; --i)
	{
		while (k >= t && cross(H[k - 2], H[k - 1], Input[i-1]) < 0)
			k--;
		H[k++] = Input[i - 1];
		// PrintPolygon(H, k,"up");
	}
	H.resize(k - 1);
	return H;
}

void solve()
{
	int n, m, x, y;
	cin >> n;
	Polygon Convex, Arbitary;
	for (int i = 0; i < n; ++i)
	{
		cin >> x >> y;
		Convex.pb(point(x, y));
	}
	Arbitary = Convex;
	cin >> m;
	for (int i = 0; i < m; ++i)
	{
		cin >> x >> y;
		Arbitary.pb(point(x, y));
	}
	Convex = convexHull(Convex);
	Polygon HullAfterAddingArbitaryPoints = convexHull(Arbitary);
	PrintPolygon(Convex);
	PrintPolygon(HullAfterAddingArbitaryPoints);
	if (Convex.size() == HullAfterAddingArbitaryPoints.size())
	{
		for (int i = 0; i < n; ++i)
			if (Convex[i] != HullAfterAddingArbitaryPoints[i])
			{
				cout << "NO\n";
				return;
			}
		cout << "YES\n";
	}
	else
		cout << "NO\n";
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