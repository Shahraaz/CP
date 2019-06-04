#include<bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
typedef pair<string,pii> psii;
map<char,int> M;

int Skew(string str)
{
	int v = 0;
	for(ch : str)
		v += abs(M[ch]-M['z']);
	return v;
}

bool CmpP(psii a,psii b)
{
if( b.f.length()*(long long)a.s.s == a.f.length()*(long long)b.s.s)
	return a.f.length() > b.f.length();
return b.f.length()*(long long)a.s.s > a.f.length()*(long long)b.s.s;

}

bool CmpT(psii a,psii b)
{
if( b.f.length()*(long long)a.s.s == a.f.length()*(long long)b.s.s)
	return a.f.length() > b.f.length();
return b.f.length()*(long long)a.s.s < a.f.length()*(long long)b.s.s;

}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int i,n,m,a,x,r;
	for(i=0;i<26;++i) M[char('a'+i)]  = i;
	for(i=0;i<26;++i) M[char('A'+i)] = 26+i;
	cin >> n >> m >> a >> x >> r;
	string MELODY ;
	cin >> MELODY;
	vector<psii> T;
	for(int i=0;i<m;++i)
	{
		string str;
		int x;
		cin >> str >> x;
		if(x>0)
			T.pb(mp(str,mp(x,x+Skew(str))));
	}
	vector<psii> P;
	for(int i=0;i<a;++i)
	{
		string str;
		int x;
		cin >> str >> x;
		P.pb(mp(str,mp(x,x+Skew(str))));
	}
	sort(T.begin(),T.end(),CmpT);
	sort(P.begin(),P.end(),CmpP);
	string Buffer;
	int BufferStart,BufferEnd,MelodyStart;
	
	return 0;
}
