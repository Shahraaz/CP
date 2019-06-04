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

typedef pair<int, int> pii;

bool cmp(pii a, pii b)
{
    return abs(a.f) + abs(a.s) < abs(b.f) + abs(b.s);
}

void solve()
{
    int n;
    cin >> n;
    vector<pii> V(n);
    for (auto &x : V)
        cin >> x.f >> x.s;
    sort(V.begin(), V.end(), cmp);
    vector<string> Ans;
    for (auto x : V)
    {
        if (x.f == 0)
        {
            if (x.s < 0)
            {
                string str = "1 ";
                str += to_string(abs(x.s));
                str += " D";
                Ans.pb(str);
                Ans.pb("2");
                str = "1 ";
                str += to_string(abs(x.s));
                str += " U";
                Ans.pb(str);
                Ans.pb("3");
            }
            else
            {
                string str = "1 ";
                str += to_string(abs(x.s));
                str += " U";
                Ans.pb(str);
                Ans.pb("2");
                str = "1 ";
                str += to_string(abs(x.s));
                str += " D";
                Ans.pb(str);
                Ans.pb("3");
            }
        }
        else if (x.s == 0)
        {
            swap(x.f,x.s);
            if (x.s < 0)
            {
                string str = "1 ";
                str += to_string(abs(x.s));
                str += " L";
                Ans.pb(str);
                Ans.pb("2");
                str = "1 ";
                str += to_string(abs(x.s));
                str += " R";
                Ans.pb(str);
                Ans.pb("3");
            }
            else
            {
                string str = "1 ";
                str += to_string(abs(x.s));
                str += " R";
                Ans.pb(str);
                Ans.pb("2");
                str = "1 ";
                str += to_string(abs(x.s));
                str += " L";
                Ans.pb(str);
                Ans.pb("3");
            }
        }
        else
        {
            if (x.s < 0)
            {
                string str = "1 ";
                str += to_string(abs(x.s));
                str += " D";
                Ans.pb(str);
                str = "1 ";
                str += to_string(abs(x.f));
                if(x.f<0)
                    str += " L";
                else str += " R";
                Ans.pb(str);
                Ans.pb("2");
                str = "1 ";
                str += to_string(abs(x.f));
                if(x.f<0)
                    str += " R";
                else str += " L";
                Ans.pb(str);
                str = "1 ";
                str += to_string(abs(x.s));
                str += " U";
                Ans.pb(str);
                Ans.pb("3");
            }
            else
            {
                string str = "1 ";
                str += to_string(abs(x.s));
                str += " U";
                Ans.pb(str);
                str = "1 ";
                str += to_string(abs(x.f));
                if(x.f<0)
                    str += " L";
                else str += " R";
                Ans.pb(str);
                Ans.pb("2");
                str = "1 ";
                str += to_string(abs(x.f));
                if(x.f<0)
                    str += " R";
                else str += " L";
                Ans.pb(str);
                str = "1 ";
                str += to_string(abs(x.s));
                str += " D";
                Ans.pb(str);
                Ans.pb("3");
            }  
        }       
    }
    cout << Ans.size() << '\n';
    for(auto x:Ans)
        cout << x << '\n';
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