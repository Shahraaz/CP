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

void solve()
{
	int n, k;
	cin >> n >> k;
	string s;
	cin >> s;
	int ans = 0;
	queue<string> Q;
	set<string> st;
	Q.push(s);
	st.insert(s);
	while (!Q.empty() && st.size() < k)
	{
		auto v = Q.front();
		Q.pop();
		for (int i = 0; i < v.size(); ++i)
		{
			string nv = v;
			nv.erase(i, 1);
			if (!st.count(nv) && (st.size() + 1 <= k))
			{
				Q.push(nv);
				st.insert(nv);
				ans += n - nv.size();
				db(nv,ans);
			}
		}
	}
	if (st.size() < k)
		cout << -1 << '\n';
	else
		cout << ans << '\n';
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