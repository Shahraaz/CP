//https://github.com/Ashishgup1/Competitive-Coding/blob/master/Convex%20Hull%20(Graham's%20Scan).cpp
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

typedef int coord_t;		// coordinate type
typedef long long coord2_t; // must be big enough to hold 2*max(|coordinate|)^2

struct Point
{
	coord_t x, y;
	bool operator<(const Point &p) const
	{
		return x < p.x || (x == p.x && y < p.y);
	}
	Point operator-(Point p)
	{
		Point a = *this;
		a.x -= p.x;
		a.y -= p.y;
		return a;
	}
};

// 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
// Returns a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
coord2_t cross(const Point &O, const Point &A, const Point &B)
{
	return (coord2_t)(A.x - O.x) * (B.y - O.y) - (coord2_t)(A.y - O.y) * (B.x - O.x);
}
coord2_t dot(const Point A, const Point B)
{
	return (coord2_t)(A.x) * (B.x) + (coord2_t)(A.y) * (B.y);
}
coord2_t cross(const Point A, const Point B)
{
	return (coord2_t)(A.x) * (B.y) - (coord2_t)(A.y) * (B.x);
}
coord2_t len(const Point A, const Point B)
{
	return (coord2_t)(A.x - B.x) * (A.x - B.x) + (coord2_t)(A.y - B.y) * (A.y - B.y);
}

// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
vector<Point> convex_hull(vector<Point> &P)
{
	size_t n = P.size(), k = 0;
	if (n <= 1)
		return P;
	vector<Point> H(2 * n);
	// Sort points lexicographically
	sort(P.begin(), P.end());
	// Build lower hull
	for (size_t i = 0; i < n; ++i)
	{
		while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) <= 0)
			k--;
		H[k++] = P[i];
	}
	// Build upper hull
	for (size_t i = n - 1, t = k + 1; i > 0; --i)
	{
		while (k >= t && cross(H[k - 2], H[k - 1], P[i - 1]) <= 0)
			k--;
		H[k++] = P[i - 1];
	}
	H.resize(k - 1);

	return H;
}

struct Data
{
	ll Dot, Len, Cross;
	bool operator==(Data a)
	{
		return (this->Dot == a.Dot) && (this->Cross == a.Cross) && (this->Len == a.Len);
	}
	bool operator!=(Data a)
	{
		return !(*this == a);
	}
};

vector<int> Prefix_function(vector<Data> &v)
{
	int n = v.size(), j;
	vector<int> pi(n);
	for (int i = 1; i < n; ++i)
	{
		j = pi[i - 1];
		db(i, v[i].Cross, v[i].Dot, v[i].Len);
		db(j, v[j].Cross, v[j].Dot, v[j].Len);
		while (j > 0 && (v[i] != v[j]))
		{
			j = pi[j - 1];
			// db(i,v[i].Cross, v[i].Dot, v[i].Len);
			db(j, v[j].Cross, v[j].Dot, v[j].Len);
		}
		if (v[i] == v[j])
			j++;
		db(pi[i], i, j);
		pi[i] = j;
	}
	return pi;
}

bool find_occurences(vector<Data> &text, vector<Data> &pattern)
{
	vector<Data> v = pattern;
	Data a;
	a.Cross = a.Dot = a.Len = -1;
	v.pb(a);
	v.insert(v.end(), text.begin(), text.end());
	int sz1 = text.size(), sz2 = pattern.size();
	vector<int> lps = Prefix_function(v);
	// db(sz1,sz2);
	for (int i = sz2 + 1; i <= sz1 + sz2; ++i)
	{
		db(i, lps[i]);
		if (lps[i] == sz2)
			return true;
	}
	return false;
}

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<Point> Poly1(n), Poly2(m);
	for (auto &x : Poly1)
		cin >> x.x >> x.y;
	for (auto &x : Poly2)
		cin >> x.x >> x.y;
	Poly1 = convex_hull(Poly1);
	Poly2 = convex_hull(Poly2);
	db(Poly1.size(), Poly2.size());
	// for (auto x : Poly1)
	// 	cout << x.x << ' ' << x.y << ' ';
	// cout << '\n';
	// for (auto x : Poly2)
	// 	cout << x.x << ' ' << x.y << ' ';
	// cout << '\n';
	if (Poly1.size() != Poly2.size())
	{
		cout << "NO";
		return;
	}
	n = Poly1.size();
	vector<Data> hull1, hull2;
	for (int i = 0; i < n; ++i)
	{
		Data curr;
		Point a = Poly1[i];
		Point b = Poly1[(1 + i) % n];
		Point c = Poly1[(2 + i) % n];
		curr.Len = len(b, a);
		curr.Dot = dot(b - a, c - b);
		curr.Cross = cross(b - a, c - b);
		db(curr.Len,
		   curr.Dot,
		   curr.Cross);
		hull1.pb(curr);
	}
	hull1.insert(hull1.end(), hull1.begin(), hull1.end());
	db("Hull2");
	for (int i = 0; i < n; ++i)
	{
		Data curr;
		Point a = Poly2[i];
		Point b = Poly2[(1 + i) % n];
		Point c = Poly2[(2 + i) % n];
		curr.Len = len(b, a);
		curr.Dot = dot(b - a, c - b);
		curr.Cross = cross(b - a, c - b);
		db(curr.Len,
		   curr.Dot,
		   curr.Cross);
		hull2.pb(curr);
	}
	if (find_occurences(hull1, hull2))
		cout << "YES\n";
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