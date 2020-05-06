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
	
	map<int,vector<pair<double,double> > > c;
	
	bool flag= true;
	
	while(flag){
		flag = false;
		temp_k = k;
		int i=0;
		c.clear();
		double dist;
		while(i<n){
			
			int f_dist=INT_MAX,pos;
			for(int z=0;z<clus;z++){
				dist = sqrt(pow((k[z].first - val[i].first),2) + pow((k[z].second - val[i].second),2));	
				if(f_dist>dist){
					f_dist = dist;
					pos = z;
				}
			}
			c[pos].push_back(make_pair(val[i].first,val[i].second));
			k[pos].first = (k[pos].first + val[i].first) / 2;
			k[pos].second = (k[pos].second + val[i].second) / 2;	
			i++;
		}
		
		for(int z=0;z<clus;z++){
			if(temp_k[z].first != k[z].first and temp_k[z].second != k[z].second)
				flag = true;
		}
	}
	cout<<endl<<endl<<"Centroids are "<<endl;
	for(int i=0;i<clus;i++)
		cout<<"C"<<i<<"  = ("<<k[i].first<<" , "<<k[i].second<<") "<<endl;
	
	cout<<endl<<"Cluster's"<<endl;
	map<int,[[[[vector<pair<double,double> > > :: iterator itr;
					for(itr = c.begin();itr !=]]]] c.end() ; itr++){
		cout<<endl<<"C"<<itr->first<<endl;
		vector<pair<double,double> > :: iterator itr1;
		for(itr1 = itr->second.begin();itr1 != itr->second.end();itr1++){
			cout<<" ("<<itr1->first<<" , "<<itr1->second<<") ";
		}
	}
	
}
