//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
#define multitest 1
#define Debug
typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
#define mp make_pair
const long long mod = 1000000007;
const long long High = 1e16;
void ControlIO();
void TimerStart();
void TimerStop();
#ifdef Debug
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__)
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

void solve()
{
	int n;
	cin >> n;
	vector<int> H(n+1),K(n+1);
	for(int i=0;i<n;++i)
		cin >> H[i+1];
	for(int i=0;i<n;++i)
		cin >> K[i+1];
	vector<vector<int>> Dp(1001,vector<int>(1001));
	// DP[i][j] = minimum number of fills needed to make fuel from 0 through j litres using only 1 to i petrol pumps 
	fill(Dp[0].begin(),Dp[0].end(),mod);
	//it is impossible to make change without using any coins
	Dp[0][0] = 0;
	//0 , 0 base case
	for(int i=1;i<=n;++i)
		for(int j=0;j<=1000;++j)
		{
			Dp[i][j] = Dp[i-1][j];
			if(K[i]<=j)
				Dp[i][j] = min(Dp[i][j], 1 + Dp[i][j-K[i]]);
		}
	int res = 0;
	for(int i=1;i<=n;++i)
		res += Dp[n][2*H[i]];
	cout << res << '\n';
}

int main()
{
	ControlIO();
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	TimerStart();
	while (t--)
		solve();
	TimerStop();
	return 0;
}

void ControlIO()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#ifndef Online
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
}

auto TimeStart = chrono::steady_clock::now();
auto TimeEnd = chrono::steady_clock::now();

void TimerStart()
{
#ifndef Online
	TimeStart = chrono::steady_clock::now();
#endif
}

void TimerStop()
{
#ifndef Online
	TimeEnd = chrono::steady_clock::now();
	auto ElapsedTime = TimeEnd - TimeStart;
	cout << "\n\nTime elapsed: " << chrono::duration<double>(ElapsedTime).count() << " seconds.\n";
#endif
}
