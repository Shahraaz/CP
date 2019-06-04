//Optimise
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define fast()                    \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
#define f first
#define s second
#define pb push_back
#define mp make_pair
const long long mod = 1000000007;
const long long High = 1e16;

vector<vector<int>> Adj;
int n;

int solve(int src, int k)
{
    queue<pair<pii, int>> Q;
    Q.push(mp(mp(src, -1), 0));
    int D = 0, currdist = 0, prevcnt = n, currcnt = 0;
    while (!Q.empty())
    {
        auto temp = Q.front();
        Q.pop();
        // cout << "Current " << temp.f.f+1 << ' ' << "Parent " << temp.f.s+1 << ' ' << "Dist " << temp.s << '\n';
        if (temp.s == currdist)
            currcnt++;
        else
        {
            prevcnt -= currcnt;
            if (prevcnt < k)
                return currdist;
            currdist++;
            currcnt = 1;
        }
        for (int x : Adj[temp.f.f])
            if (x != temp.f.s)
                Q.push(mp(mp(x, temp.f.f), temp.s + 1));
    }
    return currdist;
}

int main()
{
    fast();
    cin >> n;
    Adj.resize(n);
    vector<int> K(n);
    for (int i = 0; i < n; ++i)
        cin >> K[i];
    int u, v, m = n - 1, k;
    while (m--)
    {
        cin >> u >> v;
        u--;
        v--;
        Adj[u].pb(v);
        Adj[v].pb(u);
    }
    for (int i = 0; i < n; ++i)
        cout << solve(i, K[i])-1 << ' ';
    return 0;
}