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
  int n;
  cin >> n;
  int n1 = ceil(n/2.0);
  vector<int> Vect(n);
  int pos,neg,zero;
  pos = neg = zero = 0;
  for(int i=0;i<n;++i)
  {
    cin >> Vect[i];
    if(Vect[i]==0) zero++;
    else if(Vect[i]>0) pos++;
    else neg++;
  }
  if(pos>=n1) cout << 1;
  else   if(neg>=n1) cout << -1;
  else cout << 0;
  return 0;
}
