#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);
ofstream fout(getenv("OUTPUT_PATH"));

const int nax = 1e5 + 10;
vector<int> Adj[nax];
long long W[nax], K;
long long dp[nax][210], Previous[210];
using ll = long long;

void dfs(int node, int parent) // solve for the sub tree including the root i.e node
{
	for (int cutCnt = 0; cutCnt <= K; ++cutCnt)
		dp[node][cutCnt] = W[node];
	for (int child : Adj[node])
	{
		if (child == parent)
			continue;
		dfs(child, node);
		for (int i = 0; i <= K; ++i)
		{
			Previous[i] = dp[node][i];
			dp[node][i] = -1e18;
		}
		dp[node][0] = Previous[0] + dp[child][0];
		for (int nodeCutCnt = 0; nodeCutCnt <= K; ++nodeCutCnt)
		{
			dp[node][nodeCutCnt + 1] = max(Previous[nodeCutCnt], dp[node][nodeCutCnt + 1]);
			for (int childCutCnt = 0; childCutCnt + nodeCutCnt <= K; ++childCutCnt)
			{
				dp[node][childCutCnt + nodeCutCnt] = max(dp[node][childCutCnt + nodeCutCnt], Previous[nodeCutCnt] + dp[child][childCutCnt]);
			}
		}
	}
	// cout << node << '\n';
	// for (int cutCnt = 0; cutCnt <= K; ++cutCnt)
	// cout << cutCnt << ' ' << dp[node][cutCnt] << '\n';
	// cout << '\n';
}

ll treePrunning()
{
	int n, u, v;
	cin >> n >> K;
	for (int i = 1; i <= n; ++i)
		cin >> W[i];
	for (int i = 1; i < n; ++i)
	{
		cin >> u >> v;
		Adj[u].push_back(v);
		Adj[v].push_back(u);
	}
	dfs(1, 0);
	return dp[1][K];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	ll result = treePrunning();
	fout << result << "\n";
	// cout << result << '\n';
	fout.close();

	return 0;
}