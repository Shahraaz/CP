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

void solve()
{
	int zero,one;
	cin >> zero >> one;
	if(one+1 < zero)
	    cout << -1;
	else if(one+1==zero)
    {
        bool turn = 0;
        int t = one+zero;
        while(t--)
        {
            cout << turn;
            turn = !turn;
        }
    }
    else if(one <= 2*zero)
    {
        bool turn = 0;
        int ex = one - zero;
        int t = 2*zero;
        while(t--)
        {
            cout << turn;
            if(ex && turn)
            {
                cout << 1;
                ex--;
            }
            turn = !turn;
        }
    }
    else if(one == 2*zero+1)
    {
        one--;
        cout << 1;
        bool turn = 0;
        int t = 2*zero;
        int ex = one - zero;
        while(t--)
        {
            cout << turn;
            if(ex && turn)
            {
                cout << 1;
                ex--;
            }
            turn = !turn;
        }
    }
    else if(one == 2*zero+2)
    {
        one-=2;
        cout << 11;
        bool turn = 0;
        int t = 2*zero;
        int ex = one - zero;
        while(t--)
        {
            cout << turn;
            if(ex && turn)
            {
                cout << 1;
                ex--;
            }
            turn = !turn;
        }
    }
    else cout << -1;
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