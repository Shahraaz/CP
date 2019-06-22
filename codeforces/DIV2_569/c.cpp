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
	int n, x, q;
	cin >> n >> q;
	deque<int> Dq;
	for (int i = 0; i < n; ++i)
	{
		cin >> x;
		Dq.push_back(x);
	}
	vector<pair<int, int>> Answer;
	int start1, end1;
	Answer.pb({0, 0});
	for (int i = 0; i < n; ++i)
	{
		auto a = Dq.front();
		Dq.pop_front();
		auto b = Dq.front();
		Dq.pop_front();
		Answer.pb({a, b});
		Dq.push_front(max(a, b));
		Dq.push_back(min(a, b));
	}
	// cout << is_sorted(Dq.begin() + 1, Dq.end()) << '\n';
	int maxi = Dq.front();
	Dq.pop_front();
	// int idx1 = 0;
	// for (int i = 0; i < n; ++i)
	// {
	// 	auto a = Dq.front();
	// 	Dq.pop_front();
	// 	Answer.pb({maxi, b});
	// 	Dq.push_back(a);
	// 	if()
	// }
	while (q--)
	{
		ll x;
		cin >> x;
		if (x <= (Answer.size() - 1))
			cout << Answer[x].f << ' ' << Answer[x].s << '\n';
		else
		{
			x -= Answer.size() - 1;
			db(x);
			x %= (n - 1);
			db(x);
			x = x - 1;
			x += n - 1;
			x %= (n - 1);
			// x += start1;
			cout << maxi << ' ' << Dq[x] << '\n';
		}
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