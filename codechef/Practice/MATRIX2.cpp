//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
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
    int n, m,j;
    cin >> n >> m;
    vector<string> Matrix(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> Matrix[i];
    vector<int> c(m+1);
    ll ans = 0;
    for(int i=n;i;i--)
    {
        for(j=0;j<m;++j)
            if(Matrix[i][j]=='1')
                ++c[j];
            else c[j] = 0;
        int last = 0;
        for(j=0;j<m;++j)
            ans += (last = min(last+1,c[j]));
    }
    cout << ans;
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
#ifndef Online
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}