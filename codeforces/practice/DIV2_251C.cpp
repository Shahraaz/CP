//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
// #define multitest 1
#define Debug 1
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
	int x, n, k, p;
	cin >> n >> k >> p;
	vector<int> Even, Odd;
	for (int i = 0; i < n; ++i)
	{
		cin >> x;
		if (x & 1)
			Odd.pb(x);
		else
			Even.pb(x);
	}
	int eve = p, odd = k - p;
	if (odd > Odd.size())
		cout << "NO\n";
	else
	{
		int red = Odd.size() - odd;
		if (red & 1)
			cout << "NO\n";
		else
		{
			vector<vector<int>> ToPrint(k);
			int i;
			for (i = 0; i < odd; ++i)
			{
				if (Odd.size() == 0)
				{
					cout << "NO\n";
					return;
				}
				ToPrint[i].pb(Odd.back());
				Odd.pop_back();
			}
			int kdash;
			// bool a = false;
			for (i = odd; i < k; ++i)
			{
				if (eve && Even.size())
				{
					eve--;
					ToPrint[i].pb(Even.back());
					Even.pop_back();
				}
				else
				{
					// a = true;
					kdash = i;
					break;
				}
			}
			if (eve)
			{
				for (int i = kdash; i < k; ++i)
				{
					if (Odd.size() == 0)
					{
						cout << "NO\n";
						return;
					}
					ToPrint[i].pb(Odd.back());
					Odd.pop_back();
					if (Odd.size() == 0)
					{
						cout << "NO\n";
						return;
					}
					ToPrint[i].pb(Odd.back());
					Odd.pop_back();
				}
			}
			ToPrint[0].insert(ToPrint[0].end(),Odd.begin(),Odd.end());
			ToPrint[0].insert(ToPrint[0].end(), Even.begin(), Even.end());
			
			cout << "YES\n";
			for(auto x:ToPrint)
			{
				cout << x.size() << ' ';
				for(auto y:x)
					cout << y << ' ';
				cout << '\n';
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#ifndef Online
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	auto TimeStart = chrono::steady_clock::now();
	auto TimeEnd = chrono::steady_clock::now();
#endif
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (t--)
		solve();
#ifndef Online
	TimeEnd = chrono::steady_clock::now();
	auto ElapsedTime = TimeEnd - TimeStart;
	cout << "\n\nTime elapsed: " << chrono::duration<double>(ElapsedTime).count() << " seconds.\n";
#endif
	return 0;
}