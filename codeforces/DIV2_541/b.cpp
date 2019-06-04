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
//  ios_base::sync_with_stdio(0);
//  cin.tie(0);
  int n,x,y,xprev,yprev;
  xprev = yprev = 0;
  cin >> n;
  ll cnt = 1;
  while(n--)
  {
    cin >> x >> y;
    if(xprev==yprev)
    {
      cnt += min(x,y) - xprev;
    }
    else if(xprev<yprev)
    {
      if(x==yprev)
      {
        cnt++;
        //cout << "1++\n";
      }
      if(x>yprev)
      {
        if(x<=y)
        {
          //cout << "2x - yprev\n";
          cnt += x - yprev + 1;  
        }
        else{
          //cout << "3y - yprev\n";
         cnt += y - yprev + 1;
       }
      }
    }
    else
    {
      if(y==xprev)
      {
        cnt++;
        //cout << "4++\n";
      }
      if(y>xprev)
      {
        if(y<=x)
        {
          //cout << "5y - xprev\n";
          cnt += y - xprev + 1;  
        }
        else{
          //cout << "6x - xprev\n";       
         cnt += x - xprev + 1;
       }
      }
    }
    //cout << cnt << '\n';
    xprev = x; 
    yprev = y;
  }
  cout << cnt;
  return 0;
}