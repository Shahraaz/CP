//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
#define multitest 1
// #define Debug
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
vector<int> A, B;
vector<ll> Sum;

void precompute()
{
    Sum.resize(A.size() + 2);
    Sum[0] = A[0];
    for (int i = 1; i < A.size(); ++i)
        Sum[i] = Sum[i - 1] + A[i];
}

ll getSum(int start, int end)
{
    if(start!=0)    
        return Sum[end] - Sum[start-1];
    return Sum[end];
}

typedef pair<int, ll> pil;
struct DQ
{
    deque<pil> Q;
    int window;
    DQ()
    {
    }
    DQ(int w)
    {
        window = w;
    }
    void insert(ll value, int idx)
    {
        db(value,idx);
        if (Q.empty())
            Q.pb(mp(idx, value));
        else
        {
            while (!Q.empty() && Q.back().s <= value)
                Q.pop_back();
            while (!Q.empty() && Q.front().f <= idx - window)
                Q.pop_front();
            Q.pb(mp(idx, value));
        }
    }
    ll top()
    {
        return Q.front().s;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    A.resize(n);
    B.resize(m);
    for (int i = 0; i < n; ++i)
        cin >> A[i];
    for (int i = 0; i < m; ++i)
        cin >> B[i];
    vector<vector<ll>> DP(m, vector<ll>(n + 1));
    precompute();
    for (int i = 0; i < n; ++i)
        if (i + B[m - 1] <= n)
        {
            DP[m - 1][i] = getSum(i, i + B[m - 1] - 1);
            db(i, i + B[m - 1] - 1,DP[m - 1][i]);
        }
        else
            break;
    for (int i = m - 2; i >= 0; --i)
    {
        db("A");
        DQ Q(B[i] - B[i+1] - 1);
        for (int j = 1; j + B[i+1]-1 < B[i]-1; ++j)
            Q.insert(DP[i+1][j], j);
        db("B");
        ll x = getSum(0, B[i] - 1);
        DP[i][0] = x - Q.top();
        db(i,0,x,Q.top());
        for (int j = 1; j + B[i]-1 < n; ++j)
        {
            Q.insert(DP[i+1][j + B[i]-B[i+1] - 1], j + B[i]-B[i+1] - 1);
            x = getSum(j, j + B[i] - 1);
            DP[i][j] = x - Q.top();
            db(i,j,x,Q.top());
        }
    }
    ll maxi = 0;
    for(int i=0;i<n;++i)
        maxi = max(maxi,DP[0][i]);
    cout << maxi << '\n';
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
