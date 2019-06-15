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

vector<int> divisors(int a)
{
	vector<int> Temp;
	int n = a;
	for (int i = 1; i * i <= n; ++i)
		if (a % i == 0)
		{
			Temp.pb(i);
			if (a != (i * i))
				Temp.pb(a / i);
		}
	sort(Temp.begin(),Temp.end());
	return Temp;
}

vector<int> Intersection(vector<int> a, vector<int> b)
{
	vector<int> Temp;
	int i = 0, j = 0, n = a.size(), m = b.size();
	while (i < n && j < m)
	{
		// db(a[i], b[j], i, j);
		if (a[i] < b[j])
			++i;
		else if (a[i] > b[j])
			++j;
		else
		{
			Temp.pb(a[i]);
			++i;
			++j;
		}
	}
	return Temp;
}

void solve()
{
	int a, b;
	cin >> a >> b;
	auto A = divisors(a);
	auto B = divisors(b);
	auto intersection = Intersection(A, B);
	// db(A.size());
	// db(B.size());
	// db(intersection.size());
	// for (auto x : intersection)
	// 	db(x);
	int n;
	cin >> n;
	while (n--)
	{
		cin >> a >> b;
		auto up = upper_bound(intersection.begin(), intersection.end(), b);
		auto lo = lower_bound(intersection.begin(), intersection.end(), a);
		if(up-lo)
			cout << *prev(up) << '\n';
		else cout << -1 << '\n';
	}
	// db("ou");
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (t--)
		solve();
	return 0;
}