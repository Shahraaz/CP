//Optimise
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
#define mp make_pair
const long long mod = 1000000007;
const long long High = 1e16;

void solve()
{
    int n;
    cin >> n;
    int maxlen = 1;
    vector<ll> V(n), Dp(n);
    Dp[0] = 1;
    for (int i = 0; i < n; ++i)
        cin >> V[i];
    for (int i = n - 1; i >= 0; --i)
    {
        if (i != (n - 1) && (V[i] * V[i + 1] < 0))
            Dp[i] = Dp[i + 1] + 1;
        else
            Dp[i] = 1;
    }
    for (int i = 0; i < n; ++i)
        cout << Dp[i] << ' ';
    cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    int t = 1;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
