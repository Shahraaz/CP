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
vector<int> D(51);

int DP_Cm(int start, int end, ll ssum)
{
	// db(start,end,ssum);
	if(start==end) return 0;
	ll sum = 0;
	for(int i=start;i<end;++i)
		sum += D[i];
	if(sum==ssum) return 1;
	int Ans = 0;
	for (int i = start; i < end; ++i)
	{
		ll sum = 0;
		for (int j = i; j < end; ++j)
		{
			sum += D[j];
			if(ssum==sum)
				Ans = max(Ans,1 + DP_Cm(j + 1, end, sum));
		}
	}
	return Ans;
}

void solve()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> D[i];
	int maxi=0,maxsum=-1;
	for (int i = 0; i < n; ++i)
	{
		ll sum = 0;
		for (int j = i; j < n; ++j)
		{
			sum += D[j];
			int Ans = 1 + DP_Cm(j + 1, n, sum);
			if(Ans>maxi)
			{
				maxi = Ans;
				maxsum = sum;
			}
		}
	}
	cout << maxi << '\n';
	for (int i = 0; i < n; ++i)
	{
		ll sum = 0;
		for (int j = i; j < n; ++j)
		{
			sum += D[j];
			if(sum==maxsum)
			{
				cout << i+1 << ' ' << j+1 << '\n';
				i = j;
				break;
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
