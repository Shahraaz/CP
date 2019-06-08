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

int n, m;
vector<int> a, b;

int score(vector<int> &v, int d)
{
	int n = v.size();
	int lessOrEqualD = upper_bound(v.begin(), v.end(), d) - v.begin();
	int grearThanD = n - lessOrEqualD;
	return lessOrEqualD * 2 + grearThanD * 3;
}

void solve()
{
	cin >> n;
	a.resize(n);
	for (auto &x : a)
		cin >> x;
	cin >> m;
	b.resize(m);
	for (auto &x : b)
		cin >> x;
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	int aAnswer = -mod, bAnswer = mod;
	for (int i = 0; i < n; ++i)
	{
		int a1 = score(a, a[i] - 1);
		int b1 = score(b, a[i] - 1);
		if ((a1 - b1) >= (aAnswer - bAnswer))
			if ((a1 - b1) == (aAnswer - bAnswer))
			{
				if (aAnswer < a1)
				{
					aAnswer = a1;
					bAnswer = b1;
				}
			}
			else
			{
				aAnswer = a1;
				bAnswer = b1;
			}
		db(i, aAnswer, bAnswer, a1, b1);
	}
	for (int i = 0; i < m; ++i)
	{
		int a1 = score(a, b[i] + 1);
		int b1 = score(b, b[i] + 1);
		if ((a1 - b1) >= (aAnswer - bAnswer))
			if ((a1 - b1) == (aAnswer - bAnswer))
			{
				if (aAnswer < a1)
				{
					aAnswer = a1;
					bAnswer = b1;
				}
			}
			else
			{
				aAnswer = a1;
				bAnswer = b1;
			}
		db(i, aAnswer, bAnswer, a1, b1);
	}
	cout << aAnswer << ':' << bAnswer << '\n';
	db("ou");
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