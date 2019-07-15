//Optimise
#include <bits/stdc++.h>
using namespace std;

// #define Online 1
// #define multitest 1
#define Debug 1
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

typedef pair<int, int> point;
typedef pair<point, point> ppi;

ll distx(ppi a, ppi b)
{
	return (a.f.f - b.f.f) * (a.f.f - b.f.f);
}

ll disty(ppi a, ppi b)
{
	return (a.f.s - b.f.s) * (a.f.s - b.f.s);
}

bool cmpy(ppi a, ppi b)
{
	if (a.f.s == b.f.s)
		return (a.f.f == b.f.f) ? (a.s < b.s) : (a.f.f < b.f.f);
	return a.f.s < b.f.s;
}

vector<ll> DandC(vector<ppi> &v, int start, int end)
{
	vector<ll> A;
	if (start >= end)
	{
		A.pb(1e18);
		A.pb(1);
		A.pb(1);
		A.pb(1);
		A.pb(1);
		return A;
	}
	int mid = (start + end) / 2;
	auto a1 = DandC(v, start, mid);
	auto a2 = DandC(v, mid + 1, end);
	if (a1[0] > a2[0])
		a1 = a2;
	ll d = a1[0];
	auto middle = v[mid];
	vector<ppi> S;
	for (int i = start; i <= end; ++i)
	{
		auto d1 = distx(middle, v[i]);
		if (d1 < d)
			S.pb(v[i]);
	}
	int n = S.size();
	sort(S.begin(), S.end(), cmpy);
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
		{
			auto a = S[i];
			auto b = S[j];
			ll y = disty(a, b);
			if (y > d)
				break;
			if (a.s.f == b.s.f)
				continue;
			ll x = distx(a, b);
			if ((x + y) < d)
			{
				d = x + y;
				a1[0] = d;
				a1[1] = a.s.f;
				a1[2] = a.s.s;
				a1[3] = b.s.f;
				a1[4] = b.s.s;
				switch (a1[4])
				{
				case 1:
					a1[4] = 4;
					break;
				case 2:
					a1[4] = 3;
					break;
				case 3:
					a1[4] = 2;
					break;
				case 4:
					a1[4] = 1;
					break;
				default:
					break;
				}
			}
		}
	return a1;
}

void solve()
{
	int n, x, y;
	cin >> n;
	vector<ppi> V;
	for (int i = 0; i < n; ++i)
	{
		cin >> x >> y;
		V.pb({{x, y}, {i + 1, 1}});
		V.pb({{-x, y}, {i + 1, 2}});
		V.pb({{x, -y}, {i + 1, 3}});
		V.pb({{-x, -y}, {i + 1, 4}});
	}
	sort(V.begin(), V.end());
	auto X = DandC(V, 0, V.size() - 1);
	// cout << X[0] << '\n';
	cout << X[1] << ' ' << X[2] << ' ' << X[3] << ' ' << X[4] << '\n';
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
	// cout << "\n\nTime elapsed: " << chrono::duration<double>(ElapsedTime).count() << " seconds.\n";
#endif
	return 0;
}