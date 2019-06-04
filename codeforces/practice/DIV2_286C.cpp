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

int n, d;
vector<int> V(30005);
vector<vector<int>> DP_Table(30005, vector<int>(1600, -1));
int rang = 0;

int Brute_Force(int i, int d)
{
    if (i > rang)
        return 0;
    int ans = V[i];
    if (d > 1)
        ans = max(ans, V[i] + Brute_Force(i + d - 1, d - 1));
    ans = max(ans, V[i] + Brute_Force(i + d, d));
    ans = max(ans, V[i] + Brute_Force(i + d + 1, d + 1));
    // db(i,d,ans);
    return ans;
}

int DP(int i, int d)
{
    // db(i,d);
    if (i > rang)
        return 0;
    if (d >= 1500)
        return Brute_Force(i, d);
    int &ans = DP_Table[i][d];
    if (ans != -1)
        return ans;
    ans = V[i];
    if (d > 1)
        ans = max(ans, V[i] + DP(i + d - 1, d - 1));
    ans = max(ans, V[i] + DP(i + d, d));
    ans = max(ans, V[i] + DP(i + d + 1, d + 1));
    return ans;
}

void solve()
{
    cin >> n >> d;
    int u;
    for (int i = 0; i < n; ++i)
    {
        cin >> u;
        V[u]++;
        rang = max(rang, u);
    }
    cout << DP(d, d);
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
