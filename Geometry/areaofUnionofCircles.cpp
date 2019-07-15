#include <bits/stdc++.h>
#define ll int
#define pll std::pair<ll, ll>
#define rep(i, a, b) for (ll i = (ll)a; i < (ll)b; i++)
#define per(i, a, b) for (ll i = (ll)a; i > (ll)b; i--)
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define full(a) a.begin(), a.end()
#define rfull(a) a.rbegin(), a.rend()

using namespace std;
const long double pi = acos(-1.0);
const long double pii = 2 * pi;
const long double eps = 1e-6;

inline long double sq(long double a) { return a * a; };
inline long double parg(long double d)
{
    if (d >= pii)
    {
        d -= pii;
    }
    return d;
}

bool inter(int i, int j, std::vector<long double> &x, std::vector<long double> &y, std::vector<long double> &r)
{
    long double d = std::sqrt(sq(x[i] - x[j]) + sq(y[i] - y[j]));
    if (d > r[i] + r[j] || std::abs(r[i] - r[j]) >= d)
    {
        return false;
    }
    return true;
}

void quadratic(long double a, long double b, long double c, long double &x1, long double &x2)
{
    x1 = (-b - std::sqrt(sq(b) - 4 * a * c)) / (2 * a);
    x2 = (-b + std::sqrt(sq(b) - 4 * a * c)) / (2 * a);
}

void lyx(long double a, long double b, long double c, long double &x, long double &y)
{
    if (b)
    {
        y = (c - a * x) / b;
    }
}

bool lcf(long double x, long double y, long double r, long double a, long double b, long double c, std::vector<long double> &ans)
{
    long double x1, x2, y1, y2;
    if (b)
    {
        quadratic(1 + sq(a / b), -2 * x - 2 * (a / b) * (c / b - y), sq(x) + sq(c / b - y) - sq(r), x1, x2);
        lyx(a, b, c, x1, y1);
        lyx(a, b, c, x2, y2);
        ans = {x1, y1, x2, y2};
    }
    else
    {
        quadratic(1, -2 * y, sq(y) + sq(c / a - x) - sq(r), y1, y2);
        x1 = c / a;
        ans = {x1, y1, x1, y2};
    }
    return true;
}

inline long double gth(long double x, long double y)
{
    if (x > 0.0 && y == 0.0)
    {
        return 0.0;
    }
    if (x > 0.0 && y > 0.0)
    {
        return std::atan(y / x);
    }
    if (x == 0.0 && y > 0)
    {
        return pi / 2.0;
    }
    if (x < 0.0 && y > 0.0)
    {
        return pi - std::atan(std::abs(y / x));
    }
    if (x < 0.0 && y == 0.0)
    {
        return pi;
    }
    if (x < 0.0 && y < 0.0)
    {
        return pi + std::atan(std::abs(y / x));
    }
    if (x == 0.0 && y < 0.0)
    {
        return 1.5 * pi;
    }
    if (x > 0.0 && y < 0.0)
    {
        return pii - std::atan(std::abs(y / x));
    }
    return 0.0;
}

inline long double f1(long double x, long double y, long double r, long double theta)
{
    return r * (x * std::sin(theta)) + sq(r) * (theta + std::sin(theta) * std::cos(theta)) * 0.5;
}

