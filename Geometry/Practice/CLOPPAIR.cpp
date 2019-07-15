//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
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

typedef complex<ll> point;
typedef pair<point, int> ppi;

bool cmp(ppi a, ppi b)
{
	if (real(a.f) == real(b.f))
		return imag(a.f) < imag(b.f);
	return real(a.f) < real(b.f);
}

bool cmpy(ppi a, ppi b)
{
	if (imag(a.f) == imag(b.f))
		return real(a.f) < real(b.f);
	return imag(a.f) < imag(b.f);
}

pair<ll, pair<int, int>> findMinDist(vector<ppi> &V, int start, int end)
{
	if (start >= end)
		return {1e18, {start, start}};
	int mid = (start + end) / 2;
	auto d1 = findMinDist(V, start, mid);
	auto d2 = findMinDist(V, mid + 1, end);
	auto d = d1;
	if (d1.f < d2.f)
		d = d1;
	else
		d = d2;
	ll middle = real(V[mid].f);
	vector<ppi> v1;
	for (int i = start; i <= end; ++i)
	{
		auto x = middle - real(V[i].f);
		db(x * x, V[i].f);
		if (x * x < d.f)
			v1.pb(V[i]);
	}
	sort(v1.begin(), v1.end(), cmpy);
	int s = v1.size();
	for (int i = 0; i < s; ++i)
	{
		db(v1[i].f);
		for (int j = i + 1; j < s; ++j)
		{
			db(v1[i].f, v1[j].f, norm(v1[i].f - v1[j].f), d.f);
			if (norm(v1[i].f - v1[j].f) < d.f)
				d = {norm(v1[i].f - v1[j].f), {v1[i].s, v1[j].s}};
			if (imag(v1[i].f - v1[j].f) > d.f)
				break;
		}
	}
	db(start, end, d.f, d.s.f, d.s.s);
	return d;
}

void solve()
{
	int n, x, y;
	cin >> n;
	vector<ppi> V(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> x >> y;
		V[i].f = point(x, y);
		V[i].s = i;
	}
	sort(V.begin(), V.end(), cmp);
	// for (int i = 0; i < n; ++i)
	// 	db(i, V[i]);
	auto temp = findMinDist(V, 0, n - 1);
	cout << min(temp.s.f, temp.s.s) << ' ' << max(temp.s.f, temp.s.s) << ' ';
	cout << fixed << setprecision(6) << sqrtl(temp.f) << '\n';
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#ifndef Online
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	auto TimeStart = chrono::steady_clock::now();
	auto TimeEnd = chrono::steady_clock::now();
#endif
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (t--)
		solve();
#ifndef Online
	TimeEnd = chrono::steady_clock::now();
	auto ElapsedTime = TimeEnd - TimeStart;
	cout << "\n\nTime elapsed: " << chrono::duration<double>(ElapsedTime).count() << " seconds.\n";
#endif
	return 0;
}