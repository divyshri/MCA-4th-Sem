#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;
	cin>>s;
	int m = s.size();
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
	
	//-----------------Redundant bit set generation--------------//

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
	int data[1000] = {0};
	int x=0;

	//---------------Initializing redundant set positions with -1 --------------//

	for ( itr = dataset.begin();itr!=dataset.end();itr++ )
		data[itr->second[0]-1] = -1;
		

	//---------------Placing the data according to positions -------------------//

	for(int i=m+r-1;i>=0;i--){
		if(data[i]!=-1)
			data[i] = s[x++] - 48;	
		else
			data[i] = 0;
	}

	//---------------Placing the Redundant bits using even parity --------------//

	for ( itr = dataset.begin();itr!=dataset.end();itr++ )
	{
		int count=0;
		for ( int i=0;i<itr->second.size();i++ )
		{
			if(data[itr->second[i]-1]==1)
				count++;
		}
		(count%2==0)?data[itr->second[0]-1] = 0:data[itr->second[0]-1] = 1;
	}	
	
	//-----------------Display after appending redundant bit--------------------//

	cout<<endl<<endl<<"~~~~~~~~~ Correct Data ~~~~~~~~"<<endl<<endl;
	for(int i=m+r-1;i>=0;i--)
		cout<<data[i]<<" ";

	//-----------------Altering one bit--------------------//

		data[10]=0;

	cout<<endl<<endl<<"~~~~~~~~~ Incorrect Data ~~~~~~~~"<<endl<<endl;
	for(int i=m+r-1;i>=0;i--)
		cout<<data[i]<<" ";
	
	//-----------------Checking Redundant bit in the recieved data--------------------//


	int check[r]={0};
	for ( itr = dataset.begin();itr!=dataset.end();itr++ )
	{
		int count=0;
		for ( int i=0;i<itr->second.size();i++ )
		{
			if(data[itr->second[i]-1]==1)
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







