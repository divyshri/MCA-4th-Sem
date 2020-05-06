#include<bits/stdc++.h>
using namespace std;
// ------------------------------count the support count of each combination from main dataset------------------

int count_f(string s,map<string,vector<string> > &dt_set)
{
	int ans=0;
	map<string,vector<string> >:: iterator it1;
	vector<string>:: iterator it2;
	for(it1=dt_set.begin();it1!=dt_set.end();it1++)
	{	
		bool flag=true;
		for(int i=0;s[i]!='\0';i++)
		{
			bool flag1=false;
			for(it2=it1->second.begin();it2!=it1->second.end();it2++)
			{
				string t=*it2;
				if(t[0]==s[i]){
					flag1=true;
					break;
				}
			}
			if(!flag1){
				flag=false;
				break;
			}
		}
		if(flag) ans++;
		
	}
	return ans;
}

//----------------------------------creating hash table subset---------------------------
vector<string> subset_hash(vector<string> str)
 {
 	vector<string> ans;
 	for(int i=0;i<(1<<str.size());i++)
 	{
 		if(__builtin_popcount(i)==(2))
 		{
 			int t=i;
 			string temp="\0";
 			int j=0;
 			while(t>0)
 			{
 				if((t&1)==1)
 					temp+=str[j];
 				j++;
 				t=t>>1;
			 }
			ans.push_back(temp);
		 }
	 }
	 return ans;
 }
//----------------------------------creating hash table ---------------------------
map<string ,int> hash_table(map<string,vector<string> > &dt_set,int min_sup)
{
	map<int ,vector<string> > hash;
	map<string,int> np;
	map<string,vector<string> > :: iterator it1;
	vector<string> :: iterator it2;
	
	for(it1=dt_set.begin();it1!=dt_set.end();it1++)
	{
		vector<string> res = subset_hash(it1->second);
		for(int i=0;i<res.size();i++)
		{
			string temp=res[i];
			int h=((temp[0]-'0')*10+(temp[1]-'0'))%7;
			hash[h].push_back(res[i]);
		}
	}
	
	map<int ,vector<string> > :: iterator it;
	cout<<"-----------------Hash Bucket--------------"<<endl;
	for(it=hash.begin();it!=hash.end();it++)
	{
		cout<<it->first<<" ";
		for(it2=it->second.begin();it2!=it->second.end();it2++)
		{
			cout<<(*it2)<<" ";
		}
		cout<<endl;
	}
	
	for(it =hash.begin();it!=hash.end();it++)
	{
		if(it->second.size() >= min_sup)
		{
			for(it2=it->second.begin();it2!=it->second.end();it2++)
			{
				string temp =*it2;
				np[*it2]=count_f(temp,dt_set);
			}
		}
	}
	
	return np;
	
}


// -----------------------------Subset Generation of string-------------------------------
vector<string> subset(string str,int l)
 {
 	vector<string> ans;
 	for(int i=0;i<(1<<l);i++)
 	{
 		if(__builtin_popcount(i)==(l-1))
 		{
 			int t=i;
 			string temp="\0";
 			int j=0;
 			while(t>0)
 			{
 				if((t&1)==1)
 					temp+=str[j];
 				j++;
 				t=t>>1;
			 }
			ans.push_back(temp);
		 }
	 }
	 return ans;
 }

//----------------------------Checking whether a valid subset or not----------------- 
bool check_subset(string str,map<string,int> &m)
{
	vector<string> v = subset(str,str.length());
	bool flag=true;
	for(int i=0;i<v.size();i++)
	{
		if(m.find(v[i])==m.end())
		{
			flag=false;
			break;
		}
	}
	return flag;
}




map<string,int> reduce(map<string,int> &c,int min_sup)
{
	map<string,int>:: iterator it3;
	string arr[1000];
	int l=0;
	for(it3=c.begin();it3!=c.end();it3++)
	{
		if(it3->second < min_sup)
		{		
			arr[l++]=it3->first;
		}	
	}
	
	for(int i=0;i<l;i++)
	{
		c.erase(arr[i]);
	}
	return c;                                                     
}

