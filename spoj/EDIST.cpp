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
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1> void ZZ(const char* name, Arg1&& arg1){std::cerr << name << " = " << arg1 << endl;}
template <typename Arg1, typename... Args>void ZZ(const char* names, Arg1&& arg1, Args&&... args)
{
	const char* comma = strchr(names + 1, ',');
	std::cerr.write(names, comma - names) << " = " << arg1;
	ZZ(comma, args...);
}

string a,b;
vector<vector<int>> DP(2005,vector<int>(2005));
int n,m;

int DP_com(int i,int j)
{
	if(i == n) return  m - j;
	if(j == m) return  n - i;
	if(DP[i][j]>=0) return DP[i][j];
	if(a[i]==b[j])
		DP[i][j] = DP_com(i+1,j+1);
	else 
		DP[i][j] = 1 + min(DP_com(i+1,j+1),min(DP_com(i,j+1),DP_com(i+1,j)));
	//db(i+1,j+1,DP[i][j]);
	return DP[i][j];
}

void solve()
{
	cin >> a >> b ;
	n = a.size();
	m = b.size();
	for(int i=0;i<n;++i)
		fill(DP[i].begin(),DP[i].end(),-1);
	cout << DP_com(0,0) << '\n';
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

void TimerStop() {
	#ifndef Online
		TimeEnd = chrono::steady_clock::now();
		auto ElapsedTime = TimeEnd - TimeStart;
		cout << "\n\nTime elapsed: " << chrono::duration<double>(ElapsedTime).count() << " seconds.\n";
	#endif
}
