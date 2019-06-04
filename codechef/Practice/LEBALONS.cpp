//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
#define multitest 1
// #define Debug
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

ll Power(ll base,int index)
{ 
	if(index==0) return 1 ;
	ll temp = Power(base,index/2);
	temp *= temp;
	if(index&1)temp *= base;
	return temp;
}

void solve()
{
	int n,m,c,p;
	cin >> n >> m;
	vector<int> color(41),cost(41);
	vector<vector<ll>> Dp(41,vector<ll>(41)),Dp2(41,vector<ll>(41));
	for(int i=0;i<n;++i)
	{
		cin >> c >> p;
		cost[c] += p;
		color[c]++;
	}
	Dp[0][0] = 1;
	for(int i=1;i<=40;++i)
		Dp[i][0] = 1;
	for(int i=1;i<=40;++i)
		for(int j=1;j<=40;++j)
		{	Dp[i][j] = Dp[i-1][j] + Dp[i-1][j-1]*(Power(2,color[i])-1);
			db(i,j,Dp[i][j]);		
		}
	for(int i=1;i<=40;++i)
		for(int j=1;j<=40;++j)
			Dp2[i][j] = Dp2[i-1][j] + (Dp2[i-1][j-1])*(Power(2,color[i])-1) + Dp[i-1][j-1]*cost[i]*Power(2,color[i]-1);
	ld num , den;
	num = den = 0;
	for(int i=m;i<=40;++i)
	{
		num += Dp2[40][i];
		den += Dp[40][i];
	}
	db(num,den);
	cout << setprecision(12) << fixed << (ld)num/den << '\n';
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
