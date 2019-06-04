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

ll power(ll idx)
{
    return idx*(idx+1)/2;;
}

void solve()
{
    int k;
    cin >> k;
    string str;
    cin >> str;
    vector<ll> V(str.length()+1);
    for(int i=1;i<=str.length();++i)
    {
        V[i] = V[i-1];
        if(str[i-1]=='1') V[i]++;
    }
    ll ans = 0;
    bool turn = str[0]=='0';
    for(auto it=V.begin();it!=V.end();)
    {
        auto it2 = upper_bound(it,V.end(),*it);
        if(k!=0)
            ans += (ll)(it2-it)*(ll)(upper_bound(it2,V.end(),*it+k)-lower_bound(it2,V.end(),*it+k));
        else
            ans += power(it2-it-1);
        //cout << *it << ' ' << (it2-it) << ' ' << (upper_bound(it2,V.end(),*it+k)-lower_bound(it2,V.end(),*it+k)) << '\n';
        it = it2;
    }
    cout << ans;
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
