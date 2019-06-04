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

/*reference https://github.com/Ashishgup1/Competitive-Coding/blob/master/Convex%20Hull%20(Graham's%20Scan).cpp
COmputational Geometry and Computational Graphics in C++ by Michael J.Laszlo*/

/////////////////////////////////

typedef ld typeone;
typedef long double typetwo;
enum
{
	LEFT,
	RIGHT,
	BEYOND,
	BEHIND,
	BETWEEN,
	ORIGIN,
	DESTINATION
};

const long double EPS = 1e-9;
class point
{
public:
	typeone x, y;
	point(typeone _x = 0, typeone _y = 0) : x(_x), y(_y) {}
	bool operator<(const point &p) const
	{
		return (x < p.x) || (x == p.x && y < p.y);
	}
	bool operator>(point &p)
	{
		return (x > p.x) || (x == p.x && y > p.y);
	}
	bool operator==(point &p)
	{
		return x == p.x && y == p.y;
	}
	bool operator!=(point &p)
	{
		return !(*this == p);
	}
	point operator=(const point &p)
	{
		x = p.x;
		y = p.y;
		return *this;
	}
	point operator*(typetwo s)
	{
		return point(s * x, s * y);
	}
	point operator+(point &p)
	{
		return point(x + p.x, y + p.y);
	}
	point operator-(point &p)
	{
		return point(x - p.x, y - p.y);
	}
	typeone operator[](const int i)
	{
		return i == 0 ? x : y;
	}
	typeone orientation(point p0, point p1, point p2)
	{
		p1 = p1 - p0;
		p2 = p2 - p0;
		typeone sa = p1.x * p2.y - p2.x * p1.y;
		if (sa > 0)
			return 1;
		if (sa < 0)
			return -1;
		return 0;
	}
	typeone len2()
	{
		return x * x + y * y;
	}
	typetwo len()
	{
		return sqrtl((long double)len2());
	}

	typetwo PolarAngle()
	{
		if (x == 0 && y == 0)
			return 0;
		if (x == 0)
			return (y > 0) ? 90 : 270;
		typetwo theta = atanf((long double)y / x);
		theta *= 180 / (long double)3.141592653;
		if (x > 0)
			return y >= 0 ? theta : 360 + theta;
		else
			return 180 + theta;
	}
	int classify(point &p0, point &p1)
	{
		point p2 = *this;
		point a = p1 - p0;
		point b = p2 - p0;
		typeone sa = a.x * b.y - b.x * a.y;
		if (sa > 0)
			return LEFT;
		if (sa < 0)
			return RIGHT;
		if ((a.x * b.x < 0) || (a.y * b.y < 0))
			return BEHIND;
		if (a.len2() < b.len2())
			return BEYOND;
		if (p0 == p2)
			return ORIGIN;
		if (p0 == p1)
			return DESTINATION;
		return BETWEEN;
	}
};

typedef ld tslope;
typedef long double tconstant;
typedef long double D2;
class Line
{
public:
	// y - m*x - c = 0;
	tslope m;
	tconstant c;
	bool isverticle;
	tconstant xincident;
	Line(tslope _m = 0, tconstant _c = 0, bool b = false, tconstant _xincident = 0) : m(_m), c(_c), isverticle(b), xincident(_xincident) {}
	D2 Distance2(point p)
	{
		if (isverticle)
			return abs(xincident - p.x);
		return abs(p.y - m * (p.x) - c) / sqrtl(1 + m * m);
	}
	bool isDLessThanx(point p, long double D)
	{
		return Distance2(p) <= D;
	}
};

#define PI 3.1415926535

// returns square of distance b/w two points
long double lengthSquare(point X, point Y)
{
	auto xDiff = X.x - Y.x;
	auto yDiff = X.y - Y.y;
	return xDiff * xDiff + yDiff * yDiff;
}

ld printAngle(point A, point B, point C)
{
	// Square of lengths be a2, b2, c2
	ll a2 = lengthSquare(B, C);
	ll b2 = lengthSquare(A, C);
	ll c2 = lengthSquare(A, B);

	// lenght of sides be a, b, c
	ld a = sqrtl(a2);
	ld b = sqrtl(b2);
	ld c = sqrtl(c2);

	// From Cosine law
	ld gamma = acosl((-a2 + b2 + c2) / (2 * c * b));
	return gamma;
	// printing all the angles
}

ld printAngle(ld A, ld B, ld C)
{
	// Square of lengths be a2, b2, c2
	ll a2 = A * A;
	ll b2 = B * B;
	ll c2 = C * C;

	// lenght of sides be a, b, c
	ld a = A;
	ld b = B;
	ld c = C;

	// From Cosine law
	ld gamma = acosl((-a2 + b2 + c2) / (2 * c * b));
	return gamma;
	// printing all the angles
}

//rectangular class

ld dist(point a, point b)
{
	return sqrtl((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void solve()
{
	int x1, y1, x2, y2, r;
	cin >> x1 >> y1 >> x2 >> y2 >> r;
	point a(x1, y1);
	point b(x2, y2);
	Line l;
	if (a.x == b.x)
		l = Line(0, 0, true, a.x);
	else
		l = Line((a.y - b.y) / (1.0 * a.x - b.x), a.y - (a.y - b.y) / (1.0 * a.x - b.x) * a.x);
	if (l.isDLessThanx(point(0, 0), r))
	{
		db("A");
		ld phi = printAngle(point(0, 0), a, b);
		ld d1 = sqrtl(a.len2() - r * r);
		ld d2 = sqrtl(b.len2() - r * r);
		phi -= printAngle(d1, r, a.len());
		phi -= printAngle(d2, r, b.len());
		ld d3 = r * phi;
		d3 = min(d3, r * (2 * PI - phi) * r);
		cout << fixed << setprecision(6) << (d1 + d2 + d3) << '\n';
	}
	else
	{
		db("B");
		ld t1 = a.PolarAngle();
		ld t2 = b.PolarAngle();
		ld th = (t1 + t2) / 2;
		// db(t1,t2,th);
		db(t1, t2, th);
		point X(r * cosl(th * PI / 180), r * sinl(th * PI / 180));
		db(X.x, X.y);
		th += 180;
		th = th - (int)th / (360);
		db(t1, t2, th);
		point Y(r * cosl(th * PI / 180), r * sinl(th * PI / 180));
		db(Y.x, Y.y);
		ld a1 = dist(a, X) + dist(b, X);
		ld a2 = dist(a, Y) + dist(b, Y);
		cout << fixed << setprecision(6) << min(a1, a2) << '\n';
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