//-----------------------------Main join step---------------------------
map<string, int> join(map<string,int> &m,map<string,vector<string> > &dt_set,int k)
{
	map<string,int> np;
	map<string,int> :: iterator it1,it2;
	for(it1=m.begin();it1!=m.end();it1++)
	{
		it2=it1;
		for(it2++;it2!=m.end();it2++)
		{
			string str1=it1->first, str2=it2->first;string ans="\0";
    		bool flag=true;
  			  for(int i=0;i<(k-2);i++)
    		{
        		if(str1[i]!=str2[i])
        		{
            		flag=false;
            		break;
        		}	
    		}	
			if(flag and (str1[str1.length()-1]-'0')<(str2[str2.length()-1]-'0'))
   			{
				string str3;
				string :: iterator t,st;
				t=set_union(str1.begin(),str1.end(),str2.begin(),str2.end(),str3.begin());
				string temp="\0";
				for(st=str3.begin();st!=t;st++) temp+=*st;
				
				//cout<<endl<<temp<<endl;
				if(temp.size()<=k and check_subset(temp,m))
					np[temp]=count_f(temp,dt_set);
			}
		}
	}
	
	return np;
	
}


int main()
{
	int min_sup=2;
	/* -------------------Taking input from file ----------------*/ 
	string str;
	string st[2];
	map<string,string> dt;
	int k=0;
	ifstream file("Input.txt");
	if(file.is_open())
	{
		while(getline(file,str))
		{
			stringstream ss(str);
			string temp;
			while(getline(ss,temp,' '))
			{
				st[k++]=temp;
			}
			dt.insert(make_pair(st[0],st[1]));
			k=0;
		}
		file.close();
	}
	
	/*-----------------Arranging data as per requirements------------*/
	map<string,string>:: iterator it;
	map<string,vector<string> > dt_set;
	
	for(it=dt.begin();it!=dt.end();it++)
	{
		stringstream ss(it->second);
		string temp;
		while(getline(ss,temp,','))
		{
			temp=temp.substr(1,1);
			dt_set[it->first].push_back(temp);
		}
	}
	
	map<string,vector<string> > :: iterator it1;
	vector<string> :: iterator it2;
	
	for(it1=dt_set.begin();it1!=dt_set.end();it1++)
	{
		cout<<it1->first<<" ";
		for(it2=it1->second.begin();it2!=it1->second.end();it2++)
		{
			cout<<(*it2)<<" ";
		}
		cout<<endl;
	}
	
	/*--------generating first candidate------*/
	
	map<string ,int> c,ans;
	for(it1=dt_set.begin();it1!=dt_set.end();it1++)
	{
		for(it2=it1->second.begin();it2!=it1->second.end(); it2++)
		{
			c[*it2]++;
		}
	}
	
	
	/*-----------Generating consecutive candidates and level-------*/
	map<string ,int> :: iterator it3;
	int i=1;
	while(!c.empty())
	{
		cout<<"/-------------C"<<i<<"-------------/"<<endl;
		for(it3=c.begin();it3!=c.end();it3++)
		{
			string t=it3->first;
			for(int j=0;j<t.length();j++) cout<<"I"<<t[j]<<" ";
			cout<<"\t"<<it3->second<<endl;	
		}
		if(i==1)
		{
		  c=hash_table(dt_set,min_sup);
		  cout<<"/-------------C"<<i+1<<"-------------/"<<endl;
			for(it3=c.begin();it3!=c.end();it3++)
			{
				string t=it3->first;
				for(int j=0;j<t.length();j++) cout<<"I"<<t[j]<<" ";
					cout<<"\t"<<it3->second<<endl;	
			}
			i++;
		}
		
		c=reduce(c,min_sup);
		
		cout<<"/-------------L"<<i<<"-------------/"<<endl;
		for(it3=c.begin();it3!=c.end();it3++)
		{
			string t=it3->first;
			for(int j=0;j<t.length();j++) cout<<"I"<<t[j]<<" ";
			cout<<"\t"<<it3->second<<endl;
		}
		
		cout<<endl<<endl;
		
		if(!c.empty())
			ans=c;
		c=join(c,dt_set,i+1);
	
	i++;	
	}
	
	cout<<"/-------------ANS-------------/"<<endl;
	for(it3=ans.begin();it3!=ans.end();it3++)
		{
			string t=it3->first;
			for(int j=0;j<t.length();j++) cout<<"I"<<t[j]<<" ";
			cout<<"\t"<<it3->second<<endl;	
		}
	
	ofstream file_out("Output.txt");
	while(file_out.is_open())
	{
		for(it3=ans.begin();it3!=ans.end();it3++)
		{
			string t=it3->first;
			for(int j=0;j<t.length();j++) file_out<<"I"<<t[j]<<" ";
			file_out<<"\t"<<it3->second<<endl;	
		}
		file_out.close();
	}
	
	return 0;
}
