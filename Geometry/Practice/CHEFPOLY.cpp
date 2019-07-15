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

typedef complex<int> point;
typedef vector<point> Polygon;
Polygon inputRed;
Polygon inputBlack;
int n, m, x, y;
int base = 0;
vector<vector<int>> blackInside(200, vector<int>(200));

ll cross(point o, point a, point b)
{
	a -= o;
	b -= o;
	return (ll)real(a) * imag(b) - (ll)imag(a) * real(b);
}

ll cw(point a, point o, point b)
{
	a -= o;
	b -= o;
	return (ll)real(a) * imag(b) - (ll)imag(a) * real(b);
}

complex<ld> *Intersection(point s1, point e1, point s2, point e2)
{
	if (real(e1) < real(s1))
		swap(s1, e1);
	if (real(e2) < real(s2))
		swap(s2, e2);
	if (real(s2) < real(s1))
	{
		swap(s1, s2);
		swap(e1, e2);
	}
	db(s1, e1, s2, e2);
	if (real(e1) >= real(s2))
	{
		ll a1 = imag(e1 - s1);
		ll b1 = real(s1 - e1);
		ll c1 = a1 * real(e1) + b1 * imag(e1);

		ll a2 = imag(e2 - s2);
		ll b2 = real(s2 - e2);
		ll c2 = a2 * real(e2) + b2 * imag(e2);

		ll det = (ll)a1 * b2 - (ll)a2 * b1;
		// db(det);
		if (det == 0)
		{
			// if (a1 == a2)
			// 	if (real(s1) <= real(s2) && real(s2) <= real(e2))
			// 		return new complex<ld>(real(s2), imag(s2));
			// 	else
			// 		return NULL;
			db("Don't Intersect3");
			return NULL;
		}
		ll x = (b2 * c1 - b1 * c2);
		ll y = (c2 * a1 - c1 * a2);
		db(x, y);
		if ((det * real(s1)) <= x && x <= (det * real(e1)) && (det * real(s2)) <= x && x <= (det * real(e2)))
		{
			if ((det * min(imag(e1), imag(s1))) <= y && y <= (det * max(imag(e1), imag(s1))) && (det * min(imag(e2), imag(s2))) <= y && y <= (det * max(imag(e2), imag(s2))))
			{
				db("Intersect");
				return new complex<ld>(x, y);
			}
			db("Don't Intersect4");
		}
		else
			db("Don't Intersect2");
		return NULL;
	}
	db("Don't Intersect1");
	return NULL;
}

bool isInside(point o, point a, point b, point p)
{
	int cnt = 0;
	if (imag(o) > imag(a))
		swap(o, a);
	if (imag(o) > imag(b))
		swap(o, b);
	if (imag(b) > imag(a))
		swap(a, b);
	point extreme(mod, imag(p));
	if (imag(p) == imag(b))
		return false;
	if (imag(p) == imag(o))
		return false;
	if (auto it = Intersection(o, a, p, extreme))
		cnt++;
	if (auto it = Intersection(a, b, p, extreme))
		cnt++;
	if (auto it = Intersection(b, o, p, extreme))
		cnt++;
	return cnt & 1;
}

bool isInsideTriangle(point a, point b, point c, point d)
{
	auto bcd = abs(cw(b, c, d));
	auto acd = abs(cw(a, c, d));
	auto abd = abs(cw(a, b, d));
	auto abc = abs(cw(a, b, c));
	return abc == abd + acd + bcd;
}

void countBlack(int i, int j)
{
	// db(i, j);
	point red1 = inputRed[i];
	point red2 = inputRed[j];
	if (cross(point(0, 0), red1, red2) <= 0)
		return;
	int ans = 0;
	for (int p = 0; p < m; ++p)
	{
		bool t = isInside(red1, point(0, 0), red2, inputBlack[p]);
		ans += t;
		db(t, red1, "origin", red2, inputBlack[p]);
	}
	blackInside[i][j] = ans;
	blackInside[j][i] = -ans;
}

void solve()
{
	cin >> n >> m;
	inputRed.resize(n);
	inputBlack.resize(m);
	for (int i = 0; i < n; ++i)
	{
		cin >> x >> y;
		inputRed[i] = point(x + base, y + base);
	}
	for (int i = 0; i < m; ++i)
	{
		cin >> x >> y;
		inputBlack[i] = point(x + base, y + base);
	}
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			countBlack(i, j);

	int q, k, prev, start, curr;
	cin >> q;
	while (q--)
	{
		cin >> k;
		cin >> prev;
		start = prev;
		int ans = 0;
		for (int i = 1; i < k; ++i)
		{
			cin >> curr;
			ans += blackInside[prev - 1][curr - 1];
			prev = curr;
		}
		ans += blackInside[curr - 1][start - 1];
		cout << abs(ans) << '\n';
	}
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