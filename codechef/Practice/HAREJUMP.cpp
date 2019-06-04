//Optimise
#include <bits/stdc++.h>
using namespace std;

#define Online 1
#define multitest 1
// #define Debug
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
#ifdef Debug
#define db(...) ZZ(#__VA_ARGS__, __VA_ARGS__)
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

typedef vector<ll> row;

struct matrix
{
	vector<row> MAT; 
	matrix()
	{
		MAT.resize(16);
		for(int i=0;i<16;++i)
		{
		 this->MAT[i].resize(16);
		 this->MAT[i][i] = 1;
		}		
	}
};

matrix mul(matrix &A,matrix &B)
{
	db("MUL start");
	matrix X ;
	for(int i=0;i<16;++i)
		for(int j=0;j<16;++j)
		{
			//db(i,j);
			X.MAT[i][j] = 0;
			for(int k=0;k<16;++k)
			{
			//	db(i,j,k);
				X.MAT[i][j] = (X.MAT[i][j] + A.MAT[i][k]*B.MAT[k][j])%mod;						
			}						
		}
	db("MUL END");
	return X;
}

matrix POWER(matrix &A,ll index)
{
	db("POWER",index);
	matrix temp;
	if(index == 0)
		return temp;
	temp = POWER(A,index/2);
	temp = mul(temp,temp );
	if(index&1) 
		return mul(temp,A);
	return temp;
}

void solve()
{
	ll n,k,x;
	cin >> n >> k;
	db("Start");
	matrix A;
	db("Init");
	A.MAT[0][0] = 0;
	for(int i=1;i<16;++i)
	{
		A.MAT[i][i] = 0;
		A.MAT[i][i-1] = 1;
	}
	db("Input");
	for(int i=1;i<=k;++i)
	{
		cin >> x;
		A.MAT[0][x-1]++;
	}
	db("Expo Start");	
	A = POWER(A,n);
	db("Expo End");	
	cout << A.MAT[0][0] << '\n';
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

void TimerStop()
{
#ifndef Online
	TimeEnd = chrono::steady_clock::now();
	auto ElapsedTime = TimeEnd - TimeStart;
	cout << "\n\nTime elapsed: " << chrono::duration<double>(ElapsedTime).count() << " seconds.\n";
#endif
}
