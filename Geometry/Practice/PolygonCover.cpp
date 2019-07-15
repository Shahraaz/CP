//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
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

class PolygonCover
{
private:
	ll area(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3)
	{
		return abs((x1 - x2) * (y1 + y2) + (x2 - x3) * (y2 + y3) + (x3 - x1) * (y1 + y3));
	}

public:
	double getArea(vector<int> x, vector<int> y)
	{
		int n = x.size();
		int m = 1LL << n;
		vector<ll> BitMaskedArea(m, 1e18);
		BitMaskedArea[0] = 0;
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)
				for (int k = j + 1; k < n; ++k)
					for (int l = k + 1; l < n; ++l)
					{
						ll p = i | (1 << j) | (1 << k) | (1 << l);
						ll g = area(x[j], y[j], x[k], y[k], x[l], y[l]);
						if (BitMaskedArea[p] > BitMaskedArea[i] + g)
							BitMaskedArea[p] = BitMaskedArea[i] + g;
					}
		return (double)BitMaskedArea[m - 1] / 2;
	}
};

#ifndef Online
int main()
{
	PolygonCover T;
	cout << T.solve();
	return 0;
}
#endif