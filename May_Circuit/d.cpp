//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
// #define multitest 1
#define Debug 1
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
	vector<pair<pair<int, int>, int>> V(n);
	int i = 0;
	for (auto &x : V)
	{
		cin >> x.f.f;
		x.s = i++;
	}
	for (auto &x : V)
		cin >> x.f.s;
	vector<pair<pair<int, int>, int>> V1 = V;
	sort(V.begin(), V.end());
	vector<int> Parent(n);
	stack<int> S;
	S.push(V[0].s);
	Parent[V[0].s] = -1;
	int time = 1;
	for (int i = 1; i < n; ++i)
	{
		// db(S.size());
		// db(S.top());
		// db(V[i].s);
		Parent[V[i].s] = S.top();
		S.push(V[i].s);
		time++;
		while (S.size() && (time >= V1[S.top()].f.s))
		{
			// db(S.size());
			// db(S.top());
			// db(V[i].s);
			S.pop();
		}
		// db(S.size());
		// db(S.top());
		// db(V[i].s);
	}
	for (int i = 0; i < n; ++i)
		cout << Parent[i] + 1 << ' ';
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
