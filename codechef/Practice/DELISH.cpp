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
    vector<ll> Vect(n + 1), Lmin(n + 1), Lmax(n + 1), Rmin(n + 1), Rmax(n + 1);
    for (int i = 0; i < n; ++i)
        cin >> Vect[i];
    ll maxi = 0;
    Lmin[0] = Lmax[0] = Vect[0];
    for (int i = 1; i < n; ++i)
    {
        Lmin[i] = min(Lmin[i - 1] + Vect[i], Vect[i]);
        Lmax[i] = max(Lmax[i - 1] + Vect[i], Vect[i]);
    }
    Rmin[n - 1] = Rmax[n - 1] = Vect[n - 1];
    for (int i = n - 2; i >= 0; --i)
    {
        Rmin[i] = min(Rmin[i + 1] + Vect[i], Vect[i]);
        Rmax[i] = max(Rmax[i + 1] + Vect[i], Vect[i]);
    }
    for(int i=0;i<n-1;++i)
    {
        maxi = max(maxi,abs(Lmin[i] - Rmax[i+1]));
        maxi = max(maxi,abs(Lmax[i] - Rmin[i+1]));
    }
    cout << maxi << '\n';
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
