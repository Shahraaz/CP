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

typedef int typeone;
typedef long double typetwo;
class pint
{
public:
    typeone x, y;
    pint(typeone _x = 0, typeone _y = 0) : x(_x), y(_y) {}
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
    pint operator*(typeone s)
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
    typeone operator[](const typeone i)
    {
        return i == 0 ? x : y;
    }
    typeone orientation(pint p0, pint p1, pint p2)
    {
        p1 = p1 - p0;
        p2 = p2 - p0;
        typeone sa = p1.x * p2.y - p2.x * p1.y;
        if (sa > 0)
            return 1;
        if (sa < 0)
            return -1;
        return 0;
    }
    typeone len2()
    {
        return x * x + y * y;
    }
    typetwo PolarAngle()
    {
        if (x == 0 && y == 0)
            return 0;
        if (x == 0)
            return (y > 0) ? 90 : 270;
        typetwo theta = atan((ld)y / x);
        theta *= 180 / (ld)3.141592653;
        if (x > 0)
            return y >= 0 ? theta : 360 + theta;
        else
            return 180 + theta;
    }
};

void solve()
{
    int n, x, y;
    cin >> n;
    vector<pair<ld, pint>> C;
    for (int i = 0; i < n; ++i)
    {
        cin >> x >> y;
        pint a(x, y);
        C.pb(mp(a.PolarAngle(), a));
    }
    sort(C.begin(), C.end());
    if (n == 1)
        cout << 0;
    else
    {
        if (n == 2)
        {
            auto x = abs(C[0].f - C[1].f);
            cout << min(x, 360 - x);
            return;
        }
        ld mini = mod;
        for (int i = 0; i < n - 1; ++i)
        {
            int j = (i + 1) % n;
            mini = min(mini, 360 - C[j].f + C[i].f);
        }
        mini = min(mini, C[n-1].f - C[0].f);
        cout << fixed << setprecision(9) << mini;
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
