#include<bits/stdc++.h>
#include<stdio.h> 
#include<string.h> 
#include<fcntl.h> 
#include<sys/stat.h> 
#include<sys/types.h> 
#include<unistd.h> 
#include<sys/ipc.h> 
#include<sys/msg.h> 
using namespace std;

struct mesg_buffer { 
	long mesg_type; 
	char mesg_text[100]; 
} message; 


int main(){
	
	key_t key;
	int msg_id;
	key = ftok("progfile",65);
	msg_id = msgget(key,0666 | IPC_CREAT);
	message.mesg_type = 1;	
	while(1){	

		
		string str,div;
		cout<<endl<<endl<<"~ ~ ~ ~ ~ ~ ~ ~ "<<endl<<endl;
		cout<<"Enter msg to send: "<<endl;
		cin>>str;
		div="1101";
	
	
		for(int i=0;i<div.length()-1;i++)
			str+='0';

		int i;
		int redundant[div.length()]={0};

		for(i=0;i<div.length();i++)
			redundant[i]=str[i]-'0';

		while(str[i]!='\0'){

			int k=0;
			for(int j=0;j<div.length();j++)
				redundant[j]^=(div[j]-'0');
	

			while(redundant[0]!=1 and str[i]!='\0'){
				rotate(redundant,redundant+1,redundant+div.length());
				redundant[div.length()-1]=(str[i++]-'0');
			}
		
		}	
		if(redundant[0]!=0)
			for(int j=0; j<div.length();j++)
				redundant[j]^=(div[j]-'0');	
	
		for(int i=0;i<div.length();i++)
			cout<<redundant[i]<<" ";
		cout<<endl;
	
		for(int i=0;i<div.length()-1;i++)
			str[str.length()-i-1]=redundant[div.length()-i-1]+'0';
	
		char send_msg[1000],send_div[1000];
		int x=0,y=0;

		for(int i=0;i<str.length();i++)
			send_msg[x++]=(char)str[i];

		for(int i=0;i<div.length();i++)
			send_div[y++]=(char)div[i];

		cout<<"-------------Sender Msg------"<<endl;
		for(int i=0;i<x;i++)
			cout<<send_msg[i];

		cout<<endl;
		cout<<"-------------Sender DIV------"<<endl;

		for(int i=0;i<y;i++)
			cout<<send_div[i];

		for(int i=0;i<x;i++){

			message.mesg_text[i] = send_msg[i];
		}
		message.mesg_text[x] = '\0';

		msgsnd(msg_id, &message, sizeof(message),0); 


		
	}

}
