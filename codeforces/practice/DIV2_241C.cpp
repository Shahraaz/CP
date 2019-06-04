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

typedef pair<int,int> pii;
vector<pii> R;
vector<pair<pii,int>> C;
int n,k;

void solve()
{
    cin >> n;
    C.resize(n);
    for(int i=0;i<n;++i)
    {
        cin >> C[i].f.s >> C[i].f.f;
        C[i].s = i;
        C[i].f.s *= -1;
    }
    cin >> k;
    R.resize(k);
    for(int i=0;i<k;++i)
    {
        cin >> R[i].f;
        R[i].s = i;
    }
    sort(C.begin(),C.end());
    sort(R.begin(),R.end());
    vector<pii> A;
    ll ret = 0;
    vector<bool> Vis(k);
    for(int i=n-1;i>=0;--i)
    {
        int tmp = -C[i].f.s;
        for(int j=0;j<k; ++j)
            if(R[i].f >= tmp && !Vis[j])
            {
                Vis[j] = true;
                ret += C[i].f.f;
                A.pb(mp(a[i].s+1,b[j].s+1));
            }
    }
    cout << A.size() << ' ' << ret << '\n';
    for(auto x:A)
        cout << x.f << ' ' < x.s << '\n';
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
