#include<bits/stdc++.h>
using namespace std;
bool check_Parity(string s){
	int count = 0;
	for(int i=0;i<s.size()-1;i++){
		if(s[i] == '1')
			count++;	
	}	
	int tt = s[s.size()-1]-48;
	if(count%2 == tt)
		return true;
	return false;
}

int main(){
	string s;
	cin>>s;	
	if(check_Parity(s))
		cout<<"Correct Message Recieved"<<endl;
	else
		cout<<"InCorrect Message Recieved"<<endl<<"Promt Sender to resend the message"<<endl;
}
