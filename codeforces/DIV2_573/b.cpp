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
	vector<string> S(3);
	cin >> S[0] >> S[1] >> S[2];
	sort(S.begin(), S.end());
	int a = 0, b = 0, c = 0;
	for (int i = 0; i < 3; ++i)
		a += S[i] == S[0];
	for (int i = 0; i < 3; ++i)
		b += S[i] == S[1];
	for (int i = 0; i < 3; ++i)
		c += S[i] == S[2];
	int ans1 = 2;
	ans1 = min(ans1, 3 - a);
	ans1 = min(ans1, 3 - b);
	ans1 = min(ans1, 3 - c);
	// db(S[0], S[1], S[2]);
	if ((S[1][0] == (1 + S[0][0])) && S[0][1] == S[1][1])
	{
		// db("Hrer")
		ans1 = min(ans1, 1);
		if ((S[2][0] == (1 + S[1][0])) && S[1][1] == S[2][1])
		{
			// db("Hrer1")
			ans1 = min(ans1, 0);
		}
	}
	if ((S[1][0] == (2 + S[0][0])) && S[0][1] == S[1][1])
	{
		// db("Hrer2")
		ans1 = min(ans1, 1);
	}
	if ((S[2][0] == (1 + S[1][0])) && S[1][1] == S[2][1])
	{
		// db("Hrer2")
		ans1 = min(ans1, 1);
	}
	if ((S[2][0] == (2 + S[1][0])) && S[1][1] == S[2][1])
	{
		// db("Hrer2")
		ans1 = min(ans1, 1);
	}
	if ((S[2][0] == (1 + S[0][0])) && S[0][1] == S[2][1])
	{
		// db("Hrer2")
		ans1 = min(ans1, 1);
	}
	if ((S[2][0] == (2 + S[0][0])) && S[0][1] == S[2][1])
	{
		// db("Hrer2")
		ans1 = min(ans1, 1);
	}
	cout << ans1;
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