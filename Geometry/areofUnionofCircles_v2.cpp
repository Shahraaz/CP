#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
#define f first
#define s second
#define pb push_back
typedef long double ld;
const ld pi = acosl(-1);
const ld eps = 1e-7;

ld sq(ld a)
{
    return a * a;
}
ld correctArgument(ld a)
{
    if (a >= 2 * pi)
        return a - 2 * pi;
    return a;
}
bool overlap(int i, int j, vector<ld> &x, vector<ld> &y, vector<ld> &r)
{
    return (sqrtl(sq(x[i] - x[j]) + sq(y[i] - y[j])) + r[j]) <= r[i];
}
bool intersect(int i, int j, vector<ld> &x, vector<ld> &y, vector<ld> &r)
{
    ld d = sqrtl(sq(x[i] - x[j]) + sq(y[i] - y[j]));
    if (d > (r[i] + r[j]) || abs(r[i] - r[j]) >= d)
        return false;
    return true;
}
bool eq(ld a, ld b)
{
    return fabs(a - b) <= eps;
}
vector<ld> lineAndCircle(ld a, ld b, ld c, ld r)
{
    ld d = sqrtl(sq(2 * b) - 4 * (sq(b) + sq(a)) * (sq(c) - sq(r * a)));
    ld y1 = 2 * b * c + d, x1 = 0;
    ld y2 = 2 * b * c - d, x2 = 0;
    ld den = 2 * (sq(b) + sq(a));
    y1 /= den;
    y2 /= den;
    if (b == 0)
    {
        if (a != 0)
            x1 = x2 = c / a;
    }
    else
    {
        x1 = sqrtl(sq(y1) - sq(c / b));
        x2 = sqrtl(sq(y2) - sq(c / b));
    }
    vector<ld> v;
    v.pb(x1);
    v.pb(y1);
    v.pb(x2);
    v.pb(y2);
    return v;
}

vector<ld> GetSolutions(ld x1, ld y1, ld r1, ld x2, ld y2, ld r2)
{
    //after shifting the origin to x1 ,y1
    //equation of line is ax + by = c;
    ld a = 2 * (x1 - x2);
    ld b = 2 * (y1 - y2);
    ld c = sq(r2) - sq(r1) - sq(x1 - x2) - sq(y1 - y2);
    vector<ld> partialAnswer = lineAndCircle(a, b, c, r1);
    partialAnswer[0] += x1;
    partialAnswer[1] += y1;
    partialAnswer[2] += x1;
    partialAnswer[3] += y1;
    // cout << "PartialAnswer\n";
    // cout << partialAnswer[0] << ' ' << partialAnswer[1] << ' ' << partialAnswer[2] << ' ' << partialAnswer[3] << '\n';
    return partialAnswer;
}

ld getangle(ld x, ld y)
{
    if (x > 0 && eq(y, 0))
        return 0;
    if (x > 0 && y > 0)
        return atanl(y / x);
    if (eq(x, 0) && y > 0)
        return pi / 2;
    if (x < 0 && y > 0)
        return pi - atanl(fabs(y / x));
    if (x < 0 && y == 0)
        return pi;
    if (x < 0 && y < 0)
        return pi + atanl(fabs(y / x));
    if (eq(x, 0) && y < 0)
        return 3 * pi / 2;
    if (x > 0 && y < 0)
        return 2 * pi - atanl(fabs(y / x));
    return 0;
}

ld f1(ld x, ld y, ld r, ld theta)
{
    return r * (x * std::sin(theta)) + sq(r) * (theta + std::sin(theta) * std::cos(theta)) * 0.5;
    return x * r * sinl(theta) + (1 / 2) * sq(r) * (theta + sinl(theta) * cosl(theta));
}

