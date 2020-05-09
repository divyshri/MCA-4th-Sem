#include<bits/stdc++.h>
#include<stdio.h> 
#include<string.h> 
#include<fcntl.h> 
#include<sys/stat.h> 
#include<sys/types.h> 
#include<unistd.h> 
using namespace std;
int main()
{
	int fd1; 
  
    char* myfifo = "/home/mc18/mc1811/Desktop/Networks/myfifo"; 
  
    mkfifo(myfifo, 0666); 
  
	
	while(1){

		char recieve_msg[1000];
		char recieve_div[4] = {'1','1','0','1'};

		fd1 = open(myfifo,O_RDONLY); 

        read(fd1, recieve_msg, 1000); 
		
	
		int l=strlen(recieve_msg);
		
		cout<<endl<<"****Received Data****"<<endl<<endl;
		for(int i=0;i<strlen(recieve_msg);i++){
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
		
		close(fd1);
	}

}
