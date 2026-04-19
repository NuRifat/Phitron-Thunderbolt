#include <bits/stdc++.h>
using namespace std;


int main() {
    int n; cin >>n;
    cin.ignore();
    
    stack<char> undo;
    stack<char> redo;
    
    while(n--){
        string command;
        cin >> command;
        
        if(command=="TYPE"){
            char x; cin >> x;
            undo.push(x);
            
            while(!redo.empty()){
                redo.pop();
            }
        }
        else if(command=="UNDO"){
            if(!undo.empty()){
                redo.push(undo.top());
                undo.pop();
            }
        }
        else if(command=="REDO"){
            if(!redo.empty()){
                undo.push(redo.top());
                redo.pop();
            }
        }
    }
    string text = "";
    while(!undo.empty()){
        text += undo.top();
        undo.pop();
    }
    reverse(text.begin(), text.end());
    cout << text << endl;
    return 0;
}
