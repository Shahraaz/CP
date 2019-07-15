#include<iostream>
#include<math.h>
using namespace std;

//polar class
class polarClass
{
public:
	float r,th;
	polarClass(){
	    //no need
	}
	polarClass(float a,float b)
	{
		r=a;
		th=b;
	}
	void show()
	{
		cout<<"In polar form:\n\t r="<<r<<" and theta="<<th;
		
	}
};

//rectangular class
class rectangularClass
{
float x,y;
public:
	rectangularClass(){
	    //no need
	}
	rectangularClass(polarClass p)
	{
		x=p.r*cos(p.th);
		y=p.r*sin(p.th);
	}
	void show()
	{
		cout<<"\n\t In Rectangular form :\n\tx="<<x<<"and y="<<y;
		
	}
};

int main()
{
polarClass p(1,4);
p.show();
rectangularClass r;
r=p;
r.show();

return 0;	
}