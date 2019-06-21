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

vector<int> CalZ(string s)
{
	int n = s.size();
	int l, r;
	vector<int> z(n);
	l = r = 0;
	for (int i = 1; i < n; ++i)
	{
		if (i > r)
		{
			l = r = i;
			while (r < n && s[r] == s[r - l])
				++r;
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
					++r;
				z[i] = r - l;
				r--;
			}
		}
	}
	return z;
}

void solve(string p, string t, int n)
{

	auto z = CalZ(p + '$' + t);
	for(int i=0;i<z.size();++i)
	{
		if(z[i]==p.size())
			cout << i - p.size()-1 << '\n';
	}
	cout << '\n';
}

int main()
{
#ifndef Debug
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#endif
	// int t = 1;
#ifdef multitest
	cin >> t;
#endif
	string p, t;
	int n;
	while (cin >> n >> p >> t)
		solve(p, t, n);
	return 0;
}