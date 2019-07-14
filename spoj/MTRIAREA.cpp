//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define multitest 1
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

using ll = long long;
#define f first
#define s second
#define pb push_back
const long long mod = 1000000007;
auto TimeStart = chrono::steady_clock::now();

const int nax = 2e5 + 10;
typedef complex<int> Point;
typedef vector<Point> Polygon;

bool cmp(Point a, Point b)
{
	if (real(a) == real(b))
		return imag(a) < imag(b);
	return real(a) < real(b);
}

Polygon convex_hull(Polygon &P)
{
	int n = P.size();
	if (n <= 3)
		return P;
	Polygon H(2 * n);
	sort(P.begin(), P.end(),cmp);
	return P;
}

void solve(int n)
{
	int x, y;
	Polygon inp(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> x >> y;
		inp[i] = Point(x, y);
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	int n;
	while (cin >> n, n != -1)
		solve(n);
#ifdef TIME
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}