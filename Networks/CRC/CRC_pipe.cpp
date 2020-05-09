#include<bits/stdc++.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
using namespace std;
int main()
{
	string str,div;
	cout<<"Enter msg to send: "<<endl;
	cin>>str;
	cout<<"Enter divisor string: "<<endl;
	cin>>div;
	
	int fd1[2],fd2[2];
	
	if(pipe(fd1)==-1){	
		cout<<"error in pipe1 " <<endl;
		return 0;
	}
	if(pipe(fd2)==-1){	
		cout<<"error in pipe2 " <<endl;
		return 0;
	}
	
	
	pid_t pid=fork();
	
	if(pid<0){
		cout<<"error in fork " <<endl;
		return 0;
	}
	
	else if(pid>0){
	
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

		//send_msg[strlen(send_msg)]='\0';
		//send_div[strlen(send_div)]='\0';
		
		cout<<endl;
		close(fd1[0]);
		write(fd1[1],send_msg,strlen(send_msg)+1);
		close(fd1[1]);
		
		close(fd2[0]);
		write(fd2[1],send_div,strlen(send_div)+1);
		close(fd2[1]);
		wait(NULL);
	
	}
	else{
	
		cout<<"Child Process"<<endl;
		// Child
		char recieve_msg[1000],recieve_div[1000];
	
		close(fd1[1]);
		read(fd1[0],recieve_msg,1000);
		close(fd1[0]);
	
		close(fd2[1]);
		read(fd2[0],recieve_div,1000);
		close(fd2[0]);
	
		int l=strlen(recieve_msg)-1;
		
		cout<<endl<<"****Received Data****"<<endl<<endl;
		for(int i=0;i<strlen(recieve_msg)-1;i++){
			cout<<recieve_msg[i]<<"  ";		
		}

		cout<<endl<<"****Received Dividend****"<<endl<<endl;
		for(int i=0;i<strlen(recieve_div);i++){
			cout<<recieve_div[i]<<"  ";		
		}
		
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
		
	}

}
