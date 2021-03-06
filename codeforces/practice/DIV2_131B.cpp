//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define multitest 1
// #define Debug 1
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

void solve()
{
	int n, x;
	cin >> n;
	vector<int> Count(10);
	int sum = 0;
	while (n--)
	{
		cin >> x;
		Count[x]++;
		sum += x;
	}
	// cout << sum << '\n';
	db(sum);
	if (Count[0] == 0)
		cout << -1 << '\n';
	else
	{
		if (sum % 3 == 1)
		{
			bool b = true;
			for (int i = 1; i <= 9; i += 3)
				if (Count[i])
				{
					Count[i]--;
					sum -= i;
					b = false;
					break;
				}
			if (b)
			{
				int cnt = 2;
				for (int i = 2; cnt && i < 10; i += 3)
					while (cnt && Count[i])
					{
						Count[i]--;
						sum -= i;
						cnt--;
					}
			}
		}
		else if (sum % 3 == 2)
		{
			bool b = true;
			for (int i = 2; i <= 9; i += 3)
				if (Count[i])
				{
					Count[i]--;
					sum -= i;
					b = false;
					break;
				}
			if (b)
			{
				int cnt = 2;
				for (int i = 1; cnt && i < 10; i += 3)
					while (cnt && Count[i])
					{
						Count[i]--;
						sum -= i;
						cnt--;
					}
			}
		}
		if (sum == 0)
			cout << 0;
		else
		{
			for (int i = 9; i >= 0; --i)
				while (Count[i])
				{
					cout << i;
					Count[i]--;
				}
		}
	}
}

int main()
{
#ifndef Debug
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#endif
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (t--)
		solve();
	return 0;
}