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

typedef pair<int,int> pii;
int m,n;
vector<string> Map(205);
map<pair<pii,int>,int> DP;
int righti = 0,lefti = 1;

int Dp_com(int i,int j,int face)
{
	if(i == -1 || j == -1)	return 0;
	if(i==m || j==n)	return 0;
	if(Map[i][j] == '#')	return 0;
	if(DP.find(mp(mp(i,j),face)) != DP.end())
		return DP[mp(mp(i,j),face)];
	int k;	
	if(face==righti)
		k = (Map[i][j]=='T') + max(Dp_com(i,j+1,righti),Dp_com(i+1,j,lefti));
	else
		k = (Map[i][j]=='T') + max(Dp_com(i,j-1,lefti),Dp_com(i+1,j,righti));
	//db(i,j,face,DP[mp(mp(i,j),face)]);
	return DP[mp(mp(i,j),face)] = k;
}

void solve()
{
	DP.clear();
	cin >> m >> n;
	for(int i=0;i<m;++i)
		cin >> Map[i];
	if(Map[0][0] == '#')
		cout << 0 << '\n';
	else cout << Dp_com(0,0,righti) << '\n';		
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
