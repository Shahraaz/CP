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

vector<vector<int>> Adj(150005);
vector<bool> Vis(150005);
int parent[150005],size[150005];
int lsize[150005];
pair<int,int> Leaf[150005];

void init(int n)
{
	for(int i=1;i<=n;++i)
	{
		size[i] = 1;
		parent[i] = i;
		lsize[i] = i;
		Leaf[i].f = i;
	}
}

int find(int u)
{
  if(parent[u]==u) return u;
  return parent[u] = find(parent[u]);
}

void Dfs(int x,int p)
{
  if(Vis[x]) return;
  Vis[x] = true;
  cout << x << ' ' ;
  for(int y : Adj[x])
    if(y!=p)
      Dfs(y,x);
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n,x,y;
  cin >> n;
  init(n);
  vector<int> Deg(n+1);
  for(int i=1;i<n;++i)
  {
    cin >> x >> y;
    int x1 = x,y1 = y;
    x = find(x);
    y = find(y);
    if(size[y]>=size[x])
    {  
    	swap(x,y);
    	swap(x1,y1);
    }
    size[x]+= size[y];
    parent[y] = x;
    if(lsize[y]==1)
    {
	if(lsize[x]==1)
	{
		Adj[Leaf[x].f].pb(Leaf[y].f);
		Adj[Leaf[y].f].pb(Leaf[x].f);
		Deg[Leaf[y].f]++;
		Deg[Leaf[x].f]++;
		Leaf[x].s = Leaf[y].f;
	}
	else
	{
		Adj[Leaf[x].s].pb(Leaf[y].f);
		Adj[Leaf[y].f].pb(Leaf[x].s);
		Deg[Leaf[y].f]++;
		Deg[Leaf[x].s]++;
		Leaf[x].s = Leaf[y].f;
	}
    }
    else
    {
	if(lsize[x]==1)
	{
		Adj[Leaf[x].f].pb(Leaf[y].f);
		Adj[Leaf[y].f].pb(Leaf[x].f);
		Deg[Leaf[y].f]++;
		Deg[Leaf[x].f]++;
		Leaf[x].s = Leaf[y].s;
	}
	else
	{
		Adj[Leaf[x].s].pb(Leaf[y].f);
		Adj[Leaf[y].f].pb(Leaf[x].s);
		Deg[Leaf[y].f]++;
		Deg[Leaf[x].s]++;
		Leaf[x].s = Leaf[y].s;
	}        
    }
	lsize[x] = lsize[y] = 2;
  }
  int i;
  for(i=1;i<=n;++i)
    if(Deg[i]==1) break;
  Dfs(i,0);
  return 0;
}
