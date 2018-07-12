#include<iostream>
#include<queue>
#include<vector>
using namespace std;
struct Node
{
    Node() { data = 0;
        left = NULL;
        right = NULL;
    }
    int data;
    Node *left;
    Node *right;
};

Node* Insert(int x ,Node* root){
    if(root==NULL){
        Node *temp = new Node;
        temp->data = x;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
    }
    else if(x<root->data){
        
        root->left = Insert(x, root->left);
        return root;
    }
    else if(x>root->data){
        // root = root->right;
        root->right = Insert(x, root->right);
        return root;
    }
    else{
        cout << "Insert failed!" << endl;
        return root;
    }
}
Node* findptr(int x,Node* root){                     //二叉搜索
    if(root==NULL){
        cout << "Not find" << endl;
        return root;
    }
    else if(x<root->data){
        return findptr(x, root->left);
    }
    else if(x>root->data){
        return findptr(x, root->right);
    }
    else if(x==root->data){
        return root;
    }
    cout << "error" << endl;
    return NULL;
}
void pre(Node* root){
    if(root==NULL){
        return ;
    }
    cout << root->data << endl;
    pre(root->left);
    pre(root->right);
}
void in(Node* root){
    if(root==NULL){
        return ;
    }
    // cout << root->data << endl;
    in(root->left);
    cout << root->data << endl;
    in(root->right);
}
void post(Node* root){
    if(root==NULL){
        return ;
    }
    // cout << root->data << endl;
    post(root->left);
    post(root->right);
    cout << root->data << endl;
}
Node* BFS(int x,Node* root){
    if(root==NULL){
        cout << "error" << endl;
        return NULL;
    }

    queue<Node *> Q;
    Q.push(root);
    while(!Q.empty()){
        Node *temp = Q.front();
        if(temp->data==x){
            return temp;
        }
        if(temp->left!=NULL){
            Q.push(temp->left);
        }
        if(temp->right!=NULL){
            Q.push(temp->right);
        }
        Q.pop();
    }
    cout << "Not found" << endl;
    return NULL;
}
int main(){
    vector<int> a{ 4,1,2,3, 5, 6, 7};
    Node *Tree=new Node;
    for (int i=0; i < a.size();i++){
        Tree=Insert(a[i],Tree);
    }
    pre(Tree);
    delete Tree;
    cin.get();
    return 0;
}

