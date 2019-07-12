//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define multitest 1
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

using ll = long long;
#define f first
#define s second
#define pb push_back
const long long mod = 1000000007;
auto TimeStart = chrono::steady_clock::now();

const int nax = 2e5 + 10;

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	if (n == 1)
	{
		if (a[0] == 0)
			cout << "cslnb";
		else
		{
			if (a[0] & 1)
				cout << "sjfnb";
			else
				cout << "cslnb";
		}
	}
	else
	{
		sort(a.begin(), a.end());
		int zero = 0, i;
		for (i = 0; i < n; ++i)
		{
			if (a[i])
				break;
			zero++;
		}
		int dupCnt = 0, idx;
		for (int i = 0; i < n;)
		{
			auto up = upper_bound(a.begin(), a.end(), a[i]);
			int cnt = up - lower_bound(a.begin(), a.end(), a[i]);
			if (cnt > 3)
			{
				cout << "cslnb";
				return;
			}
			if (a[i] > 0)
				if (cnt == 2)
				{
					idx = i;
					dupCnt++;
				}
			i = up - a.begin();
		}
		if (dupCnt > 1)
		{
			cout << "cslnb";
			return;
		}
		if (dupCnt == 1)
		{
			if ()
		}
		if (i == n)
		{
			cout << "cslnb";
		}
		else
		{
			if (zero > 1)
			{
				cout << "cslnb";
			}
			else
			{
				map<int, int> PrevCnt;
				PrevCnt[0] = zero;
				bool turn = false;
				for (; i < n; ++i)
				{
					int pre = a[i] - 1;
					if (PrevCnt[pre] > 0)
					{
						// Dont Play this at ALl
						;
					}
					else
					{
						int diff = 0;
						if (i == 0)
						{
							diff = a[i];
						}
						else
						{
							diff = a[i] - a[i - 1];
						}
						if (diff == 0)
						{
						}
					}
				}
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (t--)
		solve();
#ifdef TIME
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}