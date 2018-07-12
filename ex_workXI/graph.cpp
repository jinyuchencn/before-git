#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

struct OneData{
    int S_id;
    int E_id;
    double value;
    int time;
};

struct Data 
{
    int size;
    vector<OneData *> data_v;
};

struct Edge;

typedef struct Node
{
    int id;
    vector<Edge *> out;
    vector<Edge *> in;
}Node;

typedef struct Edge{
    int time;
    double value;
    Node *start;
    Node *end;
}Edge;

class Graph{
    private:
        vector<int> Node_id;
        vector<Node *> Node;
        vector<Edge *> Edge;
    private:
        void AddOneNode(struct Node* N);
        void AddOneEdge(struct Edge* E);
        struct Node *findNode(int id);

    public:
        Graph(Data *p);
        // ~Graph();
        vector<vector<int>> FindAllLoop();
};

bool HaveUse(Node* temp,vector<Node*> &uesd){
    for (int i = 0; i < uesd.size();i++){
        if(temp==uesd[i]){
            return true;
        }
    }
    return false;
}

void DFS(Node* temp,vector<Node*> &one,Node* &start,vector<Node*> &used,Edge *before){
    // one.push_back(temp);
    // used.push_back(temp);


    if(temp->id==start->id){
        one.push_back(temp);
        used.push_back(temp);
        return;
    }

    int cal=0;
    if(temp->out.size()!=0){
        for (int i = 0; i < temp->out.size(); i++)
        {
            if(before->time<temp->out[i]->time){
                if(before->value>temp->out[i]->value){
                    if(!HaveUse(temp->out[i]->end,used)){
                        used.push_back(temp);
                        one.push_back(temp);
                        DFS(temp->out[i]->end,one,start,used,temp->out[i]);
                        if(one[one.size()-1]->id!=start->id){
                            one.pop_back();
                        }
                        else{
                            return;
                        }
                    }
                    else{
                        cal++;
                    }
                }
            }
        }
    }
    if(cal==temp->out.size()){
        return;
    }

}

vector<int> FindOnesAllLoop(Node* temp){
    vector<int> back;
    vector<int> wrong;
    for (int i = 0; i < temp->out.size(); i++)
    {

        vector<Node*> one;
        vector<Node*> used;
        // used.push_back(temp->out[i]->end);
        // one.push_back(temp->out[i]->end);
        DFS(temp->out[i]->end,one,temp,used,temp->out[i]);
        if(one.size()!=0){
            if(one[one.size()-1]->id!=temp->id){
                    one.pop_back();
                }
            else{
                for (int i = 0; i < one.size();i++){
                    back.push_back(one[i]->id);
                }
                break;
            }
        }
    }
    if(back.size()==0){
        return wrong;
    }
    if(back[back.size()-1]==temp->id){
        return back;
    }
    return wrong;
}

vector<vector<int>> Graph::FindAllLoop(){
    vector<vector<int>> back;
    vector<int> temp_loop;
    for (int i = 0; i < Node.size(); i++){
        temp_loop = FindOnesAllLoop(Node[i]);
        if(temp_loop.size()!=0){
            back.push_back(temp_loop);
        }
        cout << "I'm looping" << endl;
    }
    return back;
}

Node* Graph::findNode(int id){
    // vector<Node *>::iterator it;
    // // vector<int>::iterator iter;
    // for (it = Node.begin(); it != Node.end();it++){
    //     if(*it->id == id){
    //         return *it;
    //     }
    // }
    for (int i = 0; i < Node.size();i++){
        if(Node[i]->id==id){
            return Node[i];
        }
    }
    return NULL;
}

void Graph::AddOneEdge(struct Edge* E){
    Edge.push_back(E);
}

bool Nodein(int id,vector<int> &Node_id){
    for (int i = 0; i < Node_id.size();i++){
        if(Node_id[i]==id){
            return true;
        }
    }
    return false;
}

void Graph::AddOneNode(struct Node* N){
    if(Nodein(N->id,Node_id)){
        struct Node *temp_N = findNode(N->id);
        struct Edge *temp_E = new struct Edge;
        if(N->out.size()==1){
            temp_E = N->out[0];
            temp_E->start = temp_N;
            temp_N->out.push_back(temp_E);
        }
        else{
            // temp_N = findNode(N->in[0]->start->id);

            temp_E = N->in[0];
            temp_E->end = temp_N;
            temp_N->in.push_back(temp_E);
        }
    }
    else{
        Node_id.push_back(N->id);
        Node.push_back(N);
    }
}

Graph::Graph(Data *p){
    for (int i = 0; i < p->data_v.size();i++){
        OneData *One = new OneData;
        struct Node *S_N = new struct Node;
        struct Node *E_N = new struct Node;
        struct Edge *E = new struct Edge;

        One=p->data_v[i];

        S_N->id = One->S_id;
        E_N->id = One->E_id;

        E->start = S_N;
        E->end = E_N;
        E->time = One->time;
        E->value = One->value;

        S_N->out.push_back(E);
        E_N->in.push_back(E);

        AddOneNode(S_N);
        AddOneNode(E_N);
        AddOneEdge(E);
    }
}

void get_data(Data* &data){
    ifstream f;
    f.open("D:/my_vscode/C++code/ex_workXI/transfer.txt", ios::in);
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
        OneData *one = new OneData;

        one->S_id = S_id;
        one->E_id = E_id;
        one->time = time;
        one->value = value;
        // vector<double> one{S_id,E_id,value,time};
        if(S_id!=E_id){
            data->data_v.push_back(one);
        }
        i++;
        if(i%100000==0){
            cout << "I'm reading!" << endl;
        }
        if(i==1996191){          //1996192
            break;
        }
        // cout << S_id << " " << E_id << endl;
        // cout << i;
    }


    // return back;
}

void Print(vector<vector<int>> data){
    // cout << data[i][data[i].size()-1] ;
    for (int i = 0; i < data.size();i++){
        cout << data[i][data[i].size()-1] ;
        for (int j = 0; j < data[i].size();j++){
            cout << "->" <<data[i][j] ;
        }
        cout <<  endl;
    }
}

int main(){
    Data *data_p = new Data;
    get_data(data_p);

    Graph G(data_p);

    vector<vector<int>> Loop=G.FindAllLoop();

    Print(Loop);
    
    system("pause");

    return 0;
}