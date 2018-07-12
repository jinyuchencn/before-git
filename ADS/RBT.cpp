#include<iostream>
using namespace std;
struct Node{
    int data;
    char color;
    Node* left;
    Node* right;
    Node(int num){
        data=num;
        color='R';
        left=NULL;
        right=NULL;
    }
};
class RBT{
    public:
        RBT(){ top=NULL; };
        ~RBT();
        void insert(int data);
        void RBTdelete(int data);
    private:
        Node* top;
};
void RBT::insert(int data){
    if(top==NULL){
        top->color='R';
        top->data=data;
        top->left=NULL;
        top->right=NULL;
        return;
    }
    // Node* temp=new Node(data);
    if(data==top->data){
        cout<<"repeated"<<endl;

    }

}


void what2(int *s){
    cout<<"in func2:"<<s<<
}

void what1(int *& s){
    cout<<"in func1:"<<s<<endl;

}

int main(){
    int a=1;
    int* b=&a;
    int** c=&b;
    // cout<<a<<endl;
    // cout<<b<<endl;
    // cout<<c<<endl;
    what(b);
    cout<<"b:"<<b<<endl;
    cout<<"c:"<<c<<endl;
    system("pause");
    return 0;
}