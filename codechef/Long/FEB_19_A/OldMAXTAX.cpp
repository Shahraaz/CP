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
typedef pair<int, int> pii;
#define f first
#define s second
#define pb push_back
#define mp make_pair
const long long mod = 1000000021;
const long long High = 1e16;
#define int ll
vector<vector<int>> RealG, RevG;
vector<vector<int>> CompG;
vector<bool> Visited;
vector<int> Comp, indegree;
stack<int> St;
int cmpcnt;

void fillorder(int u)
{
    //    cout << "Fill order " << u << '\n';
    Visited[u] = true;
    for (int x : RealG[u])
        if (!Visited[x])
            fillorder(x);
    St.push(u);
}

void Dfs(int u, int c)
{
    Visited[u] = true;
    Comp[u] = c;
    for (int x : RevG[u])
        if (!Visited[x])
            Dfs(x, c);
}

void Getcomp(int n)
{
    //  cout << "Start\n";
    for (int i = 1; i <= n; ++i)
        if (!Visited[i])
            fillorder(i);
    //    cout << "Fillorder\n";
    fill(Visited.begin(), Visited.end(), false);
    cmpcnt = 0;
    //    cout << "Comp order\n";
    while (!St.empty())
    {
        int v = St.top();
        St.pop();
        //cout << v << ' ';
        if (!Visited[v])
            Dfs(v, cmpcnt++);
    }
    //cout << '\n';
}

main()
{
    fast();
    int n, m, u, v, k, t;
    cin >> t;
    while (t--)
    {
        cin >> n >> m >> k;
        vector<int> Cost(n + 1);
        RealG.clear();
        RevG.clear();
        Comp.clear();
        Visited.clear();
        RealG.resize(n + 1, vector<int>(0));
        RevG.resize(n + 1, vector<int>(0));
        Comp.resize(n + 1, -1);
        Visited.resize(n + 1, false);
        for (int i = 1; i <= n; ++i)
            cin >> Cost[i];
        while (m--)
        {
            cin >> u >> v;
            RealG[u].pb(v);
            RevG[v].pb(u);
        }
        Getcomp(n);
        //    cout << "End\n";
        vector<int>  Compsize(cmpcnt);
        vector<vector<int>> CompCostList(cmpcnt);
        indegree.clear();
        CompG.clear();
        indegree.resize(cmpcnt + 1, 0);
	vector< vector<ll> > Compcost(cmpcnt,vector<ll>(k+1,-High)),Externalcost(cmpcnt,vector<ll>(k+1,0));
        CompG.resize(cmpcnt + 1);
        for (int i = 1; i <= n; ++i)
        {
            //cout << "Component " ;
            //cout << i << ' ' << Comp[i] << '\n';
            CompCostList[Comp[i]].pb(Cost[i]);
            Compsize[Comp[i]]++;
            for (int x : RealG[i])
                if (Comp[i] != Comp[x])
                    CompG[Comp[i]].pb(Comp[x]);
        }
        //fill(Visited.begin(), Visited.end(), false);
        queue<int> Q;
        for (int i = 0; i < cmpcnt; ++i)
        {
            sort(CompCostList[i].begin(), CompCostList[i].end());
			int j = 0,curr = -1, currcnt = 0;
			//cout << "Compcost[" << i << "][j] = ";
			for(j=0;j<Compsize[i];++j)
			{
				if(j > k)
					break;
				if(curr == CompCostList[i][j])
				{
					Compcost[i][j] = Compcost[i][j-1];			
					currcnt++;
				}
				else
				{
					curr = CompCostList[i][j];
					if(j==0)
						Compcost[i][j] = ll(curr)*(Compsize[i] - j);
					else Compcost[i][j] = max(Compcost[i][j-1],ll(curr)*(Compsize[i] - j));
					currcnt = 1;
				}
			//	cout << Compcost[i][j] << ' ';
			}
			//cout << '\n';
		sort(CompG[i].begin(),CompG[i].end());
		CompG[i].erase(unique(CompG[i].begin(),CompG[i].end()),CompG[i].end());
            for (vector<int>::iterator it = CompG[i].begin(); it != CompG[i].end(); ++it)
                indegree[*it]++;
        }
        for (int i = 0; i < cmpcnt; ++i)
        {
            if (indegree[i] == 0)
                Q.push(i);
        }
        while (!Q.empty())
        {
            int v = Q.front();
            Q.pop();
            //if (Visited[v])
            //    continue;
            //Visited[v] = true;
	    //cout << v << " Is adj to ";
            for (vector<int>::iterator it = CompG[v].begin(); it != CompG[v].end(); ++it)
            {
                int x = *it;
		//cout << x << ' ';             
		   indegree[x]--;
				for(int i=0;i<=k;++i)
				{
					for(int j=0;j<=k;++j)
					{
						if(j>=Compsize[v])  break;
						if(i+j>k)
							break;
						Externalcost[x][i+j] = max(Externalcost[x][i+j],Externalcost[v][i]+Compcost[v][j]);
					}
				}
                if (indegree[x] == 0)
                    Q.push(x);
            }
		//cout << '\n';
        }
        ll maxi = 0;
        for (int l = 0; l < cmpcnt; ++l)
        {
			//cout << "CompCost[" << l << "] : ";
			for(int i=0;i<=k;++i)
			{
				//cout << Compcost[l][i] << ' ';
				for(int j=0;j<=k;++j)
				{
					if(j>=Compsize[l]) break;
					if(i+j>k)
						break;
					//cout << "Externalcost[" << l << "][" << i << "] + Compcost["<< l << "][" << j << "] : ";
					//cout << Externalcost[l][i] << ' ' << Compcost[l][j] << ' ' << Externalcost[l][i]+Compcost[l][j] <<  '\n';
					maxi = max(maxi,Externalcost[l][i]+Compcost[l][j]);
				}
			}
			//cout << '\n';
        }
		cout << maxi%mod << '\n';
    }
    return 0;
}
