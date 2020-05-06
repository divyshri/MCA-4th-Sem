#include<bits/stdc++.h>
using namespace std;
int main(){
	int trans = 1;
	ofstream file_out("Input.txt");
	while(trans <= 10){
		file_out<<"T"<<trans<<" ";
		int k = rand() %100000;
		while(k>0){
			int t = k%10;
			file_out<<"I"<<t+1<<",";
			k/=10;
		}
		file_out<<endl;
		trans++;
	}
}

