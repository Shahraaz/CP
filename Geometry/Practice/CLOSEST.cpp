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

struct point
{
	ld x, y;
	point() {}
	point(ld _x, ld _y) : x(_x), y(_y) {}
	point operator-(point a)
	{
		return point(x - a.x, y - a.y);
	}
	ld distsq()
	{
		return x * x + y * y;
	}
};

int size(vector<point> &P)
{
	return P.size();
}

point middle(point a, point b)
{
	return point((a.x + b.x) / 2, (a.y + b.y) / 2);
}

bool cmpx(point a, point b)
{
	return a.x == b.x ? a.y < b.y : a.x < b.x;
}

bool cmpy(point a, point b)
{
	return a.y == b.y ? a.x < b.x : a.y < b.y;
}

ld dist(point a, point b)
{
	return sqrtl((a - b).distsq());
}

ld perimeter(point a, point b, point c)
{
	return dist(a, b) + dist(a, c) + dist(b, c);
}

ld calc(int n, point Points[], vector<point> &PointsByY)
{
	// db(n);
	if (n <= 3)
		return 1e18;
	int left = n / 2;
	int right = n - left;
	point split = middle(Points[left - 1], Points[left]);
	vector<point> PointsByYLeft, PointsByYRight;
	for (auto x : PointsByY)
		if (cmpx(x, split))
			PointsByYLeft.pb(x);
		else
			PointsByYRight.pb(x);
	ld res = min(calc(PointsByYLeft.size(), Points, PointsByYLeft), calc(PointsByYRight.size(), Points + PointsByYLeft.size(), PointsByYRight));
	// db(res);
	ll margin = res / 2;
	vector<point> closeToThePoints;
	int start = 0;
	for (int i = 0; i < n; ++i)
	{
		point p = PointsByY[i];
		if (abs(p.x - split.x) > margin)
			continue;
		while (start < size(closeToThePoints) && (p.y - closeToThePoints[start].y > margin))
			++start;
		for (int i = start; i < size(closeToThePoints); ++i)
			for (int j = i + 1; j < size(closeToThePoints); ++j)
				res = min(res, perimeter(p, closeToThePoints[i], closeToThePoints[j]));
		closeToThePoints.pb(p);
	}
	return res;
}

ld calc(vector<point> &Points)
{
	sort(Points.begin(), Points.end(), cmpx);
	vector<point> PointsByY = Points;
	sort(PointsByY.begin(), PointsByY.end(), cmpy);
	return calc(size(Points), &Points[0], PointsByY);
}

void solve(int n)
{
	// db(n);
	int x, y;
	// cin >> n;
	vector<point> Points(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> x >> y;
		Points[i] = point(x, y);
	}
	cout << fixed << setprecision(3) << calc(Points) << '\n';
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
	cin >> t;
	while (t != -1)
	{
		solve(t);
		cin >> t;
	}
#ifndef Online
	TimeEnd = chrono::steady_clock::now();
	auto ElapsedTime = TimeEnd - TimeStart;
	cout << "\n\nTime elapsed: " << chrono::duration<double>(ElapsedTime).count() << " seconds.\n";
#endif
	return 0;
}