//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
// #define multitest 1
#define Debug 1
typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
const long long mod = 1000000007;
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

typedef long long typeone;
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

typedef long long tslope;
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
	bool isDLessThanx(point p, long long D)
	{
		return Distance2(p) <= D;
	}
};

bool byy(point a, point b)
{
	return a.y < b.y;
}

bool byxy(point a, point b)
{
	return (a.y - a.x) < (b.y - b.x);
}

bool byyx(point a, point b)
{
	return (a.y + a.x) < (b.y + b.x);
}

class PowerSupply
{
private:
	/* data */
public:
	int distOfPointsfromLine(Line l, vector<point> &P, int d)
	{
		int cnt = 0;
		for (int i = 0; i < P.size(); ++i)
		{
			// cout << l.Distance2(P[i]) << ' ';
			if (l.isDLessThanx(P[i], d))
				cnt++;
		}
		return cnt;
	}
	int maxProfit(vector<int> x, vector<int> y, int d)
	{
		int n = x.size();
		vector<point> V(n);
		for (int i = 0; i < n; ++i)
		{
			V[i].x = x[i];
			V[i].y = y[i];
		}
		int ans = 0;
		auto v1 = V;
		sort(v1.begin(), v1.end());
		reverse(v1.begin(), v1.end());
		for (int c = 0; c < n; ++c)
		{
			Line l(0, d + v1.back.y);
			ans = max(ans, distOfPointsfromLine(l, v1, 2*d));
			v1.pop_back();
		}
		v1 = V;
		sort(v1.begin(), v1.end(), byy);
		reverse(v1.begin(), v1.end());
		for (int c = 0; c < n; ++c)
		{
			Line l(0, d + v1.back.x, true, d + v1.back.x);
			ans = max(ans, distOfPointsfromLine(l, v1, 2*d));
			v1.pop_back();
		}
		v1 = V;
		sort(v1.begin(), v1.end(), byxy);
		reverse(v1.begin(), v1.end());
		for (int c = 0; c < n; ++c)
		{
			Line l(1, v1.back.y - v1.back.x - sqrtl(2) * d);
			ans = max(ans, distOfPointsfromLine(l, v1, 2*d));
			v1.pop_back();
		}
		v1 = V;
		sort(v1.begin(), v1.end(), byyx);
		reverse(v1.begin(), v1.end());
		for (int c = 0; c < n; ++c)
		{
			Line l(-1, v1.back.y + v1.back.x - sqrtl(2) * d);
			ans = max(ans, distOfPointsfromLine(l, v1, 2*d));
			v1.pop_back();
		}
		return ans;
	}
};

// int main()
// {
// 	int n;
// 	cin >> n;
// 	vector<int> x(n), y(n);
// 	for (auto &a : x)
// 		cin >> a;
// 	for (auto &a : y)
// 		cin >> a;
// 	int d = 0;
// 	cin >> d;
// 	PowerSupply P;
// 	cout << P.maxProfit(x, y, d);
// 	return 0;
// }