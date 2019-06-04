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
typedef pair<ull, ull> pull;
#define f first
#define s second
#define pb push_back
#define mp make_pair
const long long mod = 1000000007;
const long long High = 1e16;

vector<int> Colour;
vector<vector<int>> Adj;
int cnt;

void Dfs(int x, int p, int pr, int pb, int xr, int xb)
{
    cout << x+1 << ' ' << p+1 << ' ' << pr << ' ' << pb << ' ' << xr << ' ' << xb << '\n';
    if (Colour[x] == 1)
    {
        pr++;
        xr--;
    }
    if (Colour[x] == 2)
    {
        pb++;
        xb--;
    }
    if (p != -1)
    {
        if ((pr == 0) || (pb == 0))
        {
            if ((xr == 0) || (xb == 0))
            {
                cnt++;
            }
        }
    }
    for (auto y : Adj[x])
    {
        if (y != p)
            Dfs(y, x, pr, pb, xr, xb);
    }
}

int main()
{
    fast();
    int n;
    cin >> n;
    Adj.resize(n);
    Colour.resize(n);
    int x, y, b, r;
    b = r = 0;
    for (int i = 0; i < n; ++i)
    {
        cin >> Colour[i];
        if (Colour[i] == 1)
            r++;
        if (Colour[i] == 2)
            b++;
    }
    vector<int> Deg(n);
    for (int i = 1; i < n; ++i)
    {
        cin >> x >> y;
        x--;
        y--;
        Adj[x].pb(y);
        Adj[y].pb(x);
        Deg[x]++;
        Deg[y]++;
    }
    int i;
    for (i = 0; i < n; ++i)
        if (Deg[i] == 1)
            break;
    cnt = 0;
    int c = Adj[i][0];
    int pr = 0, pb = 0;
    if (Colour[i] == 1)
    {
        pr++;
        r--;
    }
    if (Colour[i] == 2)
    {
        b--;
        pb++;
    }
    if ((pr == 0) || (pb == 0))
    {
        if ((r == 0) || (b == 0))
        {
            cnt++;
        }
    }
    Dfs(c, i, pr, pb, r, b);
    cout << cnt;
    return 0;
}