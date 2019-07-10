//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define multitest 1
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
auto TimeStart = chrono::steady_clock::now();

const int nax = 1e5 + 10;
int t[nax], n;
ll dp[nax + 10];

template <typename T>
void chkmin(T &a, const T b)
{
	a = min(a, b);
}

void solve()
{
	cin >> n;
	vector<int> t(n);
	for (int i = 0; i < n; ++i)
		cin >> t[i];
	dp[0] = 0;
	for (int i = 0; i < n; ++i)
	{
		dp[i + 1] = dp[i] + 20;
		chkmin(dp[i + 1], dp[upper_bound(t.begin(), t.end(), t[i] - 90) - t.begin()] + 50);
		chkmin(dp[i + 1], dp[upper_bound(t.begin(), t.end(), t[i] - 1440) - t.begin()] + 120);
		cout << dp[i + 1] - dp[i] << '\n';
	}
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
	cout << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}