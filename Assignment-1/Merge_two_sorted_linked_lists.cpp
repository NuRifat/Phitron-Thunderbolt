#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Node{
public:
    int val;
    Node* next;
    Node(int val){
        this-> val = val;
        this->next = NULL;
    }
};

Node* createList(int n){
    Node* head = NULL;
    Node* tail = NULL;
    
    for(int i=0;i<n;i++){
        int x; cin >> x;
        Node* newNode = new Node(x);
        
        if(!head){
            head = newNode;
            tail = newNode;
        }
        else{
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}
Node* mergeList(Node* headA, Node* headB){
    Node* newNode = new Node(0);
    Node* tail = newNode;
    
    while(headA!=NULL && headB!=NULL){
        if(headA->val <= headB->val){
            tail->next=headA;
            headA = headA->next;
        }
        else{
            tail->next=headB;
            headB = headB->next;
        }
        tail = tail->next;
    }
    
    if(headA!=NULL){
        tail->next = headA;
    }
    else{
        tail->next=headB;
    }
    
    return newNode->next;
}

void printList(Node* head){
    while(head!=NULL){
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    int t;
    cin >> t;
    while(t--){
        int n,m;
        cin >> n;
        Node* headA = createList(n); 
        cin >> m;
        Node* headB = createList(m);
        
        Node* merge = mergeList(headA, headB);
        
        printList(merge);
    }
    
    return 0;
}
