//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Offline 1
// #define multitest 1
typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
#define mp make_pair
const long long mod = 1000000007;
const long long High = 1e16;
void ControlIO();

bool cmp(pair<ll, ll> a, pair<ll, ll> b)
{
  return a.f + b.s > b.f + a.s;
}

void solve()
{
  int n, x, y;
  cin >> n >> x >> y;
  vector<pair<ll, ll>> Tip(n);
  for (int i = 0; i < n; ++i)
    cin >> Tip[i].f;
  ll bsum = 0, asum = 0;
  for (int i = 0; i < n; ++i)
  {
    cin >> Tip[i].s;
    bsum += Tip[i].s;
  }
  sort(Tip.begin(), Tip.end(), cmp);
  ll ans = 0;
  for (int i = 0; i < n; ++i)
  {
    if ((x >= i) && (y >= (n - i)))
      ans = max(ans, asum + bsum);
    asum += Tip[i].f;
    bsum -= Tip[i].s;
    // cout << ans << '\n';
  }
  int i = n;
  if ((x >= i) && (y >= (n - i)))
    ans = max(ans, asum + bsum);
  cout << ans;
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
#ifdef Offline
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
}