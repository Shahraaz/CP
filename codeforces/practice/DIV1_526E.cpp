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

ll inf = 1e18;

struct convexHullDynamic
{
	bool isMax;
	struct Line
	{
		ll m, c; // y = m*x+c
		ld xleft;
		enum Type
		{
			line,
			maxQuery,
			minQuery
		} type;
		ll val;
		Line(ll _m = 0, ll _c = 0) : m(_m), c(_c), xleft(-inf), type(Type::line), val(0)
		{
		}
		ll valueAt(int x)
		{
			return m * x + c;
		}
		bool isParallel(Line l1, Line l2)
		{
			return l1.m == l2.m;
		}
		ld intersectX(Line l1, Line l2)
		{
			if (isParallel(l1, l2))
				return inf;
			return (l2.c - l1.c) / ((ld)l1.m - l2.m);
		}
		bool operator<(const Line &l) const
		{
			if (l.type == line)
				return this->m < l.m;
			if (l.type == maxQuery)
				return this->xleft < l.val;
			// if (l.type == minQuery)
			return this->xleft > l.val;
		}
	};
	set<Line> Hull;
	bool hasPrev(set<Line>::iterator it)
	{
		return it != Hull.begin();
	}
	bool hasNext(set<Line>::iterator it)
	{
		return it != Hull.end() && next(it) != Hull.end();
	}
	bool irrelevant(Line l1, Line l2, Line l3)
	{
		Line temp;
		return temp.intersectX(l1, l3) <= temp.intersectX(l1, l2);
	}
	bool irrelevant(set<Line>::iterator it)
	{
		return hasPrev(it) && hasNext(it) && ((isMax && irrelevant(*prev(it), *it, *next(it))) || (!isMax && irrelevant(*next(it), *it, *prev(it))));
	}
	set<Line>::iterator updateLeftBorder(set<Line>::iterator it)
	{
		if (isMax && !hasPrev(it) || !isMax && !hasNext(it))
			return it;
		Line temp = *it;
		ld val = temp.intersectX(*it, isMax ? *prev(it) : *next(it));
		it = Hull.erase(it);
		temp.xleft = val;
		return Hull.insert(it, temp);
	}
	convexHullDynamic(bool _isMax = true) : isMax(_isMax)
	{
	}
	void addLine(ll m, ll c)
	{
		Line l3 = Line(m, c);
		auto it = Hull.lower_bound(l3);
		if (it != Hull.end() && l3.isParallel(*it, l3))
		{
			if (isMax && it->c < c || !isMax && it->c > c)
				it = Hull.erase(it);
			else
				return;
		}
		it = Hull.insert(it, l3);
		if (irrelevant(it))
		{
			Hull.erase(it);
			return;
		}
		while (hasPrev(it) && irrelevant(prev(it)))
			Hull.erase(prev(it));
		while (hasNext(it) && irrelevant(next(it)))
			Hull.erase(next(it));
		it = updateLeftBorder(it);
		if (hasPrev(it))
			updateLeftBorder(prev(it));
		if (hasNext(it))
			updateLeftBorder(next(it));
	}
	ll getBest(ll x)
	{
		Line q;
		q.val = x;
		q.type = isMax ? Line::Type::maxQuery : Line::Type::minQuery;
		auto bestline = Hull.lower_bound(q);
		if (isMax)
			--bestline;
		q = *bestline;
		return q.valueAt(x);
	}
	void print()
	{
		for (auto it : Hull)
			db(it.m, it.c, it.val, it.xleft, it.type);
	}
};

const int N = 1e5 + 10;
int n;
ll a[N], b[N], dp[N];
convexHullDynamic hull(0);

void solve()
{
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	for (int i = 0; i < n; ++i)
		cin >> b[i];
	dp[0] = 0;
	hull.addLine(b[0], dp[0]);
	for (int i = 1; i < n; ++i)
	{
		// hull.print();
		// db(hull.getBest(a[i]));
		dp[i] = hull.getBest(a[i]);

		hull.addLine(b[i], dp[i]);
	}
	cout << dp[n - 1];
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