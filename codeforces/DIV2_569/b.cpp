//Optimise
#include <bits/stdc++.h>
using namespace std;

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

void solve()
{
	srand(time(NULL));
	int n;
	cin >> n;
	// n = (rand() % 15 + 1);
	// n = 1e5;
	vector<int> v(n);
	ll maxprod = 1;
	for (auto &x : v)
	{
		cin >> x;
		// x = rand() % 60 - 30;
		// x = 1e6;
		if (x >= 0)
			x = (-x - 1);
		maxprod *= x;
	}
	if (n & 1)
	{
		ll maxprod1 = maxprod;
		bool change = false;
		int idx = 0;
		// auto it = min_element(v.begin(), v.begin()) - v.begin();
		// db("here");
		for (int i = 0; i < n; ++i)
		{
			db(i, v[i]);
			{
				// db(maxprod * (-v[i] - 1) / v[i], maxprod1);
				if ((maxprod * (-v[i] - 1)) / v[i] > (maxprod1))
				{
					db(i);
					change = true;
					maxprod1 = maxprod / v[i] * (-v[i] - 1);
					idx = i;
				}
			}
		}
		// db("here");
		for (int i = 0; i < n; ++i)
		{
			if (i == idx && change)
				cout << -v[i] - 1 << ' ';
			else
				cout << v[i] << ' ';
		}
	}
	else
	{
		for (int i = 0; i < n; ++i)
			cout << v[i] << ' ';
	}
}

int main()
{
#ifndef Debug
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#endif
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (t--)
		solve();
	return 0;
}