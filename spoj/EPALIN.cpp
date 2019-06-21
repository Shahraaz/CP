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

vector<int> CalculateZ(string s)
{
	int len = s.length();
	vector<int> z(len);
	int l, r;
	l = r = 0;
	for (int i = 1; i < len; ++i)
	{
		if (i > r)
		{
			l = r = i;
			while (r < len && s[r] == s[r - l])
				r++;
			z[i] = r - l;
			r--;
		}
		else
		{
			int k = i - l;
			if(z[k] < r - i + 1)
				z[i] = z[k];
			else
			{
				l = i;
				while (r < len && s[r] == s[r - l])
					r++;
				z[i] = r - l;
				r--;
			}
		}
	}
	return z;
}

void solve(string s)
{
	string rev = s;
	reverse(rev.begin(), rev.end());
	string modif = rev + '$' + s;
	int len = s.length(), modifLen = modif.length();
	vector<int> z = CalculateZ(modif);
	int maxPalinLength = -1;
	for (int i = 0; i < z.size(); ++i)
		if (z[i] && z[i] == modifLen - i)
		{
			maxPalinLength = modifLen - i;
			break;
		}
	if (maxPalinLength == len)
		cout << s << '\n';
	else
	{
		string tans = s.substr(0, len - maxPalinLength);
		reverse(tans.begin(), tans.end());
		cout << s + tans << '\n';
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
	string s;
	while (cin >> s)
		solve(s);
	return 0;
}