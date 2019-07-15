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
	typeone operator[](int i)
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

class BoxUnion
{
public:
	int area(vector<string> in)
	{
		int n = in.size(), x, y;
		vector<pair<pair<point, point>, bool>> P;
		for (int i = 0; i < n; ++i)
		{
			stringstream sin(in[i]);
			sin >> x;
			sin >> y;
			// db(x,y);
			point a(x, y);
			sin >> x;
			sin >> y;
			// db(x,y);
			point b(x, y);
			P.pb({{a, b}, 0});
			P.pb({{b, a}, 1});
		}
		sort(P.begin(), P.end());
		int prevx = P[0].f.f[0], A = 0;
		vector<int> Lowerend, Upperend;
		for (int i = 0; i < 2 * n; ++i)
		{
			// db(i,Lowerend.size());
			if (Lowerend.size())
			{
				sort(Lowerend.begin(), Lowerend.end());
				sort(Upperend.begin(), Upperend.end());
				int cura = Lowerend[0], curb = Upperend[0];
				int ht = 0;
				for (int j = 1; j < Lowerend.size(); ++j)
				{
					// db(curb, Lowerend[j]);
					if (curb < Lowerend[j])
					{
						ht += curb - cura;
						cura = Lowerend[j];
					}
					curb = Upperend[j];
				}
				ht += curb - cura;
				if (P[i].s)
				{
					// if (cnt)
					A += ht * (P[i].f.f.x - prevx);
					db(i, A, ht, prevx, P[i].f.f.x, P[i].f.f.x - prevx);
				}
				else
				{
					// if (cnt)
					A += ht * (P[i].f.f.x - prevx);
					db(i, A, ht, prevx, P[i].f.f.x, P[i].f.f.x - prevx);
				}
			}
			prevx = P[i].f.f.x;
			if (P[i].s == 0)
			{
				// cnt++;
				Lowerend.pb(P[i].f.f[1]);
				Upperend.pb(P[i].f.s[1]);
			}
			else
			{
				// cnt--;
				y = P[i].f.f[1];
				x = P[i].f.s[1];
				for (auto it = Lowerend.begin(); it != Lowerend.end(); ++it)
				{
					if (*it == x)
					{
						Lowerend.erase(it);
						break;
					}
				}
				for (auto it = Upperend.begin(); it != Upperend.end(); ++it)
				{
					if (*it == y)
					{
						Upperend.erase(it);
						break;
					}
				}
			}
		}
		return A;
	}
};

int main()
{
	int n,x,y,u,v;
	cin >> n;
	vector<string> V;
	for(int i=0;i<n;++i)
	{
		string s = "";
		cin >> x >> y >> u >> v;
		s += to_string(x);
		s += ' ';
		s += to_string(y);
		s += ' ';
		s += to_string(u);
		s += ' ';
		s += to_string(v);
		s += ' ';
		V.pb(s);
	}
	BoxUnion S;
	//  "0 0 10 10", "20 20 30 30"
	// V.pb("0 0 10 10");
	// V.pb("20 20 30 30");
	// { "0 500 20000 501", "500 0 501 20000" }
	// V.pb("0 0 10 10");
	// V.pb("20 20 30 30");
	// V.pb("3 1 7 5");
	// V.pb("4 4 9 7");
	// V.pb("1 3 5 6");
	cout << S.area(V);
	return 0;
}