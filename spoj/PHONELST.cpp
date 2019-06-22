//Optimise
#include <bits/stdc++.h>
using namespace std;

#define multitest 1
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

struct Trie
{
	bool wordEndsHere;
	Trie *child[10];
	Trie()
	{
		wordEndsHere = false;
		for (int i = 0; i < 10; ++i)
			child[i] = nullptr;
	}
};

bool flag;
Trie *insert(Trie *root, string s)
{
	if (root == nullptr)
		root = new Trie;
	auto curr = root;
	if (curr->child[s[0] - '0'] == nullptr)
		curr->child[s[0] - '0'] = new Trie;

	for (int i = 0; i < s.length(); ++i)
	{
		int dig = s[i] - '0';
		if (curr->wordEndsHere)
			flag = false;
		if (curr->child[dig] == nullptr)
			curr->child[dig] = new Trie;
		curr = curr->child[dig];
	}
	curr->wordEndsHere = true;
	for (int i = 0; i < 10; ++i)
		if (curr->child[i] != nullptr)
			flag = false;
	return root;
}

void solve()
{
	int n;
	cin >> n;
	string s;
	Trie *root = nullptr;
	flag = true;
	while (n--)
	{
		cin >> s;
		root = insert(root, s);
	}
	if (flag)
		cout << "YES\n";
	else
		cout << "NO\n";
}

int main()
{
#ifndef Debug
	ios_base::sync_with_stdio(0);
	cin.tie(0);
#endif
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (t--)
		solve();
	return 0;
}