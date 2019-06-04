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

int LIS(vector<int> &v)
{
    if (v.size() == 0)
        return 0;
    std::vector<int> tail(v.size(), 0);
    int length = 1; // always points empty slot in tail

    tail[0] = v[0];
    for (size_t i = 1; i < v.size(); i++)
    {
        if (v[i] > tail[length - 1])
            tail[length++] = v[i];
        else
        {
            // TO check whether the element is not present before hand
            auto it = find(tail.begin(), tail.begin() + length, v[i]);
            if (it != tail.begin() + length)
            {
                continue;
            }
            // If not present change the tail element to v[i]
            it = upper_bound(tail.begin(), tail.begin() + length, v[i]);
            *it = v[i];
        }
    }

    return length;
}
void solve()
{
    int n, c, x;
    cin >> c >> n;
    n = n * c;
    vector<pair<int, int>> V(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> V[i].f >> V[i].s;
        V[i].f--;
        V[i].s--;
        // swap(V[i].f,V[i].s);
    }
    int maxi = 0;
    vector<int> ind;
    for (int i = 0; i < c; ++i)
        ind.pb(i);
    vector<int> v(n);
    vector<vector<int>> Mat(c, vector<int>(n / c));
    do
    {
        int cnt = 0;
        for (int i = 0; i < c; ++i)
            for (int j = 0; j < n / c; ++j)
                Mat[i][j] = cnt++;
        for (int i = 0; i < n; ++i)
            v[i] = Mat[ind[V[i].f]][V[i].s];
        maxi = max(maxi, LIS(v));
    } while (next_permutation(ind.begin(), ind.end()));
    cout << n - maxi << '\n';
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