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

int mini(int a,int b)
{
	if(a<b) return a;
	return b;
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
	int n;
	cin >> n;
	string str,str1;
	vector<int> a,b,c,d;
	cin >> str;
	cin >> str1;
	for(int i=0;i<n;++i)
	{
		if(str[i]=='0' && str1[i]=='0')	a.pb(i+1);
		else if(str[i]=='1' && str1[i]=='0')	b.pb(i+1);
		else if(str[i]=='0' && str1[i]=='1')	c.pb(i+1);
		else if(str[i]=='1' && str1[i]=='1')	d.pb(i+1);
	}
	int s = c.size() + d.size() - n/2;
	int xcnt=0,ycnt=0,zcnt=0,wcnt=0;
	//cout << s << '\n';
	//cout << a.size() << ' ' << b.size() << ' ' << c.size() << ' ' << d.size() << '\n'; 
	{
		int currcnt = 0;
		if(s>0)
		{	//cout << "A\n";		
			if(d.size()<s)
			{
				cout << -1;
				return 0;		
			}
			while(currcnt!= n/2 && (s>wcnt))
			{
				wcnt++;
				currcnt++;
			}
			//cout << "Here" << wcnt << ' ' << s << '\n';
			if(wcnt!=s)
			{
				cout << -1;
				return 0;		
			}			
		}
		else
		{	//cout << "B\n";		
			if(a.size() < -s)
			{
				cout << -1;
				return 0;		
			}
			while(currcnt!= n/2 && (-s > xcnt))
			{
				xcnt++;
				currcnt++;
			}
			if(xcnt != -s)
			{
				cout << -1;
				return 0;		
			}			
		}
		while(currcnt!= n/2 && (xcnt<a.size() && (wcnt)<d.size()))
		{
			xcnt++;
			wcnt++;
			currcnt++;
			currcnt++;
		}
		while(currcnt!= n/2 && ycnt<b.size())
		{
			currcnt++;
			ycnt++;
		} 
		while(currcnt!= n/2 && zcnt<c.size())
		{
			currcnt++;
			zcnt++;
		}
		if(currcnt!=n/2)
			cout << -1;
		else
		{
//cout << xcnt << ' ' << ycnt << ' ' << zcnt << ' ' << wcnt << '\n';
			for(int i=0;i<wcnt;++i)
				cout << d[i] << ' ';	
			for(int i=0;i<xcnt;++i)
				cout << a[i] << ' ';
			for(int i=0;i<ycnt;++i)
				cout << b[i] << ' ' ;	
			for(int i=0;i<zcnt;++i)
				cout << c[i] << ' ' ;	
		} 
	}
  return 0;
}
