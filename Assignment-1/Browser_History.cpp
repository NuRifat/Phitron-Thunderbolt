#include <bits/stdc++.h>

using namespace std;



int main()
{
    list<string> ll;
    string s;
    
    while(cin>>s && s!="end"){
        ll.push_back(s);
    }
    
    int q;
    cin >> q;
    cin.ignore();
    
    auto curr = ll.begin();
    
    while(q--){
        string line;
        getline(cin,line);
        
        string command, address;
        stringstream ss(line);
        ss >> command;
        
        if(command=="visit"){
            ss >> address;
            auto it = find(ll.begin(), ll.end(), address);
            if(it != ll.end()){
                curr = it;
                cout << *curr << endl;
            }
            else{
                cout << "Not Available" << endl;
            }
        }
        else if(command=="next"){
            auto it = curr;
            it++;
            if(it != ll.end()){
                curr = it;
                cout << *curr << endl;
            }
            else{
                cout << "Not Available" << endl;
            }
        }
        else if(command=="prev"){
            if(curr != ll.begin()){
                curr--;
                cout << *curr << endl;
            }
            else{
                cout << "Not Available" << endl;
            }
        }
    }
    

    return 0;
}
