//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
#define multitest 1
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
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__);
template <typename Arg1> void ZZ(const char* name, Arg1&& arg1){std::cerr << name << " = " << arg1 << endl;}
template <typename Arg1, typename... Args>void ZZ(const char* names, Arg1&& arg1, Args&&... args)
{
	const char* comma = strchr(names + 1, ',');
	std::cerr.write(names, comma - names) << " = " << arg1;
	ZZ(comma, args...);
}
typedef pair<int,int> pii;

void solve()
{
	int n,m;
	cin >> n >> m;
	vector<string> Board(105);
	for(int i=0;i<n;++i)
	{
		cin >> Board[i];
		Board[i] += "0";
	}
	Board[n].resize(m+1,'0');
	vector<vector<set<pii>>> Dp(105,vector<set<pii>>(105));
	if((Board[0][0]=='1'))Dp[0][0].insert(mp(0,0));
	if((Board[1][0]=='1'))Dp[0][0].insert(mp(1,0));
	if((Board[0][1]=='1'))Dp[0][0].insert(mp(0,1));	
	for(int i=1;i<m;++i)
	{
		Dp[0][i] = Dp[0][i-1];
		if((Board[0][i+1]=='1'))Dp[0][i].insert(mp(0,i+1));
		if((Board[1][i]=='1'))Dp[0][i].insert(mp(1,i));
	}
	for(int i=1;i<n;++i)
	{
		Dp[i][0] = Dp[i-1][0];
		if((Board[i+1][0]=='1'))Dp[i][0].insert(mp(i+1,0));
		if((Board[i][1]=='1'))Dp[i][0].insert(mp(i,1));
	}
	for(int i=1;i<n;++i)
		for(int j=1;j<m;++j)
		{
			auto down = Dp[i][j-1];
			if((Board[i-1][j]=='1'))down.insert(mp(i-1,j));
			auto left = Dp[i-1][j];
			if((Board[i][j-1]=='1'))down.insert(mp(i,j-1));
			if(down.size()<left.size())
				Dp[i][j] = down;
			else
				Dp[i][j] = left;
			if((Board[i+1][j]=='1'))Dp[i][j].insert(mp(i+1,j));
			if((Board[i][j+1]=='1'))Dp[i][j].insert(mp(i,j+1));				
		}
//	for(auto x:Dp[n-1][m-1])
//		db(x.f,x.s);
//	db("\n");
	cout << Dp[n-1][m-1].size() << '\n';
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
