//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Offline 1
#define multitest 1
typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
#define mp make_pair
const long long mod = 1000000007;
const long long High = 1e16;
void ControlIO()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
#ifdef Offline
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
}

void solve()
{
  int n;
  cin >> n;
  vector<string> Grid(n);
  vector<int> Ldist(n);
  for (int i = 0; i < n; ++i)
  {
    cin >> Grid[i];
    Ldist[i] = -1;
    for (int j = n - 1; j >= 0; --j)
      if (Grid[i][j] == '#')
      {
        Ldist[i] = j;
        break;
      }
  }
  int ans = 0;
  for (int j = 0; j < n; ++j)
  {
    for (int i = n - 1; i >= 0; --i)
    {
      if (Grid[i][j] == '.')
      {
        if(Ldist[i]<j)
          ans++;
      }
      else break;
    }
  }
  cout << ans << '\n';
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
