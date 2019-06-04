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

vector<int> A(1005);

void solve()
{
  int n, k;
  cin >> n >> k;
  vector<bool> Exist(1024);
  Exist[0] = 0;
  for (int i = 0; i < n; ++i)
  {
    cin >> A[i];
    Exist[A[i]] = true;
  }
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < 1024; ++j)
      Exist[j ^ A[i]] = Exist[j ^ A[i]] || Exist[j];
  int ans = k;
  for (int i = 0; i < 1024; ++i)
    if (Exist[i])
      ans = max(ans, k ^ i);
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
