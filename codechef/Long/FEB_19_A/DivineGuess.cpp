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

ull inv[60004];
void init()
{
	inv[0] = 1;
	inv[1] = 1;
	for(int i=2;i<=60000;++i)
		inv[i] = (inv[mod%i]*(mod - mod/i))%mod;		
}

ull po(ull base,ull index)
{
    if(index==0)    return 1;
    ull temp = po(base,index/2);
    temp = (temp*temp)%mod;
    if(index&1) temp = (temp*base)%mod;
    return temp;
}
ull solve(ull n,ull k,ull m)
{
    if(m&1)
    {
        ull temp = ((n-1)*inv[n])%mod;
        return (1+mod-po(temp,m/2+1))%mod;
    }
    else
    {
        ull temp = solve(n,k,m-1);
        ull temp2 = (po(((n-1)*inv[n])%mod,m/2)*inv[n+k])%mod;
        return (temp+temp2)%mod; 
    }   
}

int main()
{
    fast();
    init();
    int t;
    ull n,m,k;
    cin >> t;
    while(t--)
    {
        cin >> n >> k >> m;
        // cout << "n = " << n << " m = " << m << " k = " << k <<'\n';  
        cout << solve(n,k,m) << '\n';
    }
	return 0;
}