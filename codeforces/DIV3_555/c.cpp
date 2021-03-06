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
	vector<int> V(n);
	// cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> V[i];
	int s = 0, e = n - 1, size = n;
	int prev = 0;
	queue<char> Q;
	while (size)
	{
		int x = size;
		// db(s,e,V[s],V[e],prev);
		if (V[s] > prev)
		{
			if ((V[e] > prev) && (V[e] < V[s]))
			{
				prev = V[e];
				Q.push('R');
				e--;
				size--;
			}
			else
			{
				prev = V[s];
				Q.push('L');
				s++;
				size--;
			}
		}
		else if (V[e] > prev)
		{
			prev = V[e];
			Q.push('R');
			e--;
			size--;
		}
		else break;
	}
	cout << Q.size() << '\n';
	while(!Q.empty())
	{
		cout << Q.front();
		Q.pop();
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
