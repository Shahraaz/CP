//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define multitest 1
// #define Debug 1
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

vector<int> calZ(string s)
{
	int n = s.size();
	vector<int> z(n);
	int l, r;
	l = r = 0;
	for (int i = 1; i < n; ++i)
	{
		if (i > r)
		{
			l = r = i;
			while (r < n && s[r] == s[r - l])
				r++;
			z[i] = r - l;
			r--;
		}
		else
		{
			int k = i - l;
			if (z[k] < r - i + 1)
				z[i] = z[k];
			else
			{
				l = i;
				while (r < n && s[r] == s[r - l])
					r++;
				z[i] = r - l;
				r--;
			}
		}
	}
	return z;
}

void solve()
{
	string s;
	cin >> s;
	auto z = calZ(s);
	int max_so_far = 0;
	int n = s.length();
	for (int i = 0; i < n; ++i)
	{
		if ((z[i] == n - i) && (max_so_far >= n - i))
		{
			// db("ok")
			for (int j = 0; j < n - i; ++j)
				cout << s[j];
			return;
		}
		max_so_far = max(max_so_far,z[i]);
	}
	cout << "Just a legend";
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