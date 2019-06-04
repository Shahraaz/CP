//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
// #define multitest 1
// #define Debug 1
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
int n, m, k;
int a[4] = {1, 0, 0, -1};
int b[4] = {0, -1, 1, 0};

bool valid(int x, int y)
{
    return (x >= 0 && y >= 0) && (x < n && y < m);
}

queue<int> Temp;
vector<vector<bool>> Vis(1004, vector<bool>(1004));

void DFS(int i, int j)
{
    if (Vis[i][j])
        return;
    Vis[i][j] = true;
    Temp.push(i + 1);
    Temp.push(j + 1);
    for (int k = 0; k < 4; ++k)
        if (valid(i + a[k], j + b[k]))
            DFS(i + a[k], j + b[k]);
}

void solve()
{
    cin >> n >> m >> k;
    int curr = 1;
    int i, j;
    i = 0;
    j = 0;
    {
        DFS(0, 0);
        while (curr != k)
        {
            cout << 2 << ' ' << Temp.front() << ' ';
            Temp.pop();
            cout << Temp.front() << ' ';
            Temp.pop();
            cout << Temp.front() << ' ';
            Temp.pop();
            cout << Temp.front() << '\n';
            Temp.pop();
            curr++;
        }
        cout << Temp.size() / 2 << ' ';
        while (Temp.size())
        {
            cout << Temp.front() << ' ';
            Temp.pop();
        }
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
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
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