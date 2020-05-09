#include<bits/stdc++.h>
using namespace std;
int main()
{
	string str,div;
	cout<<"Enter msg to send: "<<endl;
	cin>>str;
	cout<<"Enter divisor string: "<<endl;
	cin>>div;
	for(int i=0;i<div.length()-1;i++)
		str+='0';
	int i;
	int red[div.length()]={0};
	for(i=0;i<div.length();i++)
		red[i]=str[i]-'0';
	//cout<<str<<endl;
	while(str[i]!='\0')
	{
		int k=0;
		for(int j=0;j<div.length();j++)
		{
			red[j]^=(div[j]-'0');
		}
		
	
		while(red[0]!=1 and str[i]!='\0')
		{
			rotate(red,red+1,red+div.length());
			red[div.length()-1]=str[i++]-'0';
		}
		cout<<"after"<<endl;
		for(int l=0;l<div.length();l++)
		cout<<red[l]<<" ";
		cout<<endl;
		
	}
	if(red[0]!=0)
	{for(int j=0; j<div.length();j++)
	{
		red[j]^=(div[j]-'0');
	}}
	for(int i=0;i<div.length();i++)
		cout<<red[i]<<" ";
	
}
