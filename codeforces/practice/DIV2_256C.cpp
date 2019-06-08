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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

vector<int> a;
int n;

ll DandC(int start, int end)
{
	db(start, end);
	if (start > end)
		return 0;
	int mini = a[start];
	for (int i = start; i <= end; ++i)
		mini = min(mini, a[i]);
	for (int i = start; i <= end; ++i)
		a[i] -= mini;
	ll verticalStroke = mini, solveUpperHalf = 0;
	int curr = -1;
	for (int i = start; i <= end; ++i)
	{
		db(i,a[i]);
		if (curr == -1 && a[i] > 0)
			curr = i;
		if (curr >= 0 && a[i] == 0)
		{
			solveUpperHalf += DandC(curr, i - 1);
			curr = -1;
		}
	}
	if (curr > 0)
		solveUpperHalf += DandC(curr, end);
	ll x = min((ll)end - start + 1, verticalStroke + solveUpperHalf);
	db(start, end, end - start + 1, verticalStroke, solveUpperHalf, verticalStroke + solveUpperHalf);
	return x;
}

void solve()
{
	cin >> n;
	a.resize(n);
	for (auto &x : a)
		cin >> x;
	cout << DandC(0, n - 1) << '\n';
	db("Ou");
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
	return 0;
}