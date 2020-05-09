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
	int msgid;
	key = ftok("progfile",65);
	msgid = msgget(key,0666 | IPC_CREAT);
  
	
	while(1){

		char recieve_msg[1000];
		msgrcv(msgid, &message, sizeof(message), 1, 0); 
	       	//msgrcv(msgid, received_data, sizeof(received_data),1,0); 
		for(int i=0;message.mesg_text[i]!='\0';i++){
			recieve_msg[i] = message.mesg_text[i];
		}
		char recieve_div[4] = {'1','1','0','1'};

		
	
		int l=strlen(recieve_msg)-1;
		
		cout<<endl<<"****Received Data****"<<l<<endl<<endl;
		for(int i=0;i<l;i++){
			cout<<recieve_msg[i]<<"  ";		
	
		}

		char receive_div[] = {'1','1','0','1'};
		
		int i;
		int redundant[strlen(recieve_div)]={0};

		for(i=0;i<strlen(recieve_div);i++)
			redundant[i]=recieve_msg[i]-'0';
		
		while(i!=l)
		{
			int k=0;
			for(int j=0;j<strlen(recieve_div);j++)
				redundant[j]^=(recieve_div[j]-'0');
		
	
			while(redundant[0]!=1 and i!=l){
				rotate(redundant,redundant+1,redundant+strlen(recieve_div));
				redundant[strlen(recieve_div)-1]=(recieve_msg[i++]-'0');
			}
			
		
		}
		if(redundant[0]!=0)
			for(int j=0; j<strlen(recieve_div);j++)
				redundant[j]^=(recieve_div[j]-'0');
		
		
		bool flag=true;
		for(int i=0;i<strlen(recieve_div);i++){	
			cout<<redundant[i];
			if(redundant[i]!=0){
				flag=false;
				break;
			}
	
		}
		cout<<endl;
		if(flag)
			cout<<"Recieve msg is correct"<<endl;
		else
			cout<<"Recieve msg is incorrect"<<endl;
		msgctl(msgid, IPC_RMID, NULL);
	
		
	}

}
