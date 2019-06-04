//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
#define multitest 1
typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
#define mp make_pair
const long long mod = 1000000007;
const long long High = 1e16;
void ControlIO();

ll gcd(ll a, ll b)
{
    return b == 0 ? a : gcd(b, a % b);
}

void solve()
{
    ll n, x;
    cin >> n;
    map<ll, ll> Dp;
    ll ans = 0;
    while (n--)
    {
        cin >> x;
        queue<pair<ll, ll>> Buffer;
        for (auto it = Dp.begin(); it != Dp.end(); ++it)
        {
            ll temp = gcd(it->f, x);
            Buffer.push(mp(temp,it->s));
        }
        Dp[x]++;
        while(!Buffer.empty())
        {
            auto temp = Buffer.front();
            Buffer.pop();
            Dp[temp.f] += temp.s;
        }
    }
    cout << Dp[1] << '\n';
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