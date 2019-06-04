//Optimise
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define fast()                    \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ull, ull> pull;
#define f first
#define s second
#define pb push_back
#define mp make_pair
const long long mod = 1000000007;
const long long High = 1e16;

int main()
{
    fast();
    int n;
    cin >> n;
    map<int, int> Hash;
    vector<vector<int>> Table(n, vector<int>(n));
    for (int i = 0; i < n * n; ++i)
    {
        int x;
        cin >> x;
        Hash[x]++;
    }
    if (n & 1)
    {
        for (int i = 0; i < n / 2; ++i)
            for (int j = 0; j < n / 2; ++j)
            {
                auto it = Hash.begin();
                while (true)
                {
                    if (it->s >= 4)
                        break;
                    else
                        it++;
                // cout << it->f << ' ' << it->s << '\n';
                    if (it == Hash.end())
                    {
                        cout << "NO" << '\n';
                        return 0;
                    }
                }
                Table[i][j] = it->f;
                Table[n - 1 - i][j] = it->f;
                Table[n - 1 - i][n - 1 - j] = it->f;
                Table[i][n - 1 - j] = it->f;
                it->s -= 4;
                if (it->s == 0)
                    Hash.erase(it);
            }
        for (int i = 0; i < n / 2; ++i)
        {
            auto it = Hash.begin();
            while (true)
            {
                if (it->s >= 2)
                    break;
                else
                    it++;
                // cout << it->f << ' ' << it->s << '\n';
                if (it == Hash.end())
                {
                    cout << "NO" << '\n';
                    return 0;
                }
            }
            Table[i][n/2] = it->f;
            Table[n - 1 - i][n/2] = it->f;
            it->s -= 2;
            if (it->s == 0)
                Hash.erase(it);
        }
        for (int i = 0; i < n / 2; ++i)
        {
            auto it = Hash.begin();
            while (true)
            {
                if (it->s >= 2)
                    break;
                else
                    it++;
                if (it == Hash.end())
                {
                    cout << "NO" << '\n';
                    return 0;
                }
            }
            Table[n/2][i] = it->f;
            Table[n/2][n-1-i] = it->f;
            it->s -= 2;
            if (it->s == 0)
                Hash.erase(it);
        }
        auto it = Hash.begin();
        if(it==Hash.end())
        {
            cout << "NO";
            return 0;
        }
        Table[n/2][n/2] = it->f;
    }
    else
    {
        for (int i = 0; i < n / 2; ++i)
            for (int j = 0; j < n / 2; ++j)
            {
                auto it = Hash.begin();
                if (it->s % 4 != 0)
                {
                    cout << "NO";
                    return 0;
                }
                Table[i][j] = it->f;
                Table[n - 1 - i][j] = it->f;
                Table[n - 1 - i][n - 1 - j] = it->f;
                Table[i][n - 1 - j] = it->f;
                it->s -= 4;
                if (it->s == 0)
                    Hash.erase(it);
            }
    }
    cout<< "YES\n";
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << Table[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}
