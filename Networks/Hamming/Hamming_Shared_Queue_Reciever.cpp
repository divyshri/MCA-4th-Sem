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

		
		char received_data[1000];
		msgrcv(msgid, &message, sizeof(message), 1, 0); 
        //msgrcv(msgid, received_data, sizeof(received_data),1,0); 
		for(int i=0;message.mesg_text[i]!='\0';i++){
			received_data[i] = message.mesg_text[i];
		}
		int k=0;
		cout<<endl<<"Do you want to change Received Data     (Yes = 1   and No = 0)"<<endl;		
		cin>>k;
		if(k==1)
			received_data[3]='0';
	
		int m = strlen(received_data);
		int r=1;
		int z=pow(2,r);
		while(z<=(m+r+1)){
			r++;
			z=pow(2,r);
		}
		map<int,vector<int> > dataset;
		for(int i=0;i<r;i++){
			vector<int> temp;
			for(int j=1;j<=m+r;j++){
				if(j>>i&1)
					temp.push_back(j);
			}
			dataset.insert(make_pair(i,temp));
		}
		map<int, vector<int> > ::iterator itr;
		itr = dataset.begin();
		int check[r]={0};

		for ( itr = dataset.begin();itr!=dataset.end();itr++ )
		{
			int count=0;
			for ( int i=0;i<itr->second.size();i++ )
			{
				if(received_data[itr->second[i]-1]=='1')
					count++;
			}
			(count%2==0)?check[(itr->first)] = 0:check[(itr->first)] = 1;
		}	

		//-----------------Display the check data--------------------//
		bool flag = true;
		cout<<endl<<endl<<"~~~~~~~~~ Check Data ~~~~~~~~"<<endl<<endl;
		for(int i=r-1;i>=0;i--){
			cout<<check[i]<<"  ";
			if(check[i]!=0)
				flag = false;
		}
		cout<<endl;
		msgctl(msgid, IPC_RMID, NULL);
	

	}
	
}
