#include<bits/stdc++.h>
#include<stdio.h> 
#include<string.h> 
#include<fcntl.h> 
#include<sys/stat.h> 
#include<sys/types.h> 
#include<unistd.h> 

using namespace std;
int main(){
	
	int fd; 
  
    // FIFO file path 
    char * myfifo = "/home/divyanshu/Desktop/Networks/myfifo"; 
  
    // Creating the named file(FIFO) 
    // mkfifo(<pathname>, <permission>) 
    mkfifo(myfifo, 0666); 
	while(1){
		
		fd = open(myfifo, O_WRONLY);

		int m,r,z;
		map<int,vector<int> > dataset;
		string s;
		cout<<endl<<"Enter Data to be sent"<<endl;
		cin>>s;

	
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


		write(fd, data, strlen(data)+1); 
        	close(fd); 

		

		char received_data[1000];


		fd = open(myfifo,O_RDONLY);

        read(fd, received_data, 1000); 
		
		if(received_data[0]=='1'){
			cout<<endl<<endl<<"Positive Acknowledgment received"<<endl;
		}
		else{
			cout<<endl<<endl<<"Negetive Acknowledgment Received"<<endl;
		}
		close(fd);

	}	
		
}
