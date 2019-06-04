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
int n;
vector<int> C(105),P(105),T(105);
map<pii,int> Dp;

int KnapSack(int start,int w)
{
	if(w<0) return -mod;
	if(start==n) return 0;
	if(Dp.find(mp(start,w))!=Dp.end())
		return Dp[mp(start,w)];	
	int k =  max(C[start]*P[start] + KnapSack(start+1,w-T[start]),KnapSack(start+1,w));
	//db(start,w,k);
	return Dp[mp(start,w)] = k;
}

void solve()
{
	Dp.clear();
	int w;
	cin >> n >> w;
	for(int i=0;i<n;++i)
		cin >> C[i] >> P[i] >> T[i];
	cout << KnapSack(0,w) << '\n';
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
