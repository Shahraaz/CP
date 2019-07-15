//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
#define multitest 1
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

const ld PI = 2 * acosl(0.0000000000000000000000);

ll sqr(int x)
{
    return (ll)x * x;
}

vector<ld> A, B;

void add(ld start, ld end)
{
    if (start > end)
        end += 2 * PI;
    if (end > PI)
    {
        A.pb(start);
        B.pb(PI);
        A.pb(-PI);
        B.pb(end - 2 * PI);
    }
    else if(start <= -PI)
    {
        A.pb(start + 2*PI);
        B.pb(PI);
        A.pb(-PI);
        B.pb(end);
    }
    else
    {
        A.pb(start);
        B.pb(end);
    }
    
}

void solve()
{
    int w, h, n;
    cin >> w >> h >> n;
    w *= 100;
    h *= 100;
    vector<int> X(n), Y(n), R(n);
    ld x, y, r;
    for (int i = 0; i < n; ++i)
    {
        cin >> x >> y >> r;
        X[i] = (int)(100 * x + 0.5);
        Y[i] = (int)(100 * y + 0.5);
        R[i] = (int)(100 * r + 0.5);
    }
    ld res = 0;
    for (int i = 0; i < n; ++i)
    {
        x = X[i];
        y = Y[i];
        r = R[i];
        if (x - w >= r || y - h >= r)
            continue;
        A.clear();
        B.clear();
        if (x < r)
        {
            ld ang = acosl(-(ld)x / r);
            add(ang, -ang);
        }
        if (abs(w - x) < r)
        {
            ld ang = acosl((ld)(w - x) / r);
            add(-ang, ang);
        }
        if (y < r)
        {
            ld ang = asinl((ld)y / r);
            add(ang - PI, -ang);
        }
        if (abs(h - y) < r)
        {
            ld ang = asinl((ld)(h - y) / r);
            add(ang, PI - ang);
        }
        bool covered = false;
        for (int j = 0; j < n; ++j)
        {
            if (i == j)
                continue;
            int xj = X[j], yj = Y[j], rj = R[j];
            ll Dij = sqr(xj - x) + sqr(yj - y);
            if (rj >= r && sqr(rj - r) >= Dij)
            {
                covered = true;
                break;
            }
            if (Dij >= sqr(r + rj) || r >= rj && sqr(r - rj) >= Dij)
                continue;
            ld phi = atan2l(ld(yj - y), ld(xj - x));
            ld alp = acosl((sqr(r) + Dij - sqr(rj)) / (2 * r * sqrtl(ld(Dij))));
            add(phi - alp, phi + alp);
        }
        if (covered)
            continue;
        ld Visible = 2 * PI;
        if (A.size())
        {
            sort(A.begin(), A.end());
            sort(B.begin(), B.end());
            ld cura = A[0], curb = B[0];
            for (int j = 1; j < A.size(); ++j)
            {
                if (curb < A[j])
                {
                    Visible -= curb - cura;
                    cura = A[j];
                }
                curb = B[j];
            }
            Visible -= curb - cura;
        }
        res += r * Visible;
    }
    cout << fixed << setprecision(15) << res / 100 << '\n';
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
