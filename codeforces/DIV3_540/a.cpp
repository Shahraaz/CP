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
    int q;
    cin >> q;
    ll n,a,b;
    while(q--)
    {
        cin >> n >> a >> b;
        if(2*a<b)
            cout << n*a << '\n';
        else
        {
            cout << n%2*a + n/2*b << '\n';
        }
        
    }
	return 0;
}
