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
    int n;
    cin >> n;
    vector<ll> SUM(n);
    cin >> SUM[0];
    for(int i=1;i<n;++i)
    {
        cin >> SUM[i];
        SUM[i] += SUM[i-1];
    }
    if(SUM[n-1]%3==0)
    {
        ll x = SUM[n-1]/3;
        vector<int> V1,V2;
        for(int i=0;i<n-1;++i)
        {
            if(SUM[i]==x) V1.pb(i);
            if(SUM[i]==2*x) V2.pb(i);
        }
        ll ans = 0;
        for(auto x:V1)
        {
            ans += V2.size() - (upper_bound(V2.begin(),V2.end(),x) - V2.begin());
            //cout << V2.size() - (upper_bound(V2.begin(),V2.end(),x) - V2.begin()) << '\n'; 
        }
        cout << ans;
    } 
    else
        cout << 0;    
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