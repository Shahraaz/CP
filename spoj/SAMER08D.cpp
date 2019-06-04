//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
// #define multitest 1
// #define Interactive 1
typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
#define mp make_pair
const long long mod = 1000000007;
const long long High = 1e16;
void ControlIO();

void solve(int k)
{
    // cout << "Solve\n";
    string s, t;
    cin >> s >> t;
    int l1 = s.length(), l2 = t.length();
    vector<vector<int>> cont(l1 + 5, vector<int>(l2 + 5)), lcs(l1 + 5, vector<int>(l2 + 5));
    for (int i = 1; i <= l1; ++i)
        for (int j = 1; j <= l2; ++j)
        {
            lcs[i][j] = max(lcs[i][j - 1], lcs[i - 1][j]);
            if (s[i - 1] == t[j - 1])
                cont[i][j] = cont[i - 1][j - 1] + 1;
            else
                cont[i][j] = 0;
            if (cont[i][j] >= k)
                for (int z = k; z <= cont[i][j]; ++z)
                    lcs[i][j] = max(lcs[i][j], lcs[i - z][j - z] + z);
        }
    cout << lcs[l1][l2] << '\n';
}

int main()
{
    ControlIO();
    int t = 1;
#ifdef multitest
    cin >> t;
#endif
    cin >> t;
    while (t)
    {
        solve(t);
        cin >> t;
    }
    return 0;
}

void ControlIO()
{
    ios_base::sync_with_stdio(0);
#ifndef Interactive
    cin.tie(0);
#endif
#ifndef Online
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}