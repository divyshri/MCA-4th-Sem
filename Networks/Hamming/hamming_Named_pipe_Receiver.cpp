#include<bits/stdc++.h>
#include<stdio.h> 
#include<string.h> 
#include<fcntl.h> 
#include<sys/stat.h> 
#include<sys/types.h> 
#include<unistd.h> 
using namespace std;
int main(){

	int fd1; 
  
    char* myfifo = "/home/divyanshu/Desktop/Networks/myfifo"; 
  
    mkfifo(myfifo, 0666); 
  
	
	while(1){

		
		char received_data[1000];


		fd1 = open(myfifo,O_RDONLY); 

        	read(fd1, received_data, 1000); 
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
		
		close(fd1);
		
		fd1 = open(myfifo, O_WRONLY);
		char c[1];
		if(flag){
			c[0] = '1';
			cout<<"Correct Data Received Sending Positive ACK"<<endl;
			write(fd1, c , 3); 
		}
		else{
			c[0] = '0';
			cout<<"Negetive Data Received Sending Negetive NCK"<<endl;
			write(fd1, c , 3); 
		}
        close(fd1); 

	

	}
	
}
