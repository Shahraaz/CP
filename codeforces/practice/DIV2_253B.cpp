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

int Val(string str, int idx, string s)
{
    int i = 0, n = str.length();
    int ans = 0;
    while (idx < n)
    {
        if (str[idx] == '*' || str[idx] == s[i])
        {
            i++;
            if (i == s.length())
                return 2*i;
        }
        else
            break;
        idx++;
    }
    return 0;
}

void solve()
{
    string str;
    cin >> str;
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i)
        str.pb('*');
    // cout << str;
    int maxi = 1;
    for (int i = 0; i < str.size(); ++i)
    {
        string s = "";
        s.pb(str[i]);
        maxi = max(maxi, Val(str, i+1, s));
        for (int j = i + 1; j < str.size(); ++j)
        {
            s += str[j];
            maxi = max(maxi, Val(str, j+1, s));
        }
    }
    cout << maxi;
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
