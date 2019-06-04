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
	string l, r;
	cin >> l;
	cin >> r;
	vector<queue<int>> LBOOT(26), RBOOT(26);
	queue<int> L, R;
	for (int i = 0; i < n; ++i)
		if (l[i] == '?')
			L.push(i + 1);
		else
			LBOOT[l[i] - 'a'].push(i + 1);
	for (int i = 0; i < n; ++i)
		if (r[i] == '?')
			R.push(i + 1);
		else
			RBOOT[r[i] - 'a'].push(i + 1);
	vector<pair<int, int>> Ans;
	for (int i = 0; i < 26; ++i)
	{
		int k = min(LBOOT[i].size(), RBOOT[i].size());
		for (int j = 0; j < k; ++j)
		{
			Ans.pb(mp(LBOOT[i].front(), RBOOT[i].front()));
			LBOOT[i].pop();
			RBOOT[i].pop();
		}
	}
	for (int i = 0; i < 26; ++i)
	{
		int k = min(LBOOT[i].size(), R.size());
		for (int j = 0; j < k; ++j)
		{
			Ans.pb(mp(LBOOT[i].front(), R.front()));
			LBOOT[i].pop();
			R.pop();
		}
	}
	for (int i = 0; i < 26; ++i)
	{
		int k = min(RBOOT[i].size(), L.size());
		for (int j = 0; j < k; ++j)
		{
			Ans.pb(mp(L.front(), RBOOT[i].front()));
			RBOOT[i].pop();
			L.pop();
		}
	}
	int k = min(L.size(), R.size());
	while (k--)
	{
		Ans.pb(mp(L.front(), R.front()));
		R.pop();
		L.pop();
	}
	cout << Ans.size() << '\n';
	for (auto x : Ans)
		cout << x.f << ' ' << x.s << "\n";
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
