//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
// #define multitest 1
// #define Debug 1
void ControlIO();
void TimerStart();
void TimerStop();
#ifdef Debug
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__);
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
typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
const long long mod = 1000000007;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void solve()
{
	int n;
	cin >> n;
	vector<ll> V(n);
	for (auto &x : V)
		cin >> x;
	sort(V.begin(), V.end());
	if (n == 1)
		cout << -1;
	else if (n == 2)
	{
		if (V[0] == (V[1]))
			cout << 1 << '\n'
				 << V[0];
		else
		{
			int d = V[1] - V[0];
			if (d == 1 || (d & 1))
				cout << 2 << '\n'
					 << V[0] - d << ' ' << V[1] + d;
			else
				cout << 3 << '\n'
					 << V[0] - d << ' ' << (V[0] + V[1]) / 2 << ' ' << V[1] + d;
		}
	}
	else
	{
		if (V[0] == (V[n - 1]))
			cout << 1 << '\n'
				 << V[0];
		else
		{
			vector<ll> D(n - 1);
			for (int i = 0; i < (n - 1); ++i)
				D[i] = V[i + 1] - V[i];
			if (is_sorted(D.begin(), D.end()) && (D[0] == D[n - 2]))
			{
				if (D[0] == 0)
					cout << 1 << '\n'
						 << D[0];
				else
					cout << 2 << '\n'
						 << V[0] - D[0] << ' ' << V[n - 1] + D[0];
			}
			else
			{
				int maxi = *max_element(D.begin(), D.end());
				int mini = *min_element(D.begin(), D.end());
				int c = count(D.begin(), D.end(), maxi);
				int c1 = count(D.begin(), D.end(), mini);
				db(c, c1, mini, maxi);
				if (c == 1)
				{
					// db("a")
					if (c1 == (n - 2) && (maxi % 2 == 0) && (mini == (maxi / 2)))
					{
						for (int i = 0; i < (n - 1); ++i)
							if ((V[i + 1] - V[i]) == maxi)
							{
								cout << 1 << '\n'
									 << (V[i + 1] + V[i]) / 2;
								return;
							}
					}
					else
						cout << 0;
				}
				else
					cout << 0;
			}
		}
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