#include<bits/stdc++.h>
#include<vector>
using namespace std;
int main(){
    
	int n;
  	cout<<"Enter Number of values"<<endl;
  	cin>>n;
  	cout<<"Enter "<<n<<" values"<<endl;
  	int ar[n];
  	for(int i=0;i<n;i++)
  		cin>>ar[i];
  	cout<<"Select Two centroids"<<endl;
  	int x,y,prev_x,prev_y;
  	cout<<"Centroid 1 "<<endl;
  	cin>>x;
  	cout<<"Centroid 2"<<endl;
  	cin>>y;
  	vector<int> c1,c2;
  	int i=0;
  	while(x!=prev_x and y!=prev_y){
  		int a=0,b=0,sum_a=0,sum_b=0;
  		i=0;
  		c1.clear();
		c2.clear();	
		while(i<n){
			int diff1 = abs(ar[i] - x);
	  		int diff2 = abs(ar[i] - y);
	  		if(diff1 < diff2){
	  			sum_a += ar[i]; 
				c1.push_back(ar[i++]);
				a++;	
			}
			else{
				sum_b += ar[i];
				c2.push_back(ar[i++]);
				b++;
			}
			
		}
		prev_x = x;
		prev_y = y;
		x = floor(sum_a / a);
		y = floor(sum_b / b);
		
	}
    
    cout<<"centroids are - C1 = "<<x<<" and C2 = "<<y<<endl;
    cout<<endl;
    
    cout<<"Cluster C1"<<endl;
	for(int i=0;i<c1.size();i++)
		cout<<c1[i]<<" ";
    cout<<endl<<"Cluster C2"<<endl;
	for(int i=0;i<c2.size();i++)
		cout<<c2[i]<<" ";
    
}
