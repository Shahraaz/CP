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
	ll a, b;
	cin >> a >> b;
	string one = to_string(a);
	string two = to_string(b);
	vector<int> Hash(10);
	for (auto c : one)
		Hash[c - '0']++;
	bool gone = false;
	if (two.length() > one.length())
	{
		sort(one.rbegin(), one.rend());
		cout << one << '\n';
		return;
	}
	for (auto c : two)
	{
		db(c);
		int j = c - '0';
		if (Hash[j] == 0)
		{

			while (Hash[j] == 0)
				--j;
			// db("Priting Buffer");
			cout << j;
			Hash[j]--;
			for (int i = 9; i >= 0; --i)
				while (Hash[i])
				{
					Hash[i]--;
					cout << i;
				}
			return;
		}
		cout << j;
		Hash[j]--;
		// db("\n");
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
	cout << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}