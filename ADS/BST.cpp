#include<iostream>
using namespace std;
struct Node{
    int data;
    Node* left;
    Node* right;
};
class BST{
    public:
        BST(){root=NULL;};
        ~BST();

        void insert(int num);
        Node* find(int num);
        bool B_delete(int num);
        bool isempty();
        
    private:
        Node* root;
};
BST::~BST(){
    
}