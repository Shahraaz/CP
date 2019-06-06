//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
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

// vector<ll> Sum;
// int _n;
// void Sum_Pre(vector<int> &v)
// {
// 	_n = v.size();
// 	Sum.resize(_n);
// 	Sum[0] = v[0];
// 	for (int i = 1; i < _n; ++i)
// 		Sum[i] = Sum[i - 1] + v[i];
// }

// ll rangesum(int start, int end)
// {
// 	if (start == 0)
// 		return Sum[end];
// 	return Sum[end] - Sum[start - 1];
// }

struct trie
{
	trie *next[26];
	// bool isLeaf;
	trie()
	{
		// isLeaf = false;
		for (int i = 0; i < 26; ++i)
			next[i] = NULL;
		// fill(next,next+26,NULL);
		// memset(next, NULL, sizeof next);
	}
};

string str, s;
int k, ans;
void insert(char *ps, trie *ob, int ct)
{
	if (ps[0] == '\0')
		return;
	if (s[ps[0] - 'a'] == '0')
		ct++;
	if (ct > k)
		return;
	if (ob->next[ps[0] - 'a'] == NULL)
		ob->next[ps[0] - 'a'] = new trie();
	insert(ps + 1, ob->next[ps[0] - 'a'], ct);
	// insert(ps + 1, ob->next[ps[0] - 'a']);
	// if (lev == len)
	// {
	// 	if (!ob->isLeaf)
	// 		ans++;
	// 	ob->isLeaf = true;
	// 	return;
	// }
	// if (s[str[lev] - 'a'] == '0')
	// 	count++;
	// if (count > k)
	// 	return;
	// if (ob->next[str[lev] - 'a'] == NULL)
	// 	ob->next[str[lev] - 'a'] = new trie();
}

void traverse(trie *t)
{
	if (t == NULL)
		return;
	ans++;
	// cout << s << '\n';
	for (int i = 0; i < 26; ++i)
	{
		// s.push_back(i + 'a');
		traverse(t->next[i]);
		// s.pop_back();
	}
}

void solve()
{
	cin >> str >> s >> k;
	int n = str.size();
	vector<int> ToPass(n);
	// for (int i = 0; i < n; ++i)
	// 	ToPass[i] = (s[str[i] - 'a'] == '0');
	// Sum_Pre(ToPass);
	trie *t = new trie();
	char sec[n + 1];
	strcpy(sec, str.c_str());
	sec[n] = '\0';
	for (int i = 0; i < n; ++i)
		insert(sec + i, t, 0);
	// insert(t, i, n, 0);
	// for (int j = i; j < n; ++j)
	// {
	// 	// int x = rangesum(i, j);
	// 	// db(x, i, j);
	// 	// if (x <= k)
	// 	{
	// 		// cout << i << ' ' << j << '\n';
	// 		// db(i, j);
	// 		char a = str[j + 1];
	// 		sec[j + 1] = '\0';
	// 		// cout << sec + i << '\n';
	// 		sec[j + 1] = a;
	// 	}
	// 	else
	// 		break;
	// }
	traverse(t);
	cout << ans - 1 << '\n';
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