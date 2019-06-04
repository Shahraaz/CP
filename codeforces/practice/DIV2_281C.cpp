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

ll Score(vector<ll> V, ll d, ll s)
{
    ll t = (upper_bound(V.begin(), V.end(), d) - V.begin());
    return 2 * t + 3 * (s - t);
}

void solve()
{
    int n, m;
    cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; ++i)
        cin > A[i];
    cin >> m;
    vector<int> B(m);
    for (int i = 0; i < m; ++i)
        cin > B[i];
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    ll low = 0, high = 1e10;
    ll sca = Score(A, mid, high), scb = Score(B, mid, m);
    ll diff = sca - scb;
    while (low <= high)
    {
        ll mid = (low + high) / 2;
        ll a = Score(A, mid, n);
        ll b = Score(B, mid, m);
        if (a - b >= diff)
        {
            diff = a - b;
            if (a - b == diff)
                if (a > sca)
                {
                    sca = a;
                    scb = a;
                }
            high = mid-1;
        }
        else low = mid+1;
    }
    cout << sca << ':' << scb ;
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
