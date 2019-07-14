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
int dp[150][150];
int dp2[150][150];

bool solve()
{
	int n;
	cin >> n;
	if (n == 0)
		return false;
	set<string> insig;
	string s;
	for (int i = 0; i < n; ++i)
	{
		cin >> s;
		insig.insert(s);
	}
	while (true)
	{
		string acro;
		cin >> acro;
		cin.ignore();
		string phrase;
		getline(cin, phrase);
		if (phrase == "CASE")
			break;
		vector<string> words;
		istringstream iss(phrase);
		while (true)
		{
			iss >> s;
			if (s == "")
				break;
			if (insig.find(s) == insig.end())
			{
				words.pb(s);
			}
		}
		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;
		// dp[i][j] is the number of ways to use the first i words and the
		// first j letters of the acronym
		// https://github.com/t3nsor/SPOJ/blob/master/acmaker.cpp
		for (int i = 0; i < words.size(); ++i)
			for (int j = 0; j < acro.length(); ++j)
			{
				// How many letters of thits you want to use
				int mx = min(acro.length() - j, words[i].length());
				for (int k = 0; k <= words[i].length(); ++k)
					dp2[k][0] = 1;
				for (int k = 1; k <= mx; ++k)
					dp2[0][k] = 0;
				for (int k = 0; k < words[i].length(); ++k)
					for (int m = 0; m < mx; ++m)
					{
						dp2[k + 1][m + 1] = dp2[k][m + 1];
						if (words[i][k] = p = tolower(acro[j + m]))
							dp2[k + 1][m + 1] += dp2[k][m];
					}
				for (int k = 1; k <= mx; ++k)
					dp[i + 1][k + j] += dp[i][j] * dp2[words[i].length()][k];
			}
		if (dp[words.size()][acro.length()] == 0)
			cout << acro << " is not a valid abbreviation\n";
		else
			cout << acro << " can be formed in " << dp[words.size()][acro.length()] << " ways\n";
	}
	return true;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t = 1;
#ifdef multitest
	cin >> t;
#endif
	while (solve())
		;
#ifdef TIME
	cerr << "\n\nTime elapsed: " << chrono::duration<double>(chrono::steady_clock::now() - TimeStart).count() << " seconds.\n";
#endif
	return 0;
}