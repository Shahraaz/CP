/* Read input from STDIN. Print your output to STDOUT*/
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
int main(int argc, char *a[])
{
    int t = 0;
    cin >> t;
    while (t--)
    {
        int x, r, c;
        // cin >> r >> c;
        r = rand() % 10 + 1;
        c = rand() % 10 + 1;
        int ans1, ans2;
        vector<int> R, C;
        ans1 = ans2 = 0;
        bool Mat[r][c];
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                Mat[i][j] = rand() % 2;
        for (int i = 0; i < r; ++i)
        {
            // cin >> x;
            x = 0;
            for (int j = 0; j < c; ++j)
                x += Mat[i][j];
            cout << x << ' ';
            R.pb(x);
        }
        cout << '\n';
        for (int j = 0; j < c; ++j)
        {
            // cin >> x;
            x = 0;
            for (int i = 0; i < r; ++i)
                x += Mat[i][j];
            cout << x << ' ';
            C.pb(x);
        }
        cout << '\n';
        string res = "YES\n";
        sort(R.begin(), R.end());
        reverse(R.begin(), R.end());
        for (int i = 0; i < r; ++i)
        {
            int x = R[i];
            for (int j = c - 1; j >= 0 && x > 0; --j)
            {
                if (C[j] == 0)
                    continue;
                x--;
                C[j]--;
                if (C[j] < 0)
                {
                    res = "NO\n";
                    break;
                }
            }
            if (x != 0)
                res = "NO\n";
        }
        for (int j = 0; j < c; ++j)
            if (C[j] != 0)
                res = "NO\n";
        cout << res;
        for (int i = 0; i < r; ++i)
        {
            for (int j = 0; j < c; ++j)
                cout << Mat[i][j] << ' ';
            cout << '\n';
        }
    }
}
