#include<bits/stdc++.h>
#include<vector>
using namespace std;

int main(){
    int n;
    cout<<"Enter no. of data"<<endl;
    cin>>n;
    double val[n][2];
    double mean_x=0,mean_y=0;
    for(int i=0;i<n;i++){
    	cin>>val[i][0]>>val[i][1];
    	mean_x += val[i][0];
    	mean_y += val[i][1];
	}
	for(int i=0;i<n;i++){
    	cout<<val[i][0]<<"  "<<val[i][1]<<endl;
    }

	mean_x = mean_x / n;
	mean_y = mean_y / n;
	cout<<"X = "<<mean_x<<"   y= "<<mean_y<<endl;
	double sum=0;
	for(int i=0;i<n;i++){
		sum += ((val[i][0] - mean_x)*(val[i][0] - mean_x));
	}	
	double xx = sum / n-1;
	sum=0;
	for(int i=0;i<n;i++){
		sum += ((val[i][0] - mean_x)*(val[i][1] - mean_y));
	}	
	double xy = sum / n-1;
	sum=0;
	for(int i=0;i<n;i++){
		sum += ((val[i][1] - mean_y)*(val[i][1] - mean_y));
	}	
	double yy = sum / n-1;
	double cov[2][2];
	cov[0][0] = xx; cov [0][1] = xy; cov[1][0] = xy; cov[1][1] = yy;
	
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++)
			cout<<cov[i][j]<<" ";
		cout<<endl;
	}
	
	
}
