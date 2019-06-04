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
int n, m, d;
vector<vector<int>> MAT(105,vector<int>(105));


void solve()
{
    cin >> n >> m >> d;
    ll sum = 0;
    int x = -1;
    int mini = mod;
    vector<int> Vect;
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
        {
            cin >> MAT[i][j];
            mini = min(mini,MAT[i][j]);
        }
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
        {
            MAT[i][j] -= mini ;
            if(MAT[i][j]%d!=0)
            {
                cout << -1;
                return;
            }
            Vect.pb(MAT[i][j]/d);
        }
    sort(Vect.begin(),Vect.end());
    int h = Vect[Vect.size()/2];
    ll ans = 0;
    for(auto x : Vect)
        ans += abs(x-h);
    cout << ans;
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
