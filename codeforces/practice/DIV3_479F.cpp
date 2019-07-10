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
vector<int> a(nax);
vector<int> len(nax), pad(nax);
int n;

void solve()
{
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	map<int, int> NextIdx;
	int answeridx = 0, answerlen = -1;
	for (int i = n; i > 0; --i)
	{
		int num = a[i] + 1;
		auto it = NextIdx.find(num);
		if (it != NextIdx.end())
		{
			int idx = it->s;
			len[i] = len[idx] + 1;
			pad[i] = idx;
		}
		else
		{
			len[i] = 1;
			pad[i] = 0;
		}
		db(i, a[i], len[i], pad[i]);
		NextIdx[a[i]] = i;
		if (answerlen < len[i])
		{
			answerlen = len[i];
			answeridx = i;
		}
	}
	cout << answerlen << '\n';
	while (answeridx != 0)
	{
		db(a[answeridx]);
		cout << answeridx << ' ';
		answeridx = pad[answeridx];
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