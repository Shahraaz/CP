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

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n,x;
  cin >> n;
  vector<int> F(n+1),S(n+1); 
  for(int i=1;i<=2*n;++i)
  {
    cin >> x;
    if(F[x]==0)
      F[x] = i;
    else S[x] = i; 
  }
  int p1 , p2;
  p1 = p2 = 1;
  ll ans = 0;
  for(int i=1;i<=n;++i)
  {
    ans += min(abs(p1-F[i])+abs(p2-S[i]),abs(p2-F[i])+abs(p1-S[i]));
    p1 = F[i];
    p2 = S[i];
  }
  cout << ans;
  return 0;
}
