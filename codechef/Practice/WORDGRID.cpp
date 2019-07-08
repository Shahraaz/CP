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

vector<string> input;

bool isLegit;
vector<string> answer(4);

bool placeitThere(char &a, char &b, char &c, char &d, string &str)
{
	if (a == '*' && str[0] == '*')
		;
	else if (str[0] == '*')
		;
	else if (a == '*')
		a = str[0];
	else if (a != str[0])
		return false;

	if (b == '*' && str[1] == '*')
		;
	else if (str[1] == '*')
		;
	else if (b == '*')
		b = str[1];
	else if (b != str[1])
		return false;

	if (c == '*' && str[2] == '*')
		;
	else if (str[2] == '*')
		;
	else if (c == '*')
		c = str[2];
	else if (c != str[2])
		return false;

	if (d == '*' && str[3] == '*')
		;
	else if (str[3] == '*')
		;
	else if (d == '*')
		d = str[3];
	else if (d != str[3])
		return false;

	return true;
}

bool makeGrid(int i, int n, vector<string> &grid)
{
	// db(i, n);
	// db(grid[0]);
	// db(grid[1]);
	// db(grid[2]);
	// db(grid[3]);
	auto &x = grid;
	if (i == n)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
				if (grid[i][j] == '*')
					grid[i][j] = 'A';
		}
		if (!isLegit)
		{
			isLegit = true;
			answer = grid;
		}
		else
		{
			if (grid[0] < answer[0])
				answer = grid;
			else if (grid[0] == answer[0])
			{
				if (grid[1] < answer[1])
					answer = grid;
				else if (grid[1] == answer[1])
				{
					if (grid[2] < answer[2])
						answer = grid;
					else if (grid[2] == answer[2])
					{
						if (grid[3] < answer[3])
							answer = grid;
					}
				}
			}
		}
		return false;
	}
	bool try1;
	char a, b, c, d;
	switch (i)
	{
	case 0:
		a = grid[0][0];
		b = grid[0][1];
		c = grid[0][2];
		d = grid[0][3];
		try1 = placeitThere(grid[0][0], grid[0][1], grid[0][2], grid[0][3], input[0]);
		if (try1 && makeGrid(i + 1, n, grid))
			return true;
		grid[0][0] = a;
		grid[0][1] = b;
		grid[0][2] = c;
		grid[0][3] = d;
		a = grid[0][3];
		b = grid[0][2];
		c = grid[0][1];
		d = grid[0][0];
		try1 = placeitThere(grid[0][3], x[0][2], x[0][1], x[0][0], input[0]);
		if (try1 && makeGrid(i + 1, n, x))
			return true;
		grid[0][3] = a;
		grid[0][2] = b;
		grid[0][1] = c;
		grid[0][0] = d;
		break;

	case 1:
		a = grid[1][0];
		b = grid[1][1];
		c = grid[1][2];
		d = grid[1][3];
		try1 = placeitThere(grid[1][0], grid[1][1], grid[1][2], grid[1][3], input[1]);
		if (try1 && makeGrid(i + 1, n, grid))
			return true;
		grid[1][0] = a;
		grid[1][1] = b;
		grid[1][2] = c;
		grid[1][3] = d;
		a = grid[1][3];
		b = grid[1][2];
		c = grid[1][1];
		d = grid[1][0];
		try1 = placeitThere(x[1][3], x[1][2], x[1][1], x[1][0], input[1]);
		if (try1 && makeGrid(i + 1, n, x))
			return true;
		grid[1][3] = a;
		grid[1][2] = b;
		grid[1][1] = c;
		grid[1][0] = d;
		break;

	case 2:
		try1 = placeitThere(grid[2][0], grid[2][1], grid[2][2], grid[2][3], input[2]);
		if (try1 && makeGrid(i + 1, n, grid))
			return true;
		try1 = placeitThere(x[2][3], x[2][2], x[2][1], x[2][0], input[2]);
		if (try1 && makeGrid(i + 1, n, x))
			return true;
		break;

	case 3:
		try1 = placeitThere(grid[3][0], grid[3][1], grid[3][2], grid[3][3], input[3]);
		if (try1 && makeGrid(i + 1, n, grid))
			return true;
		try1 = placeitThere(x[3][3], x[3][2], x[3][1], x[3][0], input[3]);
		if (try1 && makeGrid(i + 1, n, x))
			return true;
		break;

	case 4:
		try1 = placeitThere(grid[0][0], grid[1][0], grid[2][0], grid[3][0], input[4]);
		if (try1 && makeGrid(i + 1, n, grid))
			return true;
		try1 = placeitThere(x[3][0], x[2][0], x[1][0], x[0][0], input[4]);
		if (try1 && makeGrid(i + 1, n, x))
			return true;
		break;

	case 5:
		try1 = placeitThere(grid[0][0], grid[1][1], grid[2][2], grid[3][3], input[i]);
		if (try1 && makeGrid(i + 1, n, grid))
			return true;
		try1 = placeitThere(x[3][3], x[2][2], x[1][1], x[0][0], input[i]);
		if (try1 && makeGrid(i + 1, n, x))
			return true;
		break;

	case 6:
		try1 = placeitThere(grid[0][1], grid[1][1], grid[2][1], grid[3][1], input[i]);
		if (try1 && makeGrid(i + 1, n, grid))
			return true;
		try1 = placeitThere(x[3][1], x[2][1], x[1][1], x[0][1], input[i]);
		if (try1 && makeGrid(i + 1, n, x))
			return true;
		break;

	case 7:
		try1 = placeitThere(grid[0][2], grid[1][2], grid[2][2], grid[3][2], input[i]);
		if (try1 && makeGrid(i + 1, n, grid))
			return true;
		try1 = placeitThere(x[3][2], x[2][2], x[1][2], x[0][2], input[i]);
		if (try1 && makeGrid(i + 1, n, x))
			return true;
		break;

	case 8:
		try1 = placeitThere(grid[0][3], grid[1][2], grid[2][1], grid[3][0], input[i]);
		if (try1 && makeGrid(i + 1, n, grid))
			return true;
		try1 = placeitThere(x[3][0], x[1][2], x[2][1], x[0][3], input[i]);
		if (try1 && makeGrid(i + 1, n, x))
			return true;
		break;

	case 9:
		try1 = placeitThere(grid[0][3], grid[1][3], grid[2][3], grid[3][3], input[i]);
		if (try1 && makeGrid(i + 1, n, grid))
			return true;
		try1 = placeitThere(x[3][3], x[2][3], x[1][3], x[0][3], input[i]);
		if (try1 && makeGrid(i + 1, n, x))
			return true;
		break;

	default:
		break;
	}
	return false;
}

