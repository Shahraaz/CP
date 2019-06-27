//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
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

int rounds(int k, int n, int a)
{
	int c = k / a;
	k %= a;
	if (k == 0)
	{
		c--;
	}
	// db(k, n, a, c / n);
	return c / n;
}

int f2(int k, int n, int a)
{
	int c = k / a;
	k %= a;
	if (k == 0)
	{
		c--;
		k += a;
	}
	return k;
}

void solve()
{
	int k, n, a, b;
	cin >> k >> n >> a >> b;
	if (rounds(k, n, b) == 0)
	{
		cout << -1 << '\n';
		return;
	}
	if (k / b == n && k % b == 0)
	{
		cout << -1 << '\n';
		return;
	}
	ld temp = (k - n * b) / (ld(a) - b);
	int ans = 0;
	if (temp > n)
	{
		cout << n << '\n';
		return;
	}
	if(abs(temp-int(temp))<1e-8)
		temp--;
	cout << int(temp) << '\n';
	return;
	int onlyplay = rounds(k, n, a);
	// int onlyplaywhilecharge = rounds(k, n, b);
	int remrounds = k - onlyplay * n * a;
	int x = rounds(remrounds, n, b);
	{
		int low = 0, high = remrounds;
		int ans = 0;
		while (low <= high)
		{
			int mid = (low + high) / 2;
			int k = mid * a + (remrounds - mid) * b;
			if (k >= n)
			{
				ans = mid;
				low = mid + 1;
			}
			else
			{
				high = mid - 1;
			}
		}
		cout << onlyplay + ans << '\n';
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