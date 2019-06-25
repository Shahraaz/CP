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

vector<int> T(1 << 19), A;

void init(int node, int start, int end)
{
	if (start == end)
	{
		T[node] = 1;
		return;
	}
	int mid = (start + end) / 2;
	int leftNode = node << 1, rightNode = leftNode | 1;
	init(leftNode, start, mid);
	init(rightNode, mid + 1, end);
	T[node] = T[leftNode] + T[rightNode];
}

int find(int node, int start, int end, int v)
{
	if (start == end)
		return start;
	int mid = (start + end) / 2;
	int leftNode = node << 1, rightNode = leftNode | 1;
	if (T[leftNode] >= v)
		return find(leftNode, start, mid, v);
	return find(rightNode, mid + 1, end, v - T[leftNode]);
}

void remove(int node, int start, int end, int p)
{
	if (start == end)
	{
		T[node] = 0;
		return;
	}
	int mid = (start + end) / 2;
	int leftNode = node << 1, rightNode = leftNode | 1;
	if (p <= mid)
		remove(leftNode, start, mid, p);
	else
		remove(rightNode, mid + 1, end, p);
	T[node] = T[leftNode] + T[rightNode];
}

void solve()
{
	int n;
	cin >> n;
	A.resize(n);
	for (int i = 0; i < n; ++i)
		cin >> A[i];
	init(1, 0, n - 1);
	stack<int> st;
	for (int i = n - 1; i >= 0; --i)
	{
		st.push(find(1, 0, n - 1, i + 1 - A[i]));
		remove(1, 0, n - 1, st.top());
	}
	while (!st.empty())
	{
		cout << st.top() + 1 << ' ';
		st.pop();
	}
	cout << '\n';
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