void solve()
{
	input.clear();
	int n;
	cin >> n;
	set<string> S;
	string s;
	for (int i = 0; i < n; ++i)
	{
		cin >> s;
		if (S.count(s))
			continue;
		auto rev = s;
		reverse(s.begin(), s.end());
		if (S.count(s))
			continue;
		s = min(s, rev);
		input.pb(s);
		S.insert(s);
	}
	if (input.size() > 10)
	{
		db("One");
		cout << "grid\nsnot\nposs\nible\n\n";
		return;
	}
	while (input.size() < 10)
		input.pb("****");
	sort(input.begin(), input.end());
	vector<string> grid(4);
	isLegit = false;
	do
	{
		grid[0] = "****";
		grid[1] = "****";
		grid[2] = "****";
		grid[3] = "****";
		makeGrid(0, input.size(), grid);
	} while (next_permutation(input.begin(), input.end()));
	db("Two");
	if (isLegit)
	{
		cout << answer[0] << '\n';
		cout << answer[1] << '\n';
		cout << answer[2] << '\n';
		cout << answer[3] << '\n'
			 << '\n';
	}
	else
		cout << "grid\nsnot\nposs\nible\n\n";
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
	// auto start = chrono::steady_clock::now();
	while (t--)
	{
		// auto s1 = chrono::steady_clock::now();
		solve();
		// auto diff = chrono::steady_clock::now() - s1;
		// db(chrono::duration_cast<chrono::milliseconds>(diff).count());
	}
	// auto diff = chrono::steady_clock::now() - start;
	// db(chrono::duration_cast<chrono::millseconds>(diff).count());
	return 0;
}