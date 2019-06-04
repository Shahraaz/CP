//Optimise
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
#define f first
#define s second
#define pb push_back
#define mp make_pair
const long long mod = 1000000007;
const long long High = 1e16;
int a[4] = {1,-1,0,0};
int b[4] = {0,0,1,-1};

ll dist(ll x1,ll y1,ll x2,ll y2)
{
  return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2); 
}

int main()
{
  // ios_base::sync_with_stdio(0);
  // cin.tie(0);
  int n,r1,c1,r2,c2;
  cin >> n;
  cin >> r1 >> c1;
  cin >> r2 >> c2;
  r1--;
  c1--;
  r2--;
  c2--;
  vector<string> Vect(n);
  for(int i=0;i<n;++i)
    cin >> Vect[i];
  vector<vector<ll>> Vis(n,vector<ll>(n,High));
  queue<pair<pii,int>> Q;
  Q.push(mp(mp(r1,c1),0));
  Vis[r1][c1] = 0;
  vector<pair<int,int>> C;
  while(!Q.empty())
  {
    auto temp = Q.front();
    Q.pop();
    if(Vis[temp.f.f][temp.f.s] < temp.s) continue;
    // cout << temp.f.f << ' ' << temp.f.s << '\n';
    C.pb(mp(temp.f.f,temp.f.s));
    Vis[temp.f.f][temp.f.s] = temp.s;
    for(int i=0;i<4;++i)
    {
      int x = temp.f.f + a[i],y = temp.f.s + b[i];
      if(x>=0 && x<n)
        if(y>=0 && y<n)
        {
          if(temp.s+1 < Vis[x][y] && Vect[x][y]=='0')
          {
            Vis[x][y] = temp.s + 1;
            Q.push(mp(mp(x,y),temp.s + 1));
          }
        } 
    }
  }
  // cout << "C1 done\n";
  vector<pair<int,int>> C2;
  vector<vector<ll>> Vis2(n,vector<ll>(n,High));
  Q.push(mp(mp(r2,c2),0));
  Vis2[r2][c2] = 0;
  while(!Q.empty())
  {
    auto temp = Q.front();
    Q.pop();
    if(Vis2[temp.f.f][temp.f.s] < temp.s) continue;
    // cout << temp.f.f << ' ' << temp.f.s << '\n';
    C2.pb(mp(temp.f.f,temp.f.s));
    Vis2[temp.f.f][temp.f.s] = temp.s;
    for(int i=0;i<4;++i)
    {
      int x = temp.f.f + a[i],y = temp.f.s + b[i];
      if(x>=0 && x<n)
        if(y>=0 && y<n)
        {
          if(temp.s+1 < Vis2[x][y] && Vect[x][y]=='0')
          {
            Vis2[x][y] = temp.s + 1;
            Q.push(mp(mp(x,y),temp.s + 1));
          }
        } 
    }
  }
  // cout << "C2 Done\n";
  ll ans = High;
  for(int i=0;i<C.size();++i)
    for(int j=0;j<C2.size();++j)
    {
      ans = min(ans,dist(C[i].f,C[i].s,C2[j].f,C2[j].s));
    }
    cout << ans ;
  return 0;
}
