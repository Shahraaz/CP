//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
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

const int nax = 25;
int n, k;
vector<int> a(nax);

int solve(int pos, int rem, int prevXor)
{
	if (pos == n) // Exhausted the element choice
	{
		if (rem == 0) // You have chosen k elements somehow, so this is valid
			return prevXor;
		else
			return 0; // Something went wrong returning the least value possible
	}
	if (rem == 0) // Whoa! You have to finish the taking process
		return prevXor;
	// Now me have a choice
	int ret = max(solve(pos + 1, rem, prevXor), solve(pos + 1, rem - 1, prevXor ^ a[pos]));
	// Take the element or not -- Choose the best
	return ret;
}

void solve()
{
	cin >> n >> k;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	cout << solve(0, k, 0) << '\n';
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