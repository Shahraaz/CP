//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
#define multitest 1
typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
#define mp make_pair
const long long mod = 1000000007;
const long long High = 1e16;
void ControlIO();
void TimerStart();
void TimerStop();
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1> void ZZ(const char* name, Arg1&& arg1){std::cerr << name << " = " << arg1 << endl;}
template <typename Arg1, typename... Args>void ZZ(const char* names, Arg1&& arg1, Args&&... args)
{
	const char* comma = strchr(names + 1, ',');
	std::cerr.write(names, comma - names) << " = " << arg1;
	ZZ(comma, args...);
}

template <typename Arg>
class modint
{
	public:
	Arg num;
	int Mmod = 1000000007;
	modint ()
	{ 
		this->num = 0;
	}
	modint (Arg a)
	{
		a %= Mmod;
		if(a<0)
			a+=Mmod;
		this->num = a;
	}
	modint operator+(modint a)
	{
		modint temp;
		temp = *this;
		temp.num += a.num;
		if(temp.num > Mmod)
			temp.num -= Mmod;
		return temp;
	}
	modint operator-(modint a)
	{
		modint temp;
		temp = *this;
		temp.num -= a.num;
		if(temp.num < 0)
			temp.num += Mmod;
		return temp;
	}
	modint operator*(modint a)
	{
		modint temp;
		temp = *this;
		temp.num *= a.num;
		temp.num %= Mmod;
		return temp;
	}
	bool operator<(modint a)
	{
		return this->num < a.num; 
	}
	bool operator>(modint a)
	{
		return this->num > a.num; 
	}
	modint Power(modint a,int index)
	{
		if(index==0)
			return modint<Arg>(1);
		modint temp = Power(a,index/2);
		temp = temp*temp;
		if(index&1)
			temp = temp*a;
		return temp;
	}
};

typedef modint<ll> modll;
ll AP(vector<int> &A,int n)
{
	ll ans = (n+1);
	int max = A[0],min = A[0];
	for(int i=1;i<n;++i)
	{
		if(A[i]<min)
			min = A[i];
		if(A[i]>max)
			max = A[i];
	}
	int i;
	for(i=min-max;(i<=max-min); ++i)
	{
		vector<ll> Sum(max+1),Dp(n);
		for(int j=0;j<n;j++)
		{
			Dp[j] = 1;
			if(A[j] >= i+1 && (A[j] <= max + i))
				Dp[j] = Dp[j] + Sum[A[j] - i];
			ans = (ans + Dp[j] - 1)%mod;
			Sum[A[j]] = (Sum[A[j]] + Dp[j])%mod;
		}
	}
	return ans;
}

ll Power(ll a,int index)
{
	if(index==0)
		return 1;
	ll temp = Power(a,index/2);
	temp = (temp*temp)%mod;
	if(index&1)
		temp = (temp*a)%mod;
	return temp;
}

void solve()
{
	int n;
	cin >> n;
	vector<int> A(n);
	for(int i=0;i<n;++i)
		cin >> A[i];
	cout << (Power(2,n)-AP(A,n) + mod)%mod << '\n';
}

int main()
{
  ControlIO();
  int t = 1;
#ifdef multitest
  cin >> t;
#endif
	TimerStart();
  while (t--)
    solve();
	TimerStop();
  return 0;
}

void ControlIO()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
#ifndef Online
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
}

auto TimeStart = chrono::steady_clock::now();
auto TimeEnd = chrono::steady_clock::now();

void TimerStart()
{
	#ifndef Online
		TimeStart = chrono::steady_clock::now();
	#endif
}

void TimerStop() {
	#ifndef Online
		TimeEnd = chrono::steady_clock::now();
		auto ElapsedTime = TimeEnd - TimeStart;
		cout << "\n\nTime elapsed: " << chrono::duration<double>(ElapsedTime).count() << " seconds.\n";
	#endif
}
