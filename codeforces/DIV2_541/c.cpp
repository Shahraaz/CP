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
  queue<int> Q;
  stack<int> S;
  ll n;
  cin >> n;
  vector<ll> Vect(n);
  for(int i=0;i<n;i++)
  	cin >> Vect[i];
  sort(Vect.begin(),Vect.end());
  for(int i=0;i<n;++i)
  {
  	if(i&1)
  		Q.push(Vect[i]);
  	else S.push(Vect[i]);
  }
  while(!S.empty())
  {
  	cout << S.top() << ' ';
  	S.pop();
  }
  while(!Q.empty())
  {
  	cout << Q.front() << ' ';
  	Q.pop();
  }
  return 0;
}