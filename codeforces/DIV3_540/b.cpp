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
    int n, i;
    cin >> n;
    vector<int> Vect(n);
    for (int i = 0; i < n; ++i)
        cin >> Vect[i];
    int Evensum, Oddsum, lo, le;
    lo = le = 0;
    Evensum = Oddsum = 0;
    for (int i = 0; i < n; ++i)
        if (i & 1)
            Evensum += Vect[i];
        else
            Oddsum += Vect[i];
    int cnt = 0;

    for (int i = 0; i < n; ++i)
    {
        if ((i & 1))
        {
            Evensum -= Vect[i];
        }
        else
        {
            Oddsum -= Vect[i];
        }
        swap(Oddsum, Evensum);
        // cout << Evensum + le << ' ' << Oddsum + lo << '\n';
        if ((Evensum + le) == (Oddsum + lo))
            cnt++;
        swap(Oddsum, Evensum);
        if ((i & 1))
        {
            le += Vect[i];
        }
        else
        {
            lo += Vect[i];
        }
    }
    cout << cnt;
    return 0;
}
