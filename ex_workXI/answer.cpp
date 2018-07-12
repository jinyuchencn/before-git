#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<sstream>
#include <cstdio> 
#include<stack>

using namespace std;


struct Node{  
    int id;
    // int time;    //with his father

    // int time;
    vector<Node *> next;
    

    vector<Node *> Father;
};  
  

  

double find_max(vector<vector<double>> &data){
    double max=0;
    for (int i = 0; i < data.size();i++){
        if(max<data[i][0]){
            max = data[i][0];
        }
        if(max<data[i][1]){
            max = data[i][1];
        }
    }
    return max;
}

void get_data(vector<vector<double>> &data){
    ifstream f;
    f.open("D:/my_vscode/C++code/ex_workXI/test.txt", ios::in);
    long int i = 0;
    while (!f.eof())
    {
        string onepiece;
        string temp;
        while (true)
        {
            f >> temp;
            if(temp=="00:00:00"){
                break;
            }
            else if(temp=="|"){
                onepiece += " ";
            } 
            else if(temp[4]=='-'){
                string a;
                for (int i = 0; i < temp.size();i++){
                    if(temp[i]!='-'){
                        a += temp[i];
                    }
                }
                onepiece += a;
            }  
            else
            {
                onepiece += temp;
            }
            
        }
        double S_id;
        double E_id;
        double value;
        double time;
        stringstream ss;
        // for (int i = 0; i < onepiece.size();i++){
        ss << onepiece;
        ss >> S_id;
        ss >> E_id;
        ss >> value;
        ss >> time;
        vector<double> one{S_id,E_id,value,time};
        if(S_id!=E_id)data.push_back(one);
        i++;
        if(i%10000==0){
            cout << "I'm reading!" << endl;
        }
        if(i==5){
            break;
        }
        // cout << i;
    }


    // return back;
}

bool HaveF(Node *N, Node *T, Node *&F);

bool HaveFather(Node* N,vector<Node*> T,Node*&F){
    // Node *temp;
    if(T.size()==0){
        return false;
    }
    for (int i = 0; i < T.size();i++){
        if(HaveF(N,T[i],F)){
            return true;
        }
    }
    return false;
}


bool HaveF(Node*N,Node*T,Node*&F){
    if(T->next.size()==0){
        return false;
    }
    
    for (int i = 0; i < T->next.size();i++){
        if(T->next[i]->id==N->id){
            F = T->next[i];
            return true;
        }
        if(HaveF(N,T->next[i],F)){
            return true;
        }
    }
    return false;
}


bool HaveC(Node *N, Node *T, Node *&C);

bool HaveChild(Node* N,vector<Node*> T,Node*&C){
    // Node *temp;
    if(T.size()==0){
        return false;
    }
    for (int i = 0; i < T.size();i++){
        if(HaveC(N,T[i],C)){
            return true;
        }
    }
    return false;
}


bool HaveC(Node*N,Node*T,Node*&C){
    if(T->next.size()==0){
        for (int i = 0; i < T->Father.size();i++){
            if(N==T->Father[i]){
                C = T;
                return true;
            }
        }
            return false;
    }
    else{
        for (int i = 0; i < T->Father.size();i++){
            if(N==T->Father[i]){
                C = T;
                return true;
            }
        }
        for (int i = 0; i < T->next.size();i++){
            if(HaveC(N,T->next[i],C)){
                return true;
            }
        }
        return false;
    }
}

bool DFS( Node* T,stack<int> &back,Node* begin){

    if(T->next.size()==0){
        return false;
    }
    for (int i = 0; i < T->next.size();i++){
        back.push(T->next[i]->id);
        if(T->next[i]->id==begin->id){
            return true;
        }

        if(DFS(T -> next[i], back, begin)){
            return true;
        }
        else
        {
            back.pop();
            
        }
    }
    return false;
}

void findloop(const vector<Node*> &Tu,stack<int> &back){
    for (int i = 0; i < Tu.size();i++){
        Node *begin = Tu[i];
        back.push(begin->id);
        if(DFS(Tu[i], back,begin)){
            return;
        }
        
        else
        {
            back.pop();
        }
        
    }
}

int main(){
    vector<vector<double>> data;
    get_data(data);
    cout << "finish get data" << endl;
    //double max = find_max(data);
    vector<Node*> Tu;
    // vector<double> temp;
    // int temp_id;
    //Node *temp_N= new Node;
    for (int i = 0; i < data.size();i++){
/* 1、我们拿到一条边
 * 2、连接起点终点
 * 3、找到起点、终点在Trees的所有爹，连起来
 * 4、找到起点、终点在Trees的所有儿子，连起来
 * 5、若什么都没有，新建一个图
 */ 
        Node *temp_N= new Node;
        temp_N->id = data[i][0];
        // temp_N->time = -1;
        Node *temp_next = new Node;
        temp_next->id = data[i][1];
        // temp_next->time = temp[3];
        temp_N->next.push_back(temp_next);
        temp_next->Father.push_back(temp_N);
        Node *Father=new Node;
        Node *child=new Node;
        int j = 0;
        if(HaveFather(temp_N,Tu,Father)){
            Father->next.push_back(temp_next);
            temp_next->Father.push_back(Father);
            j++;
        }
        else if(HaveChild(temp_next,Tu,child)){
            child->Father.push_back(temp_next);
            temp_next->next.push_back(child);
            j++;
        }
        if(j==0){
            Tu.push_back(temp_N);
        }

    }
    cout << "finish generate" << endl;
    stack<int> loop;
    findloop(Tu,loop);
    cout << "finish find one loop" << endl;
    cout << endl;
    if(loop.empty()){
        cout << "No loop" << endl;
    }
    while (!loop.empty())
    {
        cout << loop.top() << "->" ;
        loop.pop();
    }
    cout << endl;
    system("pause");  
    return 0;
}