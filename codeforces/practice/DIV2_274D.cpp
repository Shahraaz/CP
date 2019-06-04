//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
// #define multitest 1
#define Debug 1
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

vector<ll> S(vector<ll> v, int x, int y)
{
	vector<ll> ans;
	int c1 = count(v.begin(), v.end(), x);
	int c2 = count(v.begin(), v.end(), y);
	if (c1 > 0 && c2 > 0)
		return ans;
	if (c1 > 0)
	{
		for (auto it = v.begin(); it != v.end(); ++it)
		{
			if (binary_search(v.begin(), v.end(), *it + y))
				return ans;
			if (binary_search(v.begin(), v.end(), *it - y))
				return ans;
		}
		ans.pb(y);
		return ans;
	}
	if (c2 > 0)
	{
		for (auto it = v.begin(); it != v.end(); ++it)
		{
			if (binary_search(v.begin(), v.end(), *it + x))
				return ans;
			if (binary_search(v.begin(), v.end(), *it - x))
				return ans;
		}
		ans.pb(x);
		return ans;
	}
	bool a, b;
	a = b = false;
	for (auto it = v.begin(); it != v.end(); ++it)
	{
		if (binary_search(v.begin(), v.end(), *it + y))
			a = true;
		if (binary_search(v.begin(), v.end(), *it - y))
			a = true;
	}
	for (auto it = v.begin(); it != v.end(); ++it)
	{
		if (binary_search(v.begin(), v.end(), *it + x))
			b = true;
		if (binary_search(v.begin(), v.end(), *it - x))
			b = true;
	}
	if (a & b)
		return vector<ll>(0);
	ans.pb(x);
	ans.pb(y);
	for (auto it = v.begin(); it != v.end(); ++it)
	{
		if (binary_search(v.begin(), v.end(), *it + x))
		{
			if (binary_search(v.begin(), v.end(), *it + x + y))
				return vector<ll>(0);
			if (binary_search(v.begin(), v.end(), *it + x - y))
				return vector<ll>(0);
			ans.clear();
			ans.pb(y);
		}
		else
		{
			if (binary_search(v.begin(), v.end(), *it + x + y))
			{
				if ((*it + x) <= v.back())
				{
					ans.clear();
					ans.pb(*it + x);
				}
			}
			if (binary_search(v.begin(), v.end(), *it + x - y))
			{
				if ((*it + x) <= v.back())
				{
					ans.clear();
					ans.pb(*it + x);
				}
			}
		}

		if (binary_search(v.begin(), v.end(), *it - x))
		{
			if (binary_search(v.begin(), v.end(), *it - x + y))
				return vector<ll>(0);
			if (binary_search(v.begin(), v.end(), *it - x - y))
				return vector<ll>(0);
			ans.clear();
			ans.pb(y);
		}
		else
		{
			if (binary_search(v.begin(), v.end(), *it - x + y))
			{
				if ((*it - x) <= v.back() && (*it - x) >= v.front())
				{
					ans.clear();
					ans.pb(*it - x);
				}
			}
			if (binary_search(v.begin(), v.end(), *it - x - y))
			{
				if ((*it - x) <= v.back() && (*it - x) >= v.front())
				{
					ans.clear();
					ans.pb(*it - x);
				}
			}
		}

		swap(x, y);

		if (binary_search(v.begin(), v.end(), *it + x))
		{
			if (binary_search(v.begin(), v.end(), *it + x + y))
				return vector<ll>(0);
			if (binary_search(v.begin(), v.end(), *it + x - y))
				return vector<ll>(0);
			ans.clear();
			ans.pb(y);
		}
		else
		{
			if (binary_search(v.begin(), v.end(), *it + x + y))
			{
				if ((*it + x) <= v.back())
				{
					ans.clear();
					ans.pb(*it + x);
				}
			}
			if (binary_search(v.begin(), v.end(), *it + x - y))
			{
				if ((*it + x) <= v.back())
				{
					ans.clear();
					ans.pb(*it + x);
				}
			}
		}

		if (binary_search(v.begin(), v.end(), *it - x))
		{
			if (binary_search(v.begin(), v.end(), *it - x + y))
				return vector<ll>(0);
			if (binary_search(v.begin(), v.end(), *it - x - y))
				return vector<ll>(0);
			ans.clear();
			ans.pb(y);
		}
		else
		{
			if (binary_search(v.begin(), v.end(), *it - x + y))
			{
				if ((*it - x) <= v.back() && (*it - x) >= v.front())
				{
					ans.clear();
					ans.pb(*it - x);
				}
			}
			if (binary_search(v.begin(), v.end(), *it - x - y))
			{
				if ((*it - x) <= v.back() && (*it - x) >= v.front())
				{
					ans.clear();
					ans.pb(*it - x);
				}
			}
		}
		swap(x,y);
	}
	return ans;
}

void solve()
{
	int n, l, x, y;
	cin >> n >> l >> x >> y;
	vector<ll> V(n);
	for (auto &x : V)
		cin >> x;
	auto a = S(V, x, y);
	cout << a.size() << '\n';
	for (auto x : a)
		cout << x << ' ';
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