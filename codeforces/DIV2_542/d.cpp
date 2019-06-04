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
  int n, m;
  cin >> n >> m;
  vector<vector<int>> Q1(n, vector<int>(n));
  for (int i = 0; i < m; ++i)
  {
    int x, y;
    cin >> x >> y;
    x--;
    y--;
    Q1[x][y]++;
  }
  int m1 = m;
  for (int j1 = 0; j1 < n; ++j1)
  {
    m = m1;
    vector<int> Pick(n);
    vector<vector<int>> Q(n,vector<int>(n));
    for(int i=0;i<n;++i)
      Q[i] = Q1[i];
    int t = 0;
    for (int i = j1; i < n && m; ++i)
    {
      Pick[i]++;
      for (int j = 0; j < i; ++j)
        if (Q[j][i] && Pick[j])
        {
          int temp = min(Q[j][i], Pick[j]);
          Pick[j] -= temp;
          Q[j][i] -= temp;
          m -= temp;
          if (m == 0)
            break;
        }
      t++;
    }
    while (m)
    {
      for (int i = 0; i < n && m; ++i)
      {
        Pick[i]++;
        for (int j = 0; j < n; ++j)
          if (Q[j][i] && Pick[j])
          {
            int temp = min(Q[j][i], Pick[j]);
            Pick[j] -= temp;
            Q[j][i] -= temp;
            m -= temp;
            if (m == 0)
              break;
          }
        t++;
      }
    }
    cout << t << ' ';
  }
  return 0;
}
