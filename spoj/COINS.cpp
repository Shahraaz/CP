//Optimise
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define Online 1
// #define multitest 1
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
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1> void ZZ(const char* name, Arg1&& arg1){std::cerr << name << " = " << arg1 << endl;}
template <typename Arg1, typename... Args>void ZZ(const char* names, Arg1&& arg1, Args&&... args)
{
	const char* comma = strchr(names + 1, ',');
	std::cerr.write(names, comma - names) << " = " << arg1;
	ZZ(comma, args...);
}

map<int,int> Dp;

int solve(int n)
{
	if(Dp.find(n)!=Dp.end())
			return Dp[n];
	int k = Dp[n] = max(n,solve(n/2)+solve(n/3)+solve(n/4));
	return k;
}

main()
{
  ControlIO();
  int t = 1;
#ifdef multitest
  cin >> t;
#endif
	TimerStart();
	Dp[0] = 0;
	Dp[1] = 1;
	Dp[2] = 2;
	Dp[3] = 3;
	Dp[4] = 4;
	while (cin >> t)
    cout << solve(t) << '\n';
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

void TimerStop() {
	#ifndef Online
		TimeEnd = chrono::steady_clock::now();
		auto ElapsedTime = TimeEnd - TimeStart;
		cout << "\n\nTime elapsed: " << chrono::duration<double>(ElapsedTime).count() << " seconds.\n";
	#endif
}
