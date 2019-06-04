//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
// #define multitest 1
// #define Debug
typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
#define mp make_pair
const long long mod = 1000000007;
const long long High = 1e16;
void ControlIO();
void TimerStart();
void TimerStop();
#ifdef Debug
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void ZZ(const char *name, Arg1 &&arg1)
{
    std::cerr << name << " = " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void ZZ(const char *names, Arg1 &&arg1, Args &&... args)
{
    const char *comma = strchr(names + 1, ',');
    std::cerr.write(names, comma - names) << " = " << arg1;
    ZZ(comma, args...);
}
#else
#define db(...)
#endif

int a[4] = {0, 0, 1, -1};
int b[4] = {1, -1, 0, 0};
int n, m;
bool valid(int i, int j)
{
    return i >= 0 && i < n && j >= 0 && j < m;
}
vector<string> V;

int GO(int i, int j)
{
    vector<vector<bool>> Vis(n, vector<bool>(m));
    Vis[i][j] = true;
    int t = 1;
    for (int i1 = i + 1; i1 < n; ++i1)
        if (V[i1][j] == 'B')
        {
            for (int j1 = j; j1 < m; ++j1)
                if (V[i1][j1] == 'B')
                {
                    t += !Vis[i1][j1];
                    Vis[i1][j1] = true;
                }
                else
                    break;
            for (int j1 = j - 1; j1 >= 0; --j1)
                if (V[i1][j1] == 'B')
                {
                    t += !Vis[i1][j1];
                    Vis[i1][j1] = true;
                }
                else
                    break;
        }
        else
            break;

    for (int i1 = i - 1; i1 >= 0; --i1)
        if (V[i1][j] == 'B')
        {
            for (int j1 = j; j1 < m; ++j1)
                if (V[i1][j1] == 'B')
                {
                    t += !Vis[i1][j1];
                    Vis[i1][j1] = true;
                }
                else
                    break;
            for (int j1 = j - 1; j1 >= 0; --j1)
                if (V[i1][j1] == 'B')
                {
                    t += !Vis[i1][j1];
                    Vis[i1][j1] = true;
                }
                else
                    break;
        }
        else
            break;
    for (int j1 = j + 1; j1 < m; ++j1)
        if (V[i][j1] == 'B')
        {
            for (int i1 = i; i1 < n; ++i1)
                if (V[i1][j1] == 'B')
                {
                    t += !Vis[i1][j1];
                    Vis[i1][j1] = true;
                }
                else
                    break;
            for (int i1 = i - 1; i1 >= 0; --i1)
                if (V[i1][j1] == 'B')
                {
                    t += !Vis[i1][j1];
                    Vis[i1][j1] = true;
                }
                else
                    break;
        }
        else
            break;
    for (int j1 = j - 1; j1 >= 0; --j1)
        if (V[i][j1] == 'B')
        {
            for (int i1 = i; i1 < n; ++i1)
                if (V[i1][j1] == 'B')
                {
                    t += !Vis[i1][j1];
                    Vis[i1][j1] = true;
                }
                else
                    break;
            for (int i1 = i - 1; i1 >= 0; --i1)
                if (V[i1][j1] == 'B')
                {
                    t += !Vis[i1][j1];
                    Vis[i1][j1] = true;
                }
                else
                    break;
        }
        else
            break;
    db(i, j, t);
    return t;
}

void solve()
{
    cin >> n >> m;
    V.resize(n);
    for (auto &x : V)
        cin >> x;
    vector<vector<bool>> Vis(n, vector<bool>(m));
    typedef pair<int, int> pii;
    int Black = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            Black += V[i][j] == 'B';
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (V[i][j] == 'B')
            {
                if (GO(i, j) != Black)
                {
                    cout << "NO";
                    return;
                }
            }
    cout << "YES";
}

int main()
{
    ControlIO();
    int t = 1;
#ifdef multitest
    cin >> t;
#endif
    TimerStart();
    while (t--)
        solve();
    TimerStop();
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

auto TimeStart = chrono::steady_clock::now();
auto TimeEnd = chrono::steady_clock::now();

void TimerStart()
{
#ifndef Online
    TimeStart = chrono::steady_clock::now();
#endif
}

void TimerStop()
{
#ifndef Online
    TimeEnd = chrono::steady_clock::now();
    auto ElapsedTime = TimeEnd - TimeStart;
    cout << "\n\nTime elapsed: " << chrono::duration<double>(ElapsedTime).count() << " seconds.\n";
#endif
}
