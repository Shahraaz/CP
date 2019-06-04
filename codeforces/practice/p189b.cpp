//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
// #define multitest 1
// #define Debug
typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
#define mp make_pair
const long long mod = 1000000007;
const long long High = 1e16;
void ControlIO();
void TimerStart();
void TimerStop();
#ifdef Debug
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void ZZ(const char *name, Arg1 &&arg1)
{
	std::cerr << name << " = " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void ZZ(const char *names, Arg1 &&arg1, Args &&... args)
{
	const char *comma = strchr(names + 1, ',');
	std::cerr.write(names, comma - names) << " = " << arg1;
	ZZ(comma, args...);
}
#else
#define db(...)
#endif

typedef pair<int,int> pii; 
void solve()
{
	int q,ch,x,y;
	cin >> q;
	vector<vector<int>> Adj(q+1);
	vector<pii> Nodes;
	int nodescnt = 0;
	for(int i=0;i<q;++i)
	{
		cin >> ch >> x >> y;
		if(ch==1)
		{
			for(int j=0;j<nodescnt;++j)
			{
				int x1 = Nodes[j].f,y1 = Nodes[j].s;
				if((x<x1 && x1<y) || (x<y1 && y1<y))
					Adj[j].pb(nodescnt);
				if((x1<x && x<y1) || (x1<y && y<y1))
					Adj[nodescnt].pb(j);
			}
			nodescnt++;
			Nodes.pb(mp(x,y));
		}
		else
		{
			x--;
			y--;
			vector<bool> Vis(101,false);
			queue<int> Q;
			Q.push(x);
			Vis[x] = true;
			db("BFS Start");
			while(!Q.empty())
			{
				int temp = Q.front();
				db(temp);
				Q.pop();
				for(int t : Adj[temp])
					if(!Vis[t])
					{
						Vis[t] = true;
						Q.push(t);
					}
			}
			if(Vis[y]) cout << "YES\n";
			else cout << "NO\n";
		}
	}
}

int main()
{
	ControlIO();
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	TimerStart();
	while (t--)
		solve();
	TimerStop();
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

auto TimeStart = chrono::steady_clock::now();
auto TimeEnd = chrono::steady_clock::now();

void TimerStart()
{
#ifndef Online
	TimeStart = chrono::steady_clock::now();
#endif
}

void TimerStop()
{
#ifndef Online
	TimeEnd = chrono::steady_clock::now();
	auto ElapsedTime = TimeEnd - TimeStart;
	cout << "\n\nTime elapsed: " << chrono::duration<double>(ElapsedTime).count() << " seconds.\n";
#endif
}
