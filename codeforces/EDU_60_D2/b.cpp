//Optimise
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define fast()                  \
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

int main()
{
    fast();
    ll n,m,k;
    cin >> n >> m >> k;
    vector<ll> Vect(n);
    for(int i=0;i<n;++i)
        cin >> Vect[i];
    sort(Vect.begin(),Vect.end());
    ll maxi = Vect[n-1],maxii=Vect[n-2];
    ull ans = 0;
    int t = 0;
    ll ans1 = maxi*k + maxii;
    ans = ans1*(m/(k+1));
    m%=(k+1);
    ans += maxi*m;
    cout << ans;
	return 0;
}