long double f(int n, std::vector<long double> x, std::vector<long double> y, std::vector<long double> r)
{
    long double ans;
    rep(i, 0, n)
    {
        std::vector<std::pair<long double, long double>> iPnts{};
        rep(j, 0, n)
        {
            if (i != j && inter(i, j, x, y, r))
            {
                std::vector<long double> ans(4, 0.0);
                lcf(x[i], y[i], r[i], 2 * (x[j] - x[i]), 2 * (y[j] - y[i]), sq(r[i]) - sq(r[j]) + sq(x[j]) - sq(x[i]) + sq(y[j]) - sq(y[i]), ans);
                long double theta1 = gth(ans[0] - x[i], ans[1] - y[i]);
                long double theta2 = gth(ans[2] - x[i], ans[3] - y[i]);
                if (theta1 > theta2)
                {
                    std::swap(theta1, theta2);
                }
                // cout << i << ' ' << theta1 * 180 / pi << ' ' << theta2 * 180 / pi << '\n';

                if (sq(x[j] - x[i] - r[i] * std::cos((theta1 + theta2) / 2.0)) + sq(y[j] - y[i] - r[i] * std::sin((theta1 + theta2) / 2.0)) < sq(r[j]))
                {
                    iPnts.pb({theta1, theta2});
                }
                else
                {
                    if (sq(x[j] - x[i] - r[i] * std::cos(parg((theta1 + theta2) / 2.0 + pi))) + sq(y[j] - y[i] - r[i] * std::sin(parg((theta1 + theta2) / 2.0 + pi))) < sq(r[j]))
                    {
                        iPnts.pb({theta2, pii});
                        iPnts.pb({0.0, theta1});
                    }
                }
            }
        }
        if (iPnts.size() == 0)
        {
            // cout << "No overlap\n";
            ans += pi * sq(r[i]);
        }
        else
        {
            std::sort(full(iPnts));
            long double theta1 = iPnts[0].F, theta2 = iPnts[0].S;
            std::vector<std::pair<long double, long double>> intlims{{0.0, theta1}};

            rep(j, 0, iPnts.size())
            {
                while (j < iPnts.size() && theta2 >= iPnts[j].F)
                {
                    theta2 = std::max(iPnts[j].S, theta2);
                    j++;
                }
                if (j < iPnts.size())
                {
                    intlims.pb({theta2, iPnts[j].F});
                    theta1 = iPnts[j].F;
                    theta2 = iPnts[j].S;
                }
            }
            intlims.pb({theta2, pii});

            rep(j, 0, intlims.size())
            {
                if (!(intlims[j].F == 0.0 && intlims[j].S == pii) && (intlims[j].F != intlims[j].S))
                {
                    // cout << i << ' ' << x[i] << ' ' << y[i] << ' ' << r[i] << ' ' << intlims[j].F / pi * 180 << ' ' << intlims[j].S / pi * 180 << ' ' << f1(x[i], y[i], r[i], intlims[j].S) << ' ' << f1(x[i], y[i], r[i], intlims[j].F) << '\n';
                    // cout << (f1(x[i], y[i], r[i], intlims[j].S) - f1(x[i], y[i], r[i], intlims[j].F)) << '\n';
                    ans += (f1(x[i], y[i], r[i], intlims[j].S) - f1(x[i], y[i], r[i], intlims[j].F));
                }
            }
        }
    }
    return ans;
}

inline bool f4(int j, int i, std::vector<long double> &x, std::vector<long double> &y, std::vector<long double> &r)
{
    return (j != i && (std::sqrt(sq(x[i] - x[j]) + sq(y[i] - y[j])) + r[j]) <= r[i]) ? true : false;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    int n;
    std::cin >> n;
    std::vector<long double> xp(n, 0.0), yp(n, 0.0), rp(n, 0.0), x{}, y{}, r{};
    rep(i, 0, n)
    {
        std::cin >> xp[i] >> yp[i] >> rp[i];
        rp[i] = std::abs(rp[i]);
    }

    std::vector<bool> in(n, true);
    rep(i, 0, n)
    {
        rep(j, 0, n)
        {
            if (in[i] && f4(j, i, xp, yp, rp))
            {
                in[j] = false;
            }
        }
    }
    rep(i, 0, n)
    {
        if (in[i])
        {
            x.pb(xp[i]);
            y.pb(yp[i]);
            r.pb(rp[i]);
        }
    }
    std::cout << std::fixed << std::setprecision(3) << f(x.size(), x, y, r) << "\n";
    return 0;
}