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
// #define f first
#define s second
#define pb push_back
const long long mod = 998244353;
auto TimeStart = chrono::steady_clock::now();

const int nax = 2e5 + 10, M = 3010;

ll mul(ll a, ll b)
{
	return a * b % mod;
}

ll add(ll a, ll b)
{
	a += b;
	if (a >= mod)
		a -= mod;
	return a;
}

ll power(ll base, int index)
{
	ll out = 1;
	while (index)
	{
		if (index & 1)
			out = mul(out, base);
		base = mul(base, base);
		index >>= 1;
	}
	return out;
}

ll n, m, a[nax], w[nax], f[M][M], g[M][M], inv[2 * M], sum[3];

ll inverse(ll base)
{
	return power(base, mod - 2);
}

void solve()
{
	// db("Here0");
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	// db("Here");
	for (int i = 1; i <= n; ++i)
	{
		cin >> w[i];
		sum[a[i]] += w[i];
		sum[2] += w[i];
	}
	// db("Here1");
	for (int i = max(0LL, m - sum[0]); i <= 2 * m; ++i)
		inv[i] = inverse(sum[2] + i - m);
	// db("Here2");
	for (int i = m; i >= 0; --i)
	{
		// db(i);
		f[i][m - i] = g[i][m - i] = 1;
		for (int j = min(m - i - 1, sum[0]); j >= 0; --j)
		{
			// db(j);
			f[i][j] = add(mul(sum[1] + i + 1, f[i + 1][j]), mul(sum[0] - j, f[i][j + 1]));
			f[i][j] = mul(f[i][j], inv[i - j + m]);
			g[i][j] = add(mul(sum[1] + i, g[i + 1][j]), mul(sum[0] - j - 1, g[i][j + 1]));
			g[i][j] = mul(g[i][j], inv[i - j + m]);
		}
	}
	// db("Here4");
	for (int i = 1; i <= n; ++i)
		cout << mul(w[i], a[i] ? f[0][0] : g[0][0]) << '\n';
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