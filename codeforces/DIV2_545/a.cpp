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

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
	int n;
	cin >> n;
	vector<int> Vect(n);
	for(int i=0;i<n;++i)
		cin >> Vect[i];
	int ans = 0,cnt1 = 0,cnt2 = 0,p1=0,p2=0;
	int curr = -1;
	for(int i=0;i < n;++i)
	{
		if(Vect[i]==curr)
		{
			if(Vect[i]==1)
			{	
				cnt1++;
				ans = max(ans,min(cnt1,p2));
			}
			else
			{	
				cnt2++;
				ans = max(ans,min(cnt2,p1));
			}
		}
		else
		{
			if(Vect[i]==1)
			{
				cnt1 = curr = 1;
				p2 = cnt2;			
			}
			else
			{
				curr = 2;
				cnt2 = 1;	
				p1 = cnt1;		
			}
		}		
	}
	if(ans==0)	cout << 2;
	else cout << 2*ans;
  return 0;
}
