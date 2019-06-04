//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
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
#define int long long

map<pair<int, int>, pair<int, int>> DpTable;

pair<int, int> DP(vector<int> &v, int start, int endi)
{
  if (start > endi)
    return mp(0, 0);
  if (DpTable.find(mp(start, endi)) != DpTable.end())
    return DpTable[mp(start, endi)];
  if (start == endi)
  {
    // cout << "Start " << start << " End " << endi << ' ';
    // cout << 0 << ' ' << v[start] << '\n';
    return DpTable[mp(start, endi)] = mp(0, v[start]);
  }
  pair<int, int> Ans = mp(mod, 100);
  for (int i = start; i < endi; ++i)
  {
    auto temp = DP(v, start, i);
    auto temp1 = DP(v, i + 1, endi);
    auto com = mp(temp.f + temp1.f + temp.s * temp1.s, (temp.s + temp1.s) % 100);
    Ans = min(Ans, com);
  }
  // cout << "Start " << start << " End " << endi << ' ';
  // cout << Ans.f << ' ' << Ans.s << '\n';
  return DpTable[mp(start, endi)] = Ans;
}

void solve(int n)
{
  DpTable.clear();
  vector<int> V(n);
  for (int i = 0; i < n; ++i)
    cin >> V[i];
  cout << DP(V, 0, n - 1).f << '\n';
}

main()
{
  ControlIO();
  int t = 1;
#ifdef multitest
  cin >> t;
#endif
  while (cin >> t)
    solve(t);
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