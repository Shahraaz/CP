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

vector<string> Picture;
int n, m, x, y;
vector<ll> extraNeededToFill;
ll Dp[1002][1001][2];

ll Dp_Com(int colindex, int prevcoloured, bool atLeastOneBar)
{
    if (colindex == m)
    {
        if (prevcoloured == 0)
        {
            if (atLeastOneBar)
                return 0;
            return 1e15;
        }
        if ((x <= prevcoloured) && (prevcoloured <= y))
            return 0;
        return 1e15;
    }
    if (prevcoloured > y)
        return 1e15;
    ll &ans = Dp[colindex][prevcoloured][atLeastOneBar];
    if (ans >= 0)
        return ans;
    ans = 1e15;
    // ll t = ans;
    if (prevcoloured == 0)
    {
        ans = min(ans, n - extraNeededToFill[colindex] + Dp_Com(colindex + 1, 0, atLeastOneBar));
        ans = min(ans, extraNeededToFill[colindex] + Dp_Com(colindex + 1, prevcoloured + 1, atLeastOneBar));
    }
    else if (prevcoloured < x)
        ans = min(ans, extraNeededToFill[colindex] + Dp_Com(colindex + 1, prevcoloured + 1, atLeastOneBar));
    else if (prevcoloured < y)
    {
        ans = min(ans, extraNeededToFill[colindex] + Dp_Com(colindex + 1, prevcoloured + 1, true));
        ans = min(ans, n - extraNeededToFill[colindex] + Dp_Com(colindex + 1, 0, true));
        // t = ans;
    } // db("Coloring", colindex, prevcoloured, extraNeededToFill[colindex] + Dp_Com(colindex + 1, prevcoloured + 1));
    else if(prevcoloured==y)
        ans = min(ans, n - extraNeededToFill[colindex] + Dp_Com(colindex + 1, 0, true));
    
    // if (ans < t)
    //     db(colindex, "Coloured");
    // else
    //     db(colindex, "Uncolored");
    // db("NotColoring", colindex, prevcoloured, n - extraNeededToFill[colindex] + Dp_Com(colindex + 1, 0));
    return ans;
}

void solve()
{
    memset(Dp, -1, sizeof(Dp));
    cin >> n >> m >> x >> y;
    Picture.resize(n);
    extraNeededToFill.resize(m);
    int i = 0;
    for (auto &x : Picture)
    {
        cin >> x;
        for (int j = 0; j < m; ++j)
            extraNeededToFill[j] += (x[j] == '.');
    }
    cout << Dp_Com(0, 0, 0);
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
