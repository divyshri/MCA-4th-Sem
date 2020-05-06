#include<bits/stdc++.h>
#include<vector>
using namespace std;
int main(){
    
	double n,x,y;
  	cout<<"Enter Number of values"<<endl;
  	cin>>n;
  	vector<pair<double,double> > val;
  	cout<<"Enter value of X and Y respectively"<<endl;
  	for(double i=0;i<n;i++){
  		cin>>x>>y;
  		val.push_back(make_pair(x,y));
	}
	int clus;
	cout<<"Enter the no. of clusters"<<endl;
	cin>>clus;

	vector<pair<double,double> > k ,temp_k;
	
	for(int i=0;i<clus;i++){
		k.push_back(make_pair(val[i].first,val[i].second));
	}

//	k.push_back(make_pair(val[0].first,val[0].second));
//	k.push_back(make_pair(val[1].first,val[1].second));
//	
	
	vector<pair<double,double> > c1;
	vector<pair<double,double> > c2;
	
	
	
	while(1){
//		double p_k11 = k[0].first;
//		double p_k12 = k[0].second;
//		double p_k21 = k[1].first;
//		double p_k22 = k[1].second;
		int i=0;
		c1.clear();
		c2.clear();
//		c1.push_back(make_pair(k[0].first,k[0].second));
//		c2.push_back(make_pair(k[1].first,k[1].second));
		while(i<n){
			
			double dist1 = sqrt(pow((k[0].first - val[i].first),2) + pow((k[0].second - val[i].second),2));
			double dist2 = sqrt(pow((k[1].first - val[i].first),2) + pow((k[1].second - val[i].second),2));
			if(dist1 < dist2){
				
				k[0].first = (k[0].first + val[i].first) / 2;
				k[0].second = (k[0].second + val[i].second) / 2;
				
				c1.push_back(make_pair(val[i].first,val[i].second));
				
			}
			else{
				
				k[1].first = (k[1].first + val[i].first) / 2;
				k[1].second = (k[1].second + val[i].second) / 2;
				
				c2.push_back(make_pair(val[i].first,val[i].second));
				
			}
			i++;
		}
		
		/*
		cout<<"Centroids are "<<endl;
		cout<<"C1 ----   x = "<<k[0].first<<" y = "<<k[0].second<<endl<<endl;
		cout<<"C2 ----   x = "<<k[1].first<<" y = "<<k[1].second<<endl<<endl;
	
		cout<<"Cluster's C1 --"<<endl<<endl;
		for(doublei=0;i<c1.size();i++){
			cout<<c1[i].first<<" "<<c1[i].second<<endl;
		}
		
		cout<<"Cluster's C2 --"<<endl<<endl;
		for(doublei=0;i<c2.size();i++){
			cout<<c2[i].first<<" "<<c2[i].second<<endl;
		}*/
	
		if(p_k11 == k[0].first and p_k12 == k[0].second and p_k21 == k[1].first and p_k22 == k[1].second){
				break;
		}
	}
	cout<<endl<<endl<<"Centroids are "<<endl;
	cout<<"C1 ("<<k[0].first<<" , "<<k[0].second<<") "<<endl;
	cout<<"C2 ("<<k[1].first<<" , "<<k[1].second<<") "<<endl<<endl;
	
	cout<<endl<<"Cluster's C1 --"<<endl;
	for(int i=0;i<c1.size();i++)
		cout<<" ("<<c1[i].first<<" , "<<c1[i].second<<") ";
	
	cout<<endl<<endl;
	
	cout<<endl<<"Cluster's C2 --"<<endl;
	for(int i=0;i<c2.size();i++)
		cout<<" ("<<c2[i].first<<" , "<<c2[i].second<<") ";
	
	
}
