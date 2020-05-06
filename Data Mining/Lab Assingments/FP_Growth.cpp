#include<bits/stdc++.h>
using namespace std;
=
struct node
{
	int item; //item set
	int count; // item set count
	std::vector<node *> child; // its children node
	node *parent; // ptr to parent
	node()
	{
		parent=NULL;
	}
};

 
#define MAPI map<int,int>
#define FOR_MAP(ii,structure,T) for(structure::iterator (ii)=(T).begin();(ii)!=(T).end();(ii)++)
#define FOR_next_MAP(jj,ii,structure,T) for(structure::iterator (jj)=(ii);(jj)!=(T).end();(jj)++)
const int MIN_SUP = 2;

 vector<pair<int,bool> > order_of_freq_item_id;
 vector<node *> root;
 
 vector<pair<int,vector<node* > > > header_table;

 void scan_dataset();

 void form_desc_order_list_of_freq_item(MAPI map_freq_set);

 void insert(vector<node *>& head,vector<int> list_of_items,int index_to_insert,node *prt);

 void tree_creation();
 
 void output_tree();

 void initialise_header_table_with_item();


 int main(int argc, char const *argv[])
 {
 	root.clear();
 	scan_dataset();
 	tree_creation();

 	return 0;
 }

 void scan_dataset()
 {
	
	 MAPI map_freq_set;
	 map_freq_set.clear();


	 ifstream fin;
	
	 fin.open("input.txt");

	 if(!fin)
	 {
	 	cout<<"ErrorID:FPG_1 Opening input file\n";
	 	exit(0);
	 }

	 int item_id;

	 while(fin>>item_id)
	 {
	 	if(item_id!=-1)
	 	{
			if(map_freq_set.count(item_id)>0)//if item_id is already present
				map_freq_set[item_id]++;
			else
				map_freq_set[item_id]=1;
		}
	}
	fin.close();

	MAPI map_temp;
	map_temp.clear();

	FOR_MAP(ii,MAPI,map_freq_set)
	{
		if (ii->second>=MIN_SUP)		
		{
			map_temp[ii->first]=ii->second;
		}
	}

	map_freq_set.clear();
	map_freq_set=map_temp;
	form_desc_order_list_of_freq_item(map_freq_set);
	initialise_header_table_with_item();

}

void form_desc_order_list_of_freq_item(MAPI map_freq_set)
{
	order_of_freq_item_id.clear();
	
	FOR_MAP(ii,MAPI,map_freq_set)
	{
		int max_count = 0;
		int max_item_id = 0;

		FOR_MAP(jj,MAPI,map_freq_set)
		{
			if(jj->second > max_count)
			{
				max_count = jj->second;
				max_item_id = jj->first;
			}
		}

		if (max_item_id > 0)
		{
			order_of_freq_item_id.push_back(make_pair(max_item_id,false));
			map_freq_set[max_item_id]=-1;
		}
	}

	
}

void insert(vector<node *>& head,vector<int> list_of_items,int index_to_insert,node *prt)
{
	bool item_found=false;
	if(head.size()>0)
	{
		for (int jj = 0; jj < head.size(); ++jj)
		{
			if(head[jj]->item == list_of_items[index_to_insert])
			{
				item_found=true;
				head[jj]->count++;
				if(index_to_insert+1 < list_of_items.size())
				{
					insert(head[jj]->child,list_of_items,index_to_insert+1,head[jj]);
				}
			}
		}
	}
	if(!item_found)
	{
		node *new_node;
		new_node=new node;
		new_node->item=list_of_items[index_to_insert];
		new_node->count=1;
		new_node->child.clear();
		new_node->parent=prt;
		
		if(index_to_insert+1 < list_of_items.size())
		{
			insert(new_node->child,list_of_items,index_to_insert+1,new_node);
		}
		head.push_back(new_node);
	}
	
}

void tree_creation()
{
	ifstream fin;
	fin.open("input.txt");
	int item_id;
	std::vector<int> items_to_be_inserted;
	items_to_be_inserted.clear();
	while(fin>>item_id)
	{
		if(item_id==-1)
		{
			
			 for(int ii=0;ii<order_of_freq_item_id.size();ii++)
			 {
			 	if(order_of_freq_item_id[ii].second==true)
			 		items_to_be_inserted.push_back(order_of_freq_item_id[ii].first);
			 }

			 insert(root,items_to_be_inserted,0,NULL);

			 items_to_be_inserted.clear();

			 for(int ii=0;ii<order_of_freq_item_id.size();ii++)
			 	order_of_freq_item_id[ii].second=false;

		}else
		{
				for(int ii=0;ii<order_of_freq_item_id.size();ii++)
				{
					if(order_of_freq_item_id[ii].first == item_id)
					{
						order_of_freq_item_id[ii].second=true;
						break;
					}
				}
		}
	}

	output_tree();
}

void output_tree()
{
	
	 queue<vector<node *> > q;
	 q=queue<vector<node *> >();
	 vector<node *> vec_empty;
	 vector<node *> temp;
	 vec_empty.clear();
	 temp.clear();
	 q.push(root);
	 q.push(vec_empty);
	 while(!q.empty())
	 {
	 	temp=q.front();
	 	q.pop();
	 	if(temp.size()>0)
	 	{
	 		q.push(vec_empty);
	 		if(temp[0]->parent)
	 			cout<<"parent "<<temp[0]->parent->item<<" "<<temp[0]->parent->count<<"\n";
	 		else
	 			cout<<"NULL\n";
	 		for (int i = 0; i < temp.size(); ++i)
	 		{
	 			cout<<temp[i]->item<<" "<<temp[i]->count<<",";
	 			if(temp[i]->child.size()>0)
	 			q.push(temp[i]->child);
	 		}

	 	}

	 	temp = q.front();
	 	q.pop();
	 	if(temp.size()==0)
	 	{
	 		cout<<"\n";
	 		if(q.size()==0)
	 			break;
	 		else
	 			q.push(temp);
	 	}else
	 		q.push(temp);
	 }

	 
	 
}

void initialise_header_table_with_item()
{
	header_table.clear();
	vector<node *> temp;
	temp.clear();

	for(int i = 0; i < order_of_freq_item_id.size(); ++i)
	{
		header_table.push_back(make_pair(order_of_freq_item_id[i].first,temp));
	}

}