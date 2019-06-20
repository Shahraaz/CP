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
	int n;
	cin >> n;
	vector<int> a(n), DpL(n), DpR(n);
	for (auto &x : a)
		cin >> x;
	DpL[0] = 1;
	for (int i = 1; i < n; ++i)
	{
		if (a[i] > a[i - 1])
			DpL[i] = DpL[i - 1] + 1;
		else
			DpL[i] = 1;
	}
	DpR[n - 1] = 1;
	for (int i = n - 2; i >= 0; --i)
	{
		if (a[i] < a[i + 1])
			DpR[i] = DpR[i + 1] + 1;
		else
			DpR[i] = 1;
	}
	int sum = 0;
	for (int i = 0; i < n; ++i)
	{
		sum = sum < DpL[i] ? DpL[i] : sum;
		sum = sum < DpR[i] ? DpR[i] : sum;
		if (i != 0 && a[i] <= a[i - 1])
			sum = max(sum, (DpL[i - 1] + 1));
		if (i != n - 1 && a[i] >= a[i + 1])
			sum = max(sum, (DpR[i + 1] + 1));
		if (i != 0 && i != (n - 1) && a[i + 1] - a[i - 1] >= 2)
			sum = max(sum, DpL[i - 1] + DpR[i + 1] + 1);
	}
	cout << sum << '\n';
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