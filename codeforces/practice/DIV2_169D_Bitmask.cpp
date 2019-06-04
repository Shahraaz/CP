//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
// #define multitest 1
#define Debug 1
typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
const long long mod = 1000000007;
void ControlIO();
void TimerStart();
void TimerStop();
#ifdef Debug
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__);
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

string a, b;
string toBinaryString(ll n)
{
    string res = "";
    for (int i = 63; i >= 0; --i)
    {
        if (n & (1LL << i))
            res.pb('1');
        else
            res.pb('0');
    }
    return res;
}
ll Dp[65][2][2][2][1];

ll Dp_compute(int p, int l1, int l2, int r1, int r2)
{
    if (p >= 64)
        return 0;
    ll &ans = Dp[p][l1][l2][r1][r2];
    if (ans >= 0)
        return ans;
    ans = 0;
    int mn1 = 0, mx1 = 1;
    if (l1 == 0 && a[p] == '1')
        mn1 = 1;
    if (r1 == 0 && b[p] == '0')
        mx1 = 0;
    int mn2 = 0, mx2 = 1;
    if (l2 == 0 && a[p] == '1')
        mn2 = 1;
    if (r2 == 0 && b[p] == '0')
        mx2 = 0;
    for (int i = mn1; i <= mx1; ++i)
        for (int j = mn2; j <= mx2; ++j)
        {
            ll pres = 0;
            int Xor = i ^ j;
            if (Xor)
                pres = (1LL << (64 - p - 1));
            int newl1 = l1, newl2 = l2, newr1 = r1, newr2 = r2;
            if (i > (a[p] - '0'))
                newl1 = 1;
            if (j > (a[p] - '0'))
                newl2 = 1;
            if (i < (b[p] - '0'))
                newr1 = 1;
            if (j < (b[p] - '0'))
                newr2 = 1;
            ans = max(ans, pres + Dp_compute(p + 1, newl1, newl2, newr1, newr2));
        }
    return ans;
}

void solve()
{
    memset(Dp, -1, sizeof(Dp));
    ll l, r;
    cin >> l >> r;
    // cout << log2(LLONG_MAX) << ' ' << LLONG_MAX/(1e18);
    // ll ans = l ^ r;
    a = toBinaryString(l); 
    b = toBinaryString(r); 
    cout << Dp_compute(0, 0, 0, 0, 0) << '\n';
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