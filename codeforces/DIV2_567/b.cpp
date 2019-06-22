//Optimise
#include <bits/stdc++.h>

using namespace std;

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

string add(string one, string two)
{
	string ans = "";
	reverse(one.begin(), one.end());
	reverse(two.begin(), two.end());
	int sz = min(one.length(), two.length()), i;
	bool carry = false;
	for (i = 0; i < sz; ++i)
	{
		int t1 = one[i] - '0';
		int t2 = two[i] - '0';
		t1 += t2 + carry;
		if (carry)
			carry = false;
		if (t1 > 9)
		{
			t1 %= 10;
			carry = true;
		}
		ans += t1 + '0';
	}
	while (i < one.length())
	{
		int t = one[i] - '0';
		t += carry;
		carry = false;
		if (t > 9)
		{
			t %= 10;
			carry = true;
		}
		ans += t + '0';
		++i;
	}
	while (i < two.length())
	{
		int t = two[i] - '0';
		t += carry;
		carry = false;
		if (t > 9)
		{
			t %= 10;
			carry = true;
		}
		ans += t + '0';
		++i;
	}
	if (carry)
		ans += '1';
	reverse(ans.begin(), ans.end());
	return ans;
}

string maxi(string a, string b)
{
	if (a.length() == b.length())
	{
		for (int i = 0; i < a.length(); ++i)
		{
			if (a[i] < b[i])
				return a;
			if (a[i] > b[i])
				return b;
		}
		return a;
	}
	if (a.length() < b.length())
		return a;
	return b;
}

void solve()
{
	int n;
	cin >> n;
	string s, one, two;
	cin >> s;
	// cin >> one >> two;
	int k = n / 2;
	bool flag = true;
	// cout << add(one, two);
	string answer = s;
	for (int i = k; i < n - 1; ++i)
	{
		if (s[i + 1] == '0')
			continue;
		one = "";
		two = "";
		for (int j = 0; j <= i; ++j)
			one += s[j];
		for (int j = i + 1; j < n; ++j)
			two += s[j];
		one = add(one, two);
		answer = maxi(answer, one);
		if (flag)
			break;
		flag = true;
	}
	for (int i = k-1; i >= 0; --i)
	{
		if (s[i + 1] == '0')
			continue;
		one = "";
		two = "";
		for (int j = 0; j <= i; ++j)
			one += s[j];
		for (int j = i + 1; j < n; ++j)
			two += s[j];
		one = add(one, two);
		answer = maxi(answer, one);
		// if (flag)
			break;
		// flag = true;
	}
	cout << answer;
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