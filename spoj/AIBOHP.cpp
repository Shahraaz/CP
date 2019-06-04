//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define Online 1
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

int lcs(string a,string b)
{
    int  n = a.length();
    vector<vector<int>> Dp(n+10,vector<int>(n+10));
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            if(a[i-1]==b[j-1])
                Dp[i][j] = Dp[i-1][j-1] + 1;
            else Dp[i][j] = max(Dp[i-1][j],Dp[i][j-1]);
    return Dp[n][n];
}

void solve()
{
    string str,rev;
    cin >> str;
    rev = str;
    reverse(rev.begin(),rev.end()); 
    cout << str.length() - lcs(str,rev) << '\n';
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