ld f(int n, vector<ld> &x, vector<ld> &y, vector<ld> &r)
{
    ld answer = 0;
    // cout << n << '\n';
    for (int i = 0; i < n; ++i)
    {
        vector<pair<ld, ld>> IntersectionPoints;
        for (int j = 0; j < n; ++j)
            if (i != j && intersect(i, j, x, y, r))
            {
                vector<ld> ans = GetSolutions(x[i], y[i], r[i], x[j], y[j], r[j]);
                ld theta1 = getangle(ans[0] - x[i], ans[1] - y[i]);
                ld theta2 = getangle(ans[2] - x[i], ans[3] - y[i]);
                if (theta1 > theta2)
                    swap(theta1, theta2);
                // cout << i << ' ' << theta1 * 180 / pi << ' ' << theta2 * 180 / pi << '\n';
                ld mid = (theta1 + theta2) / 2;
                if (sq(x[j] - x[i] - r[i] * std::cos((theta1 + theta2) / 2.0)) + sq(y[j] - y[i] - r[i] * std::sin((theta1 + theta2) / 2.0)) < sq(r[j]))
                    IntersectionPoints.pb({theta1, theta2});
                else
                {
                    mid += pi;
                    mid = correctArgument(mid);
                    if (sq(x[j] - x[i] - r[i] * std::cos(correctArgument((theta1 + theta2) / 2.0 + pi))) + sq(y[j] - y[i] - r[i] * std::sin(correctArgument((theta1 + theta2) / 2.0 + pi))) < sq(r[j]))
                    {
                        IntersectionPoints.pb({theta2, 2 * pi});
                        IntersectionPoints.pb({0, theta1});
                    }
                }
            }
        // cout << IntersectionPoints.size() << " Size of intersection\n";
        if (IntersectionPoints.size() == 0)
        {
            cout << "No overlap\n";
            answer += pi * sq(r[i]);
        }
        else
        {
            sort(IntersectionPoints.begin(), IntersectionPoints.end());
            ld start = IntersectionPoints[0].f;
            ld end = IntersectionPoints[0].s;
            vector<pair<ld, ld>> IncludedAngles;
            IncludedAngles.pb({0, start});
            for (int j = 0; j < IntersectionPoints.size(); ++j)
            {
                while (j < IntersectionPoints.size() && end >= IntersectionPoints[j].f)
                {
                    end = max(end, IntersectionPoints[j].s);
                    ++j;
                }
                if (j < IntersectionPoints.size())
                {
                    IncludedAngles.pb({end, IntersectionPoints[j].f});
                    start = IntersectionPoints[j].f;
                    end = IntersectionPoints[j].s;
                }
            }
            IncludedAngles.pb({end, 2 * pi});
            for (int j = 0; j < IncludedAngles.size(); ++j)
            {
                // cout << j << ' ' << 180 / pi * IncludedAngles[j].f << ' ' << 180 / pi * IncludedAngles[j].s << '\n';
                if (!(IncludedAngles[j].f == 0 && IncludedAngles[j].s == (2 * pi)) && (IncludedAngles[j].f != IncludedAngles[j].s))
                {
                    cout << i << ' ' << x[i] << ' ' << y[i] << ' ' << r[i] << ' ' << 180 / pi * IncludedAngles[j].f << ' ' << 180 / pi * IncludedAngles[j].s << ' ';
                    ld a = f1(x[i], y[i], r[i], IncludedAngles[j].s);
                    ld b = f1(x[i], y[i], r[i], IncludedAngles[j].f);
                    cout << a << ' ' << b << '\n';
                    answer += a - b;
                }
            }
        }
        // cout << i << ' ' << answer << '\n';
    }
    return answer;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<ld> X, Y, R;
    ld x, y, r;
    for (int i = 0; i < n; ++i)
    {
        cin >> x >> y >> r;
        X.pb(x);
        Y.pb(y);
        R.pb(r);
    }
    vector<bool> Exist(n, true);
    for (int i = 0; i < n; ++i)
        if (Exist[i])
            for (int j = 0; j < n; ++j)
                if (i != j)
                    if (overlap(i, j, X, Y, R))
                        Exist[j] = false;
    vector<ld> X1, Y1, R1;
    for (int i = 0; i < n; ++i)
        if (Exist[i])
        {
            X1.pb(X[i]);
            Y1.pb(Y[i]);
            R1.pb(R[i]);
        }
    cout << fixed << setprecision(3) << f(X1.size(), X1, Y1, R1) << '\n';
    return 0;
}