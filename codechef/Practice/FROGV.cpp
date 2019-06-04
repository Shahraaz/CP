//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define Offline 1
// #define multitest 1
typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
#define mp make_pair
const long long mod = 1000000007;
const long long High = 1e16;
void ControlIO();

void solve()
{
    int n, k, p;
    cin >> n >> k >> p;
    vector<pair<int, int>> V(n);
    vector<int> Dp(n + 1);
    for (int i = 0; i < n; ++i)
    {
        cin >> V[i].f;
        V[i].s = i + 1;
    }
    sort(V.begin(),V.end(),greater<pair<int,int>>());
    Dp[V[0].s] = V[0].f + k;
    for(int i=1;i<n;++i)
    {
        if(V[i-1].f - V[i].f <= k)
            Dp[V[i].s] = Dp[V[i-1].s];
        else Dp[V[i].s] = V[i].f + k;
    }
    int x,y;
    while(p--)
    {
        cin >> x >> y;
        if(Dp[x]==Dp[y])
            cout << "Yes\n";
        else cout << "No\n";
    }
}

int main()
{
    ControlIO();
    int t = 1;
#ifdef multitest
    cin >> t;
#endif
    while (t--)
        solve();
    return 0;
}

void ControlIO()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#ifdef Offline
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}