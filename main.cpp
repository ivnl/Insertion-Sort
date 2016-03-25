#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

ifstream in_data;
ofstream out_data;

class node {
    
    friend class list;
    
public:
    int data;
    node* next;
    
    node() {
        data = -9999;
        next = nullptr;
    }
    
    node(int incoming) {
        
        this->data = incoming;
        next = nullptr;
        
    }
    
};

class list {
    
    int rejects=0;
    node *head;
    node *tail;
    
public:
    
    list() {
        
        node* n = new node();
        head = n;
        tail = n;
        
    }
    
    void append(int x) {
        
        node* newnode;
        newnode = new node(x);
        
        if(head->next == NULL) head->next = newnode;
        tail->next = newnode;
        tail = newnode;
        
    }
    
    int getRejects() {
        
        return rejects;
    }
    
    
    node* Spot(int findInt) {
        
        node* temp = head;
        
        if(temp->next==nullptr) {
            out_data<<"\nList Empty!\n";
            return NULL;
        }
        
        while(temp->next!=nullptr && temp->next->data<findInt) {
            temp=temp->next;
        }
        
        return temp;
        
    }
    
    void display() {
        
        node* temp = head->next;
        
        if(temp==nullptr) {
            
            out_data<<"\nList Empty!\n";
            return;
        }
        
        while(temp!=nullptr) {
            
            out_data<<temp->data<<" ";
            temp = temp->next;
        }
        
        out_data<<"\n\n";
        
    }
    
    void altPrint() {
        
        node*temp = head;
        if(temp==nullptr) {
            
            out_data<<"\nList Empty!\n";
            return;
        }
        
        out_data<<"listHead";
        
        while(temp->next!=nullptr) {
            
            out_data<<" --> ("<<temp->data<<", "<<temp->next->data<<")";
            
            if(temp->next->next==nullptr) {
                out_data<<" --> ("<<temp->next->data<<","<<" -1)";
            }
            
            temp = temp->next;
            
        }
        
    }
    
    void insert(int inData) {
        
        //if list is currently empty, we append the incoming element and return
        if (head->next==nullptr) {
            
            this->append(inData);
            
            out_data<<"\nInserting "<<inData<<": ";
            altPrint();
            return;
        }
        
        node* newnode = new node(inData);
        node* temp = this->Spot(inData); //use spot to find info and save to temp node
        
        //if list already has at least one element inside and duplicate data found, reject duplicate and return
        if(temp->next!=nullptr && temp->next->data==inData) {
            
            out_data<<"\n\n!Rejecting attempt to insert duplicate: "<<inData<<"\n";
            rejects++;
            return;
        }
        
        //otherwise insert element within sorted list
        out_data<<"\nInserting "<<inData<<": ";
        
        newnode->next = temp->next;
        temp->next = newnode;
        
        altPrint();
    }
    
};

int main(int argc, char * argv[]) {
    
    
    if(argc<3) {
        cout<<"Insufficient Arguments, argv[1] is input txt file name, argv[2] is output txt file name \n\n";
        return 0;
        
    }
    
    out_data.open(argv[2]);
    
    out_data<<"Elements within input file: ";
    
    in_data.open(argv[1]);
    
    int count=0;
    
    int num;
    
    if (in_data.is_open()) {
        
        while (in_data>>num) {
            
            count++;
            out_data<<num<<" ";
            
        }
        
        out_data<<"\n\n"<<"Total number of elements found in file: "<<count<<"\n";
        
        in_data.close();
        
    }
    
    list newlist; //CREATE LINKED LIST OBJECT 'newlist'
    
    in_data.open(argv[1]);
    
    if (in_data.is_open()) {
        
        while (in_data>>num) {
            newlist.insert(num);
            
        }
        
        out_data<<"\n"<<newlist.getRejects()<< " duplicates were rejected from list";
        
        in_data.close();
        
    }
    
    out_data<<"\n\n";
    
    out_data<<"Final numbers remaining in list: ";
    newlist.display();
    
    out_data<<"\n";
    
    out_data.close();
    
    cout<<"Please refer to output file specified in argv[2]\n\n";
    
    return 0;
    
};
