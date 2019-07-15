//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
// #define multitest 1
#define Debug 1
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

/*reference https://github.com/Ashishgup1/Competitive-Coding/blob/master/Convex%20Hull%20(Graham's%20Scan).cpp
COmputational Geometry and Computational Graphics in C++ */

class pint
{
public:
    int x, y;
    pint(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    bool operator<(const pint &p) const
    {
        return (x < p.x) || (x == p.x && y < p.y);
    }
    bool operator>(pint &p)
    {
        return (x > p.x) || (x == p.x && y > p.y);
    }
    bool operator==(pint &p)
    {
        return x == p.x && y == p.y;
    }
    bool operator!=(pint &p)
    {
        return !(*this == p);
    }
    pint operator=(const pint &p)
    {
        x = p.x;
        y = p.y;
        return *this;
    }
    pint operator*(int s)
    {
        return pint(s * x, s * y);
    }
    pint operator+(pint &p)
    {
        return pint(x + p.x, y + p.y);
    }
    pint operator-(pint &p)
    {
        return pint(x - p.x, y - p.y);
    }
    int operator[](const int i)
    {
        return i == 0 ? x : y;
    }
    int orientation(pint p0, pint p1, pint p2)
    {
        p1 = p1 - p0;
        p2 = p2 - p0;
        int sa = p1.x * p2.y - p2.x * p1.y;
        if (sa > 0)
            return 1;
        if (sa < 0)
            return -1;
        return 0;
    }
    int len2()
    {
        return x * x + y * y;
    }
};

void solve()
{
    set<pint> S;
    pint t;
    for (int i = 10; i > 0; --i)
    {
        t.x = t.y = i;
        S.insert(t);
    }
    for (auto A = S.begin(); A != S.end(); A++)
    {
        cout << A->x << ' ' << A->y << '\n';
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
