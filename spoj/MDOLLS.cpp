//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
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

bool cmp(pair<int, int> a, pair<int, int> b)
{
    if (a.f == b.f)
        return a.s > b.s;
    return a.f < b.f;
}

void solve()
{
    int n;
    cin >> n;
    vector<pair<int, int>> V(n);
    for (int i = 0; i < n; ++i)
        cin >> V[i].f >> V[i].s;
    sort(V.begin(), V.end(),cmp);
    vector<pair<int, int>> Buffer;
    Buffer.pb(V[n - 1]);
    for (int i = n - 2; i >= 0; --i)
    {
        int low = 0, high = Buffer.size() - 1, mid;
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (Buffer[mid].f == V[i].f || (Buffer[mid].s <= V[i].s))
                low = mid + 1;
            else
                high = mid - 1;
        }
        if (low == Buffer.size())
            Buffer.pb(V[i]);
        else
            Buffer[low] = V[i];
    }
    cout << Buffer.size() << '\n';
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