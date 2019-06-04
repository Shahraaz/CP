//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
// #define multitest 1
#define Debug
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
int a[4] = {1, -1, 0, 0};
int b[4] = {0, 0, 1, -1};
int n, m, k;
bool valid(int x, int y)
{
    if (x < 0 || y < 0)
        return false;
    return x < n && y < m;
}

void solve()
{
    cin >> n >> m >> k;
    vector<string> Maze(n);
    for (int i = 0; i < n; ++i)
        cin >> Maze[i];
    vector<vector<bool>> Visited(n, vector<bool>(m));
    vector<pair<int, int>> Q;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (Maze[i][j] == '.')
            {
                int l, r;
                l = 0;
                Visited[i][j] = true;
                Q.pb(mp(i, j));
                r = 1;
                while (l < r)
                {
                    int x = Q[l].f, y = Q[l].s;
                    for (int k = 0; k < 4; ++k)
                    {
                        int dx = x + a[k];
                        int dy = y + b[k];
                        if (valid(dx, dy) && !Visited[dx][dy] && Maze[dx][dy] == '.')
                        {
                            Visited[dx][dy] = true;
                            Q.pb(mp(dx,dy));
                            r++;
                        }
                    }
                    l++;
                }
                for(int i = r - k;i<r;++i)
                    Maze[Q[i].f][Q[i].s] = 'X';
                for(int i = 0;i<n;++i)
                    cout << Maze[i] << '\n';
                return;
            }
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
