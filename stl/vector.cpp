#include<bits/stdc++.h>
using namespace std;
#define Tie ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define int long long
int T,n,m,t;
int year[146097];
int mouth[146097];
int day[146097];
int pd(int year,int mouth)
{
	if(mouth==1)
		return 31;
	if(mouth==2)
		if(year%4==0&&year%100!=0||year%400==0)
			return 29;
	else
		return 28;
	if(mouth==3)
		return 31;
	if(mouth==4)
		return 30;
	if(mouth==5)
		return 31;
	if(mouth==6)
		return 30;
	if(mouth==7)
		return 31;
	if(mouth==8)
		return 31;
	if(mouth==9)
		return 30;
	if(mouth==10)
		return 31;
	if(mouth==11)
		return 30;
	if(mouth==12)
		return 31;
}
signed main()
{
	Tie;
	mouth[0]=day[0]=1;
	for(int i=1;i<146097;i++)
	{
		day[i]=day[i-1]+1;
		mouth[i]=mouth[i-1];
		year[i]=year[i-1];
		if(day[i]>pd(year[i],mouth[i]))
			mouth[i]++,day[i]=1;
		if(mouth[i]>12)
			year[i]++,mouth[i]=1;
	}
	cin>>T;
	while(T--)
	{
		cin>>n;
		if(n>2299160)
		{
			n-=2159351;
			t=n/146097*400+1200;
			n%=146097;
		}
		else
		{
			t=n/1461*4-4712;
			n%=1461;
		}
		if(t+year[n]>0)
			cout<<day[n]<<' '<<mouth[n]<<' '<<t+year[n]<<'\n';
		else
			cout<<day[n]<<' '<<mouth[n]<<' '<<1-t-year[n]<<" BC\n"; 
	}
}
