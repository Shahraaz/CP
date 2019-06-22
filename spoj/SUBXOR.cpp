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
	int lc, rc;
	Trie *left, *right;
	Trie()
	{
		lc = rc = 0;
		left = right = NULL;
	}
};

int maxBits = 20;

Trie *insert(Trie *curr, int level, int N)
{
	if (level == -1)
		return curr;
	int b = N & (1 << level);
	if (b)
	{
		curr->rc++;
		if (curr->right == NULL)
			curr->right = new Trie;
		curr->right = insert(curr->right, level - 1, N);
	}
	else
	{
		curr->lc++;
		if (curr->left == NULL)
			curr->left = new Trie;
		curr->left = insert(curr->left, level - 1, N);
	}
	return curr;
}

int query(Trie *curr, int level, int N, int K)
{
	if (level == -1 || curr == NULL)
		return 0;
	bool bitN = N & (1 << level);
	bool bitK = K & (1 << level);
	if (bitK)
	{
		if (bitN)
			return curr->rc + query(curr->left, level - 1, N, K);
		else
			return curr->lc + query(curr->right, level - 1, N, K);
	}
	else
	{
		if (bitN)
			return query(curr->right, level - 1, N, K);
		else
			return query(curr->left, level - 1, N, K);
	}
}

void solve()
{
	int x, n, k;
	cin >> n >> k;
	int p;
	p = 0;
	ll ans = 0;
	Trie *root = new Trie;
	root = insert(root, maxBits, 0);
	for (int i = 0; i < n; ++i)
	{
		cin >> x;
		p = p ^ x;
		ans += query(root, maxBits, p, k);
		root = insert(root, maxBits, p);
	}
	cout << ans << '\n';
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