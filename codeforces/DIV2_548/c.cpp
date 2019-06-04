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

ll power(ll base,ll index)
{
	if(index==0) return 1;
	ll temp = power(base,index/2);
	temp = (temp*temp)%mod;
	if(index&1)
		temp = (temp*base)%mod;
	return temp;
}

void solve()
{
	ll n, k, u, v, x;
	cin >> n >> k;
	vector<vector<ll>> Adj(n);
	vector<bool> Vis(n);
	for(int i=1;i<n;++i)
	{
		cin >> u >> v >> x;
		u--;
		v--;
		if(x==0)
		{
			Vis[u] = Vis[v] = true;
			Adj[u].pb(v);
			Adj[v].pb(u);
		}
	}
	ll ans = (power(n,k) - n + mod)%mod;
	db(ans,n);
	int cnt = 0;
	for(int i=0;i<n;++i)
	{
		if(Vis[i]==true)
		{
			queue<int> Q;
			vector<bool> Visited(n,false);
			Vis[i] = false;
			Visited[i] = true;
			Q.push(i);
			ll cnt = 0;
			while(!Q.empty())
			{
				auto temp = Q.front();
				Q.pop();
				db(temp);
				cnt++;
				for(auto x : Adj[temp])
				{
					db(x);
					if(Visited[x]==false)
					{
						Visited[x] = true;
						Vis[x] = false;
						Q.push(x);
					}
				}
			}
			db(ans,cnt);
			ans = (ans - power(cnt,k) + cnt + mod)%mod;
		}
	}
	cout << ans;
}

main()
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
