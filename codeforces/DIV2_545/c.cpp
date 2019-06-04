//Optimise
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
#define f first
#define s second
#define pb push_back
#define mp make_pair
const long long mod = 1000000007;
const long long High = 1e16;

int lis(vector<int> arr,int n)
{
//	cout  << "LIS\n";
	int max = 1,len = 1;
	for(int i=1;i<n;++i)
	{
		if(arr[i]>arr[i-1])	len++;
		else if(arr[i]==arr[i-1]);
		else 
		{
			if(max<len) max = len;
			len = 1;
		}
		if(max<len) max = len;
	} 
	return max;
}
int lisrev(vector<int> arr,int n)
{
	int max = 1,len = 1;
	for(int i=1;i<n;++i)
	{
		if(arr[i]<arr[i-1])	len++;
		else if(arr[i]==arr[i-1]);
		else 
		{
			if(max<len) max = len;
			len = 1;
		}
		if(max<len) max = len;
	} 
	return max;
}

int main()
{
//  ios_base::sync_with_stdio(0);
//  cin.tie(0);
	int n,m;
	cin >> n >> m;
	vector<vector<int>> Vect(n,vector<int>(m));
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j)
			cin >> Vect[i][j];
	vector<int> H(n),V(m);
	for(int i=0;i<n;++i)
		H[i] = max(lis(Vect[i],m),lisrev(Vect[i],m));
	for(int i=0;i<m;++i)
	{
		vector<int> Vi(n);
		for(int j=0;j<n;++j)
			Vi[j] = Vect[j][i];
		V[i] = max(lis(Vi,n),lisrev(Vi,n));
	}
	//cout << "Compute\m";
	for(int i=0;i<n;++i)
	{	
		for(int j=0;j<m;++j)
		{
			int ans = max(H[i],V[j]);
			int lei,led,lwi,lwd,lni,lnd,lsi,lsd;
			lei=led=lwi=lwd=lni=lnd=lsi=lsd=1;
			for(int i1=i-1;i1>=0;--i1)
			{
				if(Vect[i1][j]>=Vect[i1+1][j])
					lei++;
				else break;
				if(Vect[i1][j]==Vect[i1+1][j])
					lei--;
			}
			for(int i1=i-1;i1>=0;--i1)
			{
				if(Vect[i1][j]<=Vect[i1+1][j])
					led++;
				else break;
				if(Vect[i1][j]==Vect[i1+1][j])
					led--;
			}
			for(int i1=i+1;i1<n;++i1)
			{
				if(Vect[i1][j]==Vect[i1-1][j])
					lwi--;
				if(Vect[i1][j]>=Vect[i1-1][j])
					lwi++;
				else break;
			}
			for(int i1=i+1;i1<n;++i1)
			{
				if(Vect[i1][j]==Vect[i1-1][j])
					lwd--;
				if(Vect[i1][j]<=Vect[i1-1][j])
					lwd++;
				else break;
			}
////////////////////////////////////////////////////////////////////////////
			for(int i1=j-1;i1>=0;--i1)
			{
				if(Vect[i][i1]==Vect[i][i1+1])
					lni--;
				if(Vect[i][i1]>=Vect[i][i1+1])
					lni++;
				else break;
			}
			for(int i1=j-1;i1>=0;--i1)
			{
				if(Vect[i][i1]==Vect[i][i1+1])
					lnd--;
				if(Vect[i][i1]<=Vect[i][i1+1])
					lnd++;
				else break;
			}
			for(int i1=j+1;i1<m;++i1)
			{
				if(Vect[i][i1]==Vect[i][i1-1])
					lsi--;
				if(Vect[i][i1]>=Vect[i][i1-1])
					lsi++;
				else break;
			}
			for(int i1=j+1;i1<m;++i1)
			{
				if(Vect[i][i1]==Vect[i][i1-1])
					lsd--;
				if(Vect[i][i1]<=Vect[i][i1-1])
					lsd++;
				else break;
			}
			ans = max(ans,lei+lnd-1);	
			ans = max(ans,lei+lwd-1);	
			ans = max(ans,lei+lsd-1);	
			ans = max(ans,lwi+lnd-1);	
			ans = max(ans,lwi+led-1);	
			ans = max(ans,lwi+lsd-1);	
			ans = max(ans,lni+led-1);	
			ans = max(ans,lni+lwd-1);	
			ans = max(ans,lni+lsd-1);	
			ans = max(ans,lsi+lnd-1);	
			ans = max(ans,lsi+lwd-1);	
			ans = max(ans,lsi+led-1);
			cout << ans << ' ';	
		}
		cout << '\n';
	}
  return 0;
}
