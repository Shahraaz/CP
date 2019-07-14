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

int cross(Point o, Point a, Point b)
{
	a -= o;
	b -= o;
	return real(a) * imag(b) - imag(a) * real(b);
}

Polygon convex_hull(Polygon &P)
{
	int n = P.size();
	if (n <= 3)
		return P;
	Polygon H(2 * n);
	sort(P.begin(), P.end(), cmp);
	int k = 0;
	for (int i = 0; i < n; ++i)
	{
		while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) <= 0)
			--k;
		H[k++] = P[i];
	}
	int t = k + 1;
	for (int i = n - 1; i > 0; --i)
	{
		while (k >= t && cross(H[k - 2], H[k - 1], P[i - 1]) <= 0)
			--k;
		H[k++] = P[i - 1];
	}
	H.resize(k - 1);
	return H;
}

int inc(int a, int n)
{
	a++;
	if (a >= n)
		a -= n;
	return a;
}

double maxTri(Polygon &Hull)
{
	int a, b, c, n = Hull.size();
	int ans = 0;
	a = 0;
	b = 1;
	c = 2;
	for (; a < n; ++a)
	{
		if (a == b)
			b = inc(b, n);
		if (c == b)
			c = inc(c, n);
		while (true)
		{
			while (abs(cross(Hull[a], Hull[b], Hull[c])) <= abs(cross(Hull[a], Hull[b], Hull[inc(c, n)])))
				c = inc(c, n);
			if (abs(cross(Hull[a], Hull[b], Hull[c])) <= abs(cross(Hull[a], Hull[inc(b, n)], Hull[c])))
				b = inc(b, n);
			else
				break;
		}
		int curr = abs(cross(Hull[a], Hull[b], Hull[c]));
		ans = max(curr, ans);
	}
	return 0.5 * ans;
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
	inp = convex_hull(inp);
#ifndef Brute
	cout << fixed << setprecision(2) << maxTri(inp) << '\n';
	/*
		Sadly the testcases were weak above solution gives wrong answer
		9
		4752 4262
		3383 413
		759 2927
		4745 4322
		1213 691
		2506 4423
		3040 4460
		1000 1000
		5000 1000
		9
		2459 691
		2828 758
		4361 1951
		4183 4244
		3832 4647	
		2529 5756
		2481 5718
		0 3587
		728 2028
		-1
		the correct output is:
		6920000.00
		6919204.00 
	 */
#else
	int ans = 0;
	n = inp.size();
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			for (int k = j + 1; k < n; ++k)
				ans = max(ans, abs(cross(inp[i], inp[j], inp[k])));
	cout << fixed << setprecision(2);
	cout << ans * 0.5 << '\n';
#endif
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