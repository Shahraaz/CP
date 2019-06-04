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
    int x1, y1, x2, y2, n;
    cin >> x1 >> y1 >> x2 >> y2 >> n;
    string str;
    cin >> str;
    if (x1 == x2 && y1 == y2)
    {
        cout << 0;
        return 0;
    }
    int U, D, L, R;
    U = D = L = R = 0;
    for (int i = 0; i < n; ++i)
    {
        if (str[i] == 'U')
            U++;
        else if (str[i] == 'D')
            D++;
        else if (str[i] == 'R')
            R++;
        else if (str[i] == 'L')
            L++;
    }
    if(U==n)
    {
        if(x2<x1)
        {
            cout << -1;
            return 0;
        }
    }
    if(D==n)
    {
        if(x2>x1)
        {
            cout << -1;
            return 0;
        }
    }
    if(R==n)
    {
        if(y2<y1)
        {
            cout << -1;
            return 0;
        }
    }
    if(L==n)
    {
        if(y2>y1)
        {
            cout << -1;
            return 0;
        }
    }
    int Ureq = x2 - x1,Rreq = y2 - y1;
    int PUreq = x2 - x1,PRreq = y2 - y1;
    ll cycle = 0,cU = (U-D),cR = (R-L);
    for(int i=0;i<n;++i)
    {
        if(str[i]=='U') Ureq--;
        else if(str[i]=='D') Ureq++;
        else if(str[i]=='R') Rreq--;
        else if(str[i]=='L') Rreq++; 
        if(abs(Ureq) + abs(Rreq) < cycle*n + (i+1) )
        {
            cout << cycle*n + (i+1) << '\n';
            return 0;
        }
        cout << abs(Ureq) << ' ' << abs(Rreq) << ' ' <<  cycle*n + (i+1) << '\n';
        cout << Ureq << ' ' << Rreq << ' ' << i+1 << ' ' << cycle << '\n';
        if(i==(n-1))
        {
            i  = -1;
            cycle++;
            // if(PUreq - Ureq > 0 )
            // {
            //     cout << -1;
            //     return 0;
            // }
            // if(PRreq - Rreq > 0 )
            // {
            //     cout << -1;
            //     return 0;
            // }
            // if( PUreq == Ureq  && PRreq == Rreq)
            // {
            //     cout << -1;
            //     return 0;
            // }
        }
    }
    return 0;
}