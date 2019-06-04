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

typedef complex<ld> point;

#define PI 3.1415926535

ld printAngle(point A, point B, point C)
{
    // Square of lengths be a2, b2, c2
    ll a2 = norm(B - C);
    ll b2 = norm(A - C);
    ll c2 = norm(A - B);

    // lenght of sides be a, b, c
    ld a = sqrtl(a2);
    ld b = sqrtl(b2);
    ld c = sqrtl(c2);

    // From Cosine law
    ld gamma = acosl((-a2 + b2 + c2) / (2 * c * b));
    return gamma;
    // printing all the angles
}

ld printAngle(ld A, ld B, ld C)
{
    // Square of lengths be a2, b2, c2
    ll a2 = A * A;
    ll b2 = B * B;
    ll c2 = C * C;

    // lenght of sides be a, b, c
    ld a = A;
    ld b = B;
    ld c = C;

    // From Cosine law
    ld gamma = acosl((-a2 + b2 + c2) / (2 * c * b));
    return gamma;
    // printing all the angles
}

//rectangular class

ld dist(point a, point b)
{
    // return sqrtl((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    return abs(a-b);
}

ld dist(int x1, int y1, int x2, int y2)
{
    int a = x2 - x1;
    int b = y1 - y2;
    ll c = abs(a * y1 + b * x1);
    return c / (sqrtl(a * a + b * b));
}

void solve()
{
    int x1, y1, x2, y2, r;
    cin >> x1 >> y1 >> x2 >> y2 >> r;
    point a(x1, y1);
    point b(x2, y2);
    ld d1;
    if (x1 == x2)
        d1 = x1;
    else
        d1 = dist(x1, y1, x2, y2);
    if (d1 <= r)
    {
        db("A");
        ld phi = printAngle(point(0, 0), a, b);
        ld d1 = sqrtl(norm(a) - r * r);
        ld d2 = sqrtl(norm(b) - r * r);
        phi -= printAngle(d1, r, abs(a));
        phi -= printAngle(d2, r, abs(b));
        phi = min(phi, (2 * PI - phi));
        ld d3 = r * phi;
        cout << fixed << setprecision(6) << (d1 + d2 + d3) << '\n';
    }
    else
    {
        db("B");
        ld t1 = arg(a);
        ld t2 = arg(b);
        if(t1<0)
            t1 += PI;
        if(t1<0)
            t1 += PI;
        ld th = (t1 + t2) / 2;
        // db(t1,t2,th);
        point X = polar((ld)r,th);
        th += PI;
        if(th>2*PI)
        th = th - (2*PI);
        point Y = polar((ld)r,th);
        ld a1 = dist(a, X) + dist(b, X);
        ld a2 = dist(a, Y) + dist(b, Y);
        cout << fixed << setprecision(6) << min(a1, a2) << '\n';
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
