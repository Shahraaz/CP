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
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &x : a)
		cin >> x;
	sort(a.rbegin(), a.rend());
	deque<int> Dq;
	if (a[0] < a[1] + a[2])
	{
		cout << "YES\n";
		Dq.push_front(a[0]);
		bool turn = true;
		for (int i = 1; i < n; ++i)
		{
			if (turn)
				Dq.push_front(a[i]);
			else
				Dq.push_back(a[i]);
			turn = !turn;
		}
		while (!Dq.empty())
		{
			cout << Dq.front() << ' ';
			Dq.pop_front();
		}
	}
	else
		cout << "NO\n";
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