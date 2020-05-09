#include<bits/stdc++.h>
using namespace std;
char check_Parity(string s){
	int count = 0;
	for(int i=0;i<s.size();i++){
		if(s[i] == '1')
			count++;	
	}	
	if(count%2)
		return '1';
	return '0';
}

int main(){
	string s;
	cin>>s;	
	char check = check_Parity(s);
	s = s + check;
	cout<<s<<endl;
}
