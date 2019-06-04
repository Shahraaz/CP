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

int main()
{
    fast();
    int n;
    cin >> n;
    vector<ld> Vect(n);
    ld maxi = 0;
    for (int i = 0; i < n; ++i)
    {
        cin >> Vect[i];
        maxi = max(maxi, Vect[i]);
    }
    int cnt = 0, curcnt = 0;
    ld curr = -1;
       for (int i = 0; i < n;)
    {
        if (Vect[i] == maxi)
        {
            int C = 0;
            while(i<n && Vect[i]==maxi)
            {
                i++;
                C++;
            }
            cnt = max(cnt,C);
        }
        else
            i++;
    }
    cout << cnt;
    return 0;
}