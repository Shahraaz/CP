//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
#define multitest 1
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

set<int> Set;

int add(int n)
{
	n++;
	while (n % 10 == 0)
		n /= 10;
	return n;
}

void F(int n)
{
	if (Set.find(n) == Set.end())
	{
		Set.insert(n);
		n = add(n);
		F(n);
	}
}

ll solve1(int n)
{
	int i,j,a,b,ld;
	int sum = 0;
	ld = n % 10;
	n = n / 10;
	sum += 9;
	if (n != 0)
	{
		if (ld == 0)
			sum += 10;
		else
			sum += (10 - ld);
		if ((n / 10) > 0)
			n++;
		while ((n / 10) > 0)
		{
			if ((n % 10) != 0)
			{
				sum += (10 - (n % 10));
				n /= 10;
				n++;
			}
			else
				n /= 10;
		}
	}
	return sum;
}

void solve()
{
	Set.clear();
	int n;
	cin >> n;
	// n = rand()%mod;
	F(n);
	if(Set.size() > 2000)
		cout << n << '\n';
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
