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
int n;
vector<int> V;
string str;

int DP_Table[1005][11][11];
vector<int> print(1005);

int DP(int i,int diff, int last,int m)
{
    if(i>0 && diff<=0 ) return 0;
    if(i==m)
    {
        cout << "YES\n";
        for(int i=0;i<m;++i)
            cout << print[i] << ' ';
        return 1;
    }
    if(DP_Table[i][diff][last]) return 0;
    DP_Table[i][diff][last] = 1;
    for(auto x : V)
        if(x!=last)
        {
            print[i] = x;
            if(DP(i+1,x - diff,x,m))
                return 1;
        }
    return 0;
}

void solve()
{
    cin >> str >> n;
    for (int i = 0; i < str.length(); ++i)
        if (str[i] == '1')
            V.pb(i + 1);
    if(!DP(0,0,0,n)) cout << "NO";
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
