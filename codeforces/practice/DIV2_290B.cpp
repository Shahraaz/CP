//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
// #define multitest 1
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

int a[4]={1,-1,0,0};
int b[4]={0,0,1,-1};
int n,m;

bool valid(int i,int j)
{
    return (i>=0 && i<n) && (j<m && j>=0);
}
vector<vector<bool>> Vis(100,vector<bool>(100));
vector<string> Mat(100);

void DFS(int i,int j,char c,int pi,int pj)
{
    if(Vis[i][j])
    {
        cout << "Yes";
        exit(0);
    }
    Vis[i][j] = true;
    for(int k=0;k<4;++k)
    {
        int x = i + a[k], y = i+b[k];
        if(Valid(x,y))
        {
            if(x==pi & y==pj) continue;
            if(Mat[x][y]==c)
                DFS(x,y,c,i,j);
        }
    }
}

void solve()
{
    cin > n >> m;
    for(int i=0;i<n;++i)
        cin >> Mat[i];
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            if(!Vis[i][j])
                DFS(i,j,Mat[i][j],i,j);
    cout << "No\n";
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
