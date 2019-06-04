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

void solve()
{
    int n, d, x;
    cin >> n;
    queue<int> Q;
    int i = 0;
    vector<int> D(n), X(n);
    vector<pair<int, int>> A;
    while (n--)
    {
        cin >> d >> x;
        if (d == 1)
            Q.push(i);
        D[i] = d;
        X[i] = x;
        i++;
    }
    while (!Q.empty())
    {
        auto u = Q.front();
        Q.pop();
        if(D[u]==0) continue;
        int v = X[u];
        D[v]--;
        D[u]--;
        X[v] ^= u;
        if (D[v] == 1)
            Q.push(v);
        if (u != v)
        {
            if(v<u) swap(u,v);
            A.pb(mp(u, v));
        }
    }
    sort(A.begin(),A.end());
    A.erase(unique(A.begin(),A.end()),A.end());
    cout << A.size() << '\n';
    for (auto x : A)
        cout << x.f << ' ' << x.s << '\n';
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
