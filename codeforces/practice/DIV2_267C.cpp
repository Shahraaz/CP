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
int n, m, k;
vector<int> INPUT;
vector<vector<ll>> DP_Table(5005,vector<ll>(5005,-1));

ll DP(int i, int n, int m, int k)
{
    //cout << i << ' ' << n << ' ' << m << ' ' << k << '\n';
    if(k==0) return 0;
    if(i >= n) 
        return -High;
    if(DP_Table[i][k]!=-1)
        return DP_Table[i][k];
    ll temp = 0;
    ll maxi = DP(i+1,n,m,k);
    for(int j=0;j<m;++j)
    {
        if(i+j >= n) break;
        temp += INPUT[i+j];
        maxi = max(maxi,temp+DP(i+j+1,n,m,k-1));
    }
    return DP_Table[i][k] = maxi;
}

void solve()
{
    cin >> n >> m >> k;
    INPUT.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> INPUT[i];
    cout << DP(0, n, m, k);
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
