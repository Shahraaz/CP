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

typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
const long long mod = 1000000007;
auto TimeStart = chrono::steady_clock::now();

int n, m;

void solve()
{
	cin >> n >> m;
	int len1, len2;
	len1 = len2 = 1;
	for (int a = 7; a < n; a *= 7)
		len1++;
	for (int b = 7; b < m; b *= 7)
		len2++;
	int ans = 0;
	if (len1 + len2 <= 7)
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
			{
				vector<int> Hash(7);
				for (int a = i, k = 0; k < len1; ++k, a /= 7)
					Hash[a % 7]++;
				for (int a = j, k = 0; k < len2; ++k, a /= 7)
					Hash[a % 7]++;
				if (*max_element(Hash.begin(), Hash.end()) <= 1)
					++ans;
			}
	cout << ans;
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