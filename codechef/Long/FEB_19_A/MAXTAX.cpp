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
vector<vector<int>> CompG, ParG;
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
        vector<int> Compsize(cmpcnt);
        vector<vector<int>> CompCostList(cmpcnt);
        indegree.clear();
        CompG.clear();
        ParG.clear();
        indegree.resize(cmpcnt + 1, 0);
        vector<vector<ll>> Compcost(cmpcnt, vector<ll>(k + 1, -High)), Externalcost(cmpcnt, vector<ll>(k + 1, 0));
        CompG.resize(cmpcnt + 1);
        ParG.resize(cmpcnt + 1);
        for (int i = 1; i <= n; ++i)
        {
            CompCostList[Comp[i]].pb(Cost[i]);
            Compsize[Comp[i]]++;
            for (int x : RealG[i])
                if (Comp[i] != Comp[x])
                {
                    CompG[Comp[i]].pb(Comp[x]);
                    ParG[Comp[x]].pb(Comp[i]);
                }
        }
        //fill(Visited.begin(), Visited.end(), false);
        queue<int> Q;
        for (int i = 0; i < cmpcnt; ++i)
        {
            sort(CompCostList[i].begin(), CompCostList[i].end());
            int j = 0, curr = -1, currcnt = 0;
            for (j = 0; j < Compsize[i]; ++j)
            {
                if (j > k)
                    break;
                if (curr == CompCostList[i][j])
                {
                    Compcost[i][j] = Compcost[i][j - 1];
                    currcnt++;
                }
                else
                {
                    curr = CompCostList[i][j];
                    if (j == 0)
                        Compcost[i][j] = ll(curr) * (Compsize[i] - j);
                    else
                        Compcost[i][j] = max(Compcost[i][j - 1], ll(curr) * (Compsize[i] - j));
                    currcnt = 1;
                }
            }
            sort(CompG[i].begin(), CompG[i].end());
            CompG[i].erase(unique(CompG[i].begin(), CompG[i].end()), CompG[i].end());
            sort(ParG[i].begin(), ParG[i].end());
            ParG[i].erase(unique(ParG[i].begin(), ParG[i].end()), ParG[i].end());
            for (vector<int>::iterator it = CompG[i].begin(); it != CompG[i].end(); ++it)
                indegree[*it]++;
        } /*
	cout << "\nAfter\n";
	for(int i=0;i<cmpcnt;++i)
	{
		cout << i << " Child of ";
		for(int x : CompG[i])
			cout << x << ' ';
		cout << '\n' << i << " Parent of ";
		for(int x : ParG[i])
			cout << x << ' ';
		cout << '\n';
	}
	cout << '\n';*/
        for (int i = 0; i < cmpcnt; ++i)
        {
            if (indegree[i] == 0)
                Q.push(i);
        }
        vector<ll> ParSize(cmpcnt);
        while (!Q.empty())
        {
            int v = Q.front();
            Q.pop();
            vector<ll> Temp(k + 1), Answer(k + 1);
            int Parmax = 0;
            for (int j = 0; j < CompG[v].size(); ++j)
            {
                ll x = CompG[v][j];
                //		cout << x << ' ';
                indegree[x]--;
                if (indegree[x] == 0)
                    Q.push(x);
            }
            //		cout << '\n';
            //	    cout << v << " Is parent of " << ParG[v].size() << ' ';
            for (int j = 0; j < ParG[v].size(); ++j)
            {
                ll x = ParG[v][j];
                //		cout << x << ' ';
                Parmax = max(Parmax, ParSize[x]);
                for (int i = 0; i <= ParSize[x]; ++i)
                    Temp[i] = max(Temp[i], Externalcost[x][i]);
            }
            //		cout << '\n';
            //	    for(int i=0;i<=Parmax;++i)
            //		cout << "Temp[" << i << "] = " << Temp[i] << '\n';
            //	cout << '\n';
            int maxdist = Compsize[v] - 1;
            for (int i = 0; i < Compsize[v]; ++i)
            {
                if (i > k)
                    break;
                Answer[i] = max(Answer[i], Compcost[v][i]);
                for (int j = 0; j <= Parmax; ++j)
                {
                    if (i + j > k)
                        break;
                    maxdist = max(maxdist, i + j);
                    Answer[i + j] = max(Answer[i + j], Temp[j] + Compcost[v][i]);
                }
            }
            //	    cout << "Externalcost[" << v << "] : ";
            maxdist = min(maxdist, k);
            for (int i = 0; i <= maxdist; ++i)
            {
                Externalcost[v][i] = Answer[i];
                //	    	cout << Externalcost[v][i] << ' ';
            }
            ParSize[v] = maxdist;
            //          cout << '\n';
        }
        ll maxi = 0;
        for (int l = 0; l < cmpcnt; ++l)
            //cout << "CompCost[" << l << "] : ";
            for (int i = 0; i <= ParSize[l]; ++i)
                maxi = max(maxi, Externalcost[l][i]);
        //cout << '\n';
        cout << maxi % mod << '\n';
    }
    return 0;
}
