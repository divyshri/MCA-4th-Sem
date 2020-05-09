#include<bits/stdc++.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
using namespace std;
int main(){
	int fd[2],m,r,z;
	map<int,vector<int> > dataset;
	if(pipe(fd)==-1){
		cout<<"Pipe Faied"<<endl;
		return 1;
	}
	string s;
	cin>>s;

	//-----------------Creating Process------------------------//
	
	pid_t pid; 
	pid = fork();
	if(pid<0){
		cout<<"Fork Failed"<<endl;
		return 1;
	}
	
	//----------------Parent Process-------------------------//

	if(pid > 0){
		m = s.size();
		r=1;
		z=pow(2,r);
		while(z<=(m+r+1)){
			r++;
			z=pow(2,r);
		}
		
		//-----------------Redundant bit set generation--------------//		

		
		for(int i=0;i<r;i++){
			vector<int> temp;
			for(int j=1;j<=m+r;j++){
				if(j>>i&1)
					temp.push_back(j);
			}
			dataset.insert(make_pair(i,temp));
		}
		map<int, vector<int> > ::iterator itr;
	
		
		cout<<endl<<endl<<"~~~~~~~~~ Redundant bit Set Generation ~~~~~~~~"<<endl<<endl;
		for ( itr = dataset.begin();itr!=dataset.end();itr++ )
		{
			cout << itr->first << " :";
			for ( int i=0;i<itr->second.size();i++ )
			{
				cout << itr->second[i]<<"  ";
			}
			cout << endl;
		}


		itr = dataset.begin();
		char data[1000];
		int x=0;
		//memset(data,'0',100);

		//---------------Initializing redundant set positions with -1 --------------//

		for ( itr = dataset.begin();itr!=dataset.end();itr++ )
			data[itr->second[0]-1] = 'x';
		
		//---------------Placing the data according to positions -------------------//

		for(int i=m+r-1;i>=0;i--){
			if(data[i]!='x')
				data[i] = s[x++];	
			else
				data[i] = '0';
		}


		//---------------Placing the Redundant bits using even parity --------------//

		for ( itr = dataset.begin();itr!=dataset.end();itr++ )
		{
			int count=0;
			for ( int i=0;i<itr->second.size();i++ )
			{
				if(data[itr->second[i]-1]=='1')
					count++;
			}
			(count%2==0)?data[itr->second[0]-1] = '0':data[itr->second[0]-1] = '1';
		}


		//-----------------Display after appending redundant bit--------------------//

		cout<<endl<<endl<<"~~~~~~~~~ Correct Data ~~~~~~~~"<<endl<<endl;
		for(int i=m+r-1;i>=0;i--)
			cout<<data[i]<<" ";


		close(fd[0]);
		write(fd[1], data, strlen(data)); 
        	close(fd[1]); 	


		wait(NULL);
		
	}
	else{

		m = s.size();
		r=1;
		z=pow(2,r);
		while(z<=(m+r+1)){
			r++;
			z=pow(2,r);
		}
		char received_data[1000];


		close(fd[1]);
		read(fd[0], received_data, 1000);
		close(fd[0]);
		
		received_data[3]='1';

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

		cout<<endl<<endl<<"~~~~~~~~~ Check Data ~~~~~~~~"<<endl<<endl;
		for(int i=r-1;i>=0;i--)
			cout<<check[i]<<"  ";
		cout<<endl;

	}
	
}
