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

int gcd(int a,int b)
{
    return b==0 ? a : gcd(b,a%b);
}

void solve()
{
    int n,x,gcdi;
    cin >> n;
    cin >> x;
    gcdi = x;
    n--;
    while(n--)
    {
        cin >> x ;
        gcdi = gcd(gcdi,x);
    }
    cout << gcdi << '\n';
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