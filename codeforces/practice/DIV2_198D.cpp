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

int lis(vector<int> &a, int n)
{
	set<int> s;
	auto k = s.begin();
	for (int i = 0; i < n; ++i)
	{
		if (s.insert(a[i]).s)
		{
			k = s.find(a[i]);
			k++;
			if (k != s.end())
				s.erase(k);
		}
	}
	return s.size();
}

void solve()
{
	int n;
	cin >> n;
	vector<int> V(n);
	for (auto &x : V)
		cin >> x;
	cout << lis(V, n) << '\n';
	db("ou")
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