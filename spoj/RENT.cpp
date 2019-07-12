//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
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

using ll = long long;
#define f first
#define s second
#define pb push_back
const long long mod = 1000000007;
auto TimeStart = chrono::steady_clock::now();

const int nax = 10000 + 10;
struct Interval
{
	int start, End, profit;
	Interval(int start = 0, int End = 0, int profit = 0) : start(start), End(End), profit(profit) {}
	bool operator<(const Interval &a) const
	{
		if (start == a.start)
		{
			if (End == a.End)
				return profit < a.profit;
			return End < a.End;
		}
		return start < a.start;
	}
};
vector<Interval> Intervals;
vector<int> dp(nax);
int n, st, d, p;

void solve()
{
	cin >> n;
	Intervals.clear();
	Intervals.resize(n);
	for (int i = 0; i < n; ++i)
	{
		dp[i] = 0;
		cin >> st >> d >> p;
		Intervals[i] = Interval(st, st + d, p);
	}
	sort(Intervals.begin(), Intervals.end());
#ifdef Debug
	for (int i = 0; i < n; ++i)
		db(Intervals[i].start, Intervals[i].End, Intervals[i].profit);
#endif
	for (int i = n - 1; i >= 0; --i)
	{
		auto up = lower_bound(Intervals.begin() + i, Intervals.end(), Interval(Intervals[i].End, Intervals[i].End, 0)) - Intervals.begin();
		db(up);
		if (i != n - 1)
			dp[i] = max(dp[i], dp[i + 1]);
		if (up == n)
			dp[i] = max(dp[i], Intervals[i].profit);
		else
			dp[i] = max(dp[i], Intervals[i].profit + dp[up]);
	}
	cout << dp[0] << '\n';
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
#ifdef TIME
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}