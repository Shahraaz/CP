//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
#define multitest 1
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

typedef pair<complex<ll>, int> point;

bool cmp(point a1, point b1)
{
	auto a = a1.f;
	auto b = b1.f;
	return imag(a - b) == 0 ? (real(a - b) == 0 ? (a1.s < b1.s) : (real(a) < real(b)))
							: (imag(a) < imag(b));
}

ll cross(point o, point a1, point b1)
{
	auto a = a1.f - o.f;
	auto b = b1.f - o.f;
	return real(a) * imag(b) - real(b) * imag(a);
}

vector<point> ConvexHull(vector<point> Polygon)
{
	int n = Polygon.size();
	if (n < 2)
		return Polygon;
	vector<point> H(2 * n);
	sort(Polygon.begin(), Polygon.end(), cmp);
	int k = 0;
	for (int i = 0; i < n; ++i)
	{
		// db(i, Polygon[i].f, Polygon[i].s);
		while (k >= 2 && (cross(H[k - 2], H[k - 1], Polygon[i]) <= 0))
			k--;
		H[k++] = Polygon[i];
	}
	int t = k + 1;
	for (int i = n - 1; i > 0; --i)
	{
		// db(i, Polygon[i].f, Polygon[i].s);
		while (k >= t && cross(H[k - 2], H[k - 1], Polygon[i - 1]) <= 0)
			k--;
		H[k++] = Polygon[i - 1];
	}
	H.resize(k - 1);
	return H;
}

ld abs1(complex<ll> a)
{
	return sqrtl(norm(a));
}

ld Perimeter(vector<point> Polygon)
{
	int n = Polygon.size();
	if (n < 2)
		return 0;
	ld ans = 0;
	for (int i = 0; i < n; ++i)
	{
		// cout << Polygon[i].f << ' ' << Polygon[(i + 1) % n].f << ' ' << abs1(Polygon[i].f - Polygon[(i + 1) % n].f) << '\n';
		ans += abs1(Polygon[i].f - Polygon[(i + 1) % n].f);
	}
	return ans;
}

void PrintPolygon(vector<point> Polygon)
{
	for (auto x : Polygon)
		cout << x.s << ' ';
	cout << '\n';
	cout << '\n';
}

void solve()
{
	int n, x, y;
	cin >> n;
	vector<point> Polygon(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> x >> y;
		Polygon[i] = point(complex<ll>(x, y), i + 1);
	}
	sort(Polygon.begin(), Polygon.end(), cmp);
	int size = 0;
	for (int i = 0; i < n; ++i)
	{
		if (size == 0 || (Polygon[size - 1].f != Polygon[i].f))
			Polygon[size++] = Polygon[i];
	}
	Polygon.resize(size);
	// PrintPolygon(Polygon);
	Polygon = ConvexHull(Polygon);
	cout << fixed << setprecision(2) << Perimeter(Polygon) << '\n';
	PrintPolygon(Polygon);
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
	while (t--)
		solve();
#ifndef Online
	TimeEnd = chrono::steady_clock::now();
	auto ElapsedTime = TimeEnd - TimeStart;
	cout << "\n\nTime elapsed: " << chrono::duration<double>(ElapsedTime).count() << " seconds.\n";
#endif
	return 0;
}