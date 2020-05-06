#include <bits/stdc++.h>
using namespace std;


void dispCount(map<set<int>, int> count) {  

    cout << "\nItem counts:\nItem\tCount\n";

    for (map<set<int> , int>::iterator i = count.begin(); i != count.end(); ++i) {  
        for (set<int>::iterator j = (i->first).begin(); j != (i->first).end(); ++j) {
            cout << *j;
        }

        cout << '\t' << i->second << endl;
    }
}


int tsupport(multiset<int> item, set<int> key) {   

    int flag = 1, sup = 0;

    for (set<int>::iterator j = key.begin(); j != key.end(); ++j) {
        if (item.find(*j) == item.end()) {
            flag = 0;
        }
    }

    if (flag) { 
        sup++;
    }

    return sup;
}


void join(vector<set<int>> dsqaure, map<set<int>, int> &lattice, map<set<int>, int> &age) {  
    for (vector<set<int>>::iterator i = dsqaure.begin(); i != dsqaure.end(); ++i) { 
        vector<set<int>>::iterator it = i;
        for (vector<set<int>>::iterator j = ++it; j != dsqaure.end(); ++j) {    
            set<int> s1(i->begin(), --(i->end())), s2(j->begin(), --(j->end()));
            int n1 = *(--(i->end())), n2 = *(--(j->end())); 
            if (s1 == s2 && n1 != n2) {
                set<int> s = *i;
                s.insert(n2);
                lattice[s] = 0;
                age[s] = 0;
            }
        }
    }
}


int main(int argc, char const *argv[]) {

    if (argc != 4) {
        cout << "Exepcting 2 arguments!\nUsage: a.out [file.csv] [min_support] [step]\n";
        return 1;
    }

    ifstream infile(argv[1]);   
    int minsup = stol(argv[2]), m = stol(argv[3]); 
    string line;
    vector<multiset<int>> items;    
    while (getline(infile, line)) { 
        stringstream stream(line);
        string word;
        multiset<int> s;
        while (getline(stream, word, ',')) {
            s.insert(stol(word));
        }
        items.push_back(s);
    }

    for (vector<multiset<int>>::iterator i = items.begin(); i != items.end(); ++i) {   
        for (multiset<int>::iterator j = i->begin(); j != i->end(); ++j) {
            cout << *j << '\t';
        }
        cout << endl;
    }

    map<set<int>, int> lattice; 
    vector<set<int>> dsqaure;   
    vector<set<int>> frequent;  
    map<set<int>, int> age;     

    for (vector<multiset<int>>::iterator i = items.begin(); i != items.end(); ++i) {  
        for (multiset<int>::iterator j = i->begin(); j != i->end(); ++j) {
            set<int> tmp;
            tmp.insert(*j);
            lattice[tmp] = 0;
            age[tmp] = 0;
        }
    }

   

    vector<multiset<int>>::iterator i = items.begin();
    while (!lattice.empty()) {  
        for (int h = 0; h < m; ++h) {  
            for (map<set<int>, int>::iterator j = lattice.begin(); j != lattice.end(); ++j) {  
                j->second += tsupport(*i , j->first);
            }

            ++i;
            if(i == items.end()){
                i = items.begin();
            }

            
        }

        for (map<set<int>, int>::iterator j = age.begin(); j != age.end(); ++j) {   
            j->second += m;
        }

       
        for (map<set<int>, int>::iterator i = lattice.begin(); i != lattice.end(); ++i) {  
            if (i->second >= minsup) {
                set<int> tmp = i->first;
                if (find(dsqaure.begin(), dsqaure.end(), tmp) == dsqaure.end()) {
                    dsqaure.push_back(tmp);
                }
            }
        }
        join(dsqaure, lattice, age);
      

       
        for (map<set<int>, int>::iterator i = age.begin(); i != age.end(); ) {   
            
            int flag = 1;
            if (i->second >= items.size()) {
                
                flag = 0;
                lattice.erase(i->first);
               
                if (find(dsqaure.begin(), dsqaure.end(), i->first) != dsqaure.end()) {  
                  
                    dsqaure.erase(remove(dsqaure.begin(), dsqaure.end(), i->first));
                    set<int> tmp = i->first;
                    frequent.push_back(tmp);
                }
                i = age.erase(i);
            }
            if (flag) {
                ++i;
            }

        }


    }
    cout << "\nFrequent:\n";
    for (vector<set<int>>::iterator i = frequent.begin(); i != frequent.end(); ++i) {   
        for (set<int>::iterator j = i->begin(); j != i->end(); ++j) {
            cout << *j;
        }
        cout << endl;
    }

    return 0;
}