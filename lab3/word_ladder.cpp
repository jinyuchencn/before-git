#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<string>
#include<queue>
#include<stack>
#include<algorithm>
#include<memory>
#include<time.h>
using namespace std;
map<string, string> maplist;
map<string, int> datalist;
struct Node
{
    string word;
    string before;
    Node(string w,string a){
        word = w;
        before = a;
    }
};

void getdata(){
    ifstream file;
    string filename;
    cout << "Dictionary file name?";
    while(cin){
        cin >> filename;
        file.open(filename, ios::in);
        if(file.fail()){
            cout << endl;
            cout << "Unable to open that file.  Try again." << endl;
            cout << "Dictionary file name?";
        }
        else
        {
            string data;
            while(!file.eof()){
                file >> data;
                datalist[data]=0;
            }
            break;
        }
    }
    cout << endl;

}
void getword(string &begin,string &end){
    cout << "Word #1 (or Enter ! to quit):";
    cin >> begin;
    if(begin=="!"){
        end = "!";
        return;
    }
    cout << "Word #1 (or Enter ! to quit):";
    cin >> end;

}
string getway(Node theOne){
    string back;
    stack<string> Sstack;
    //Node p = *theOne;
    while (theOne.before!="No word")
    {
        Sstack.push(theOne.word);
        theOne.word = theOne.before;
        theOne.before = maplist[theOne.before];
    }
    Sstack.push(theOne.word);
    while (!Sstack.empty())
    {
        
        back += Sstack.top();
        Sstack.pop();
        back += " ";
    }
    return back;
}
bool in(string s){
    if(datalist.count(s)==1){
        return true;
    }
    else{
        return false;
    }
}

stack<Node> OnesSons(Node N){
    string word=N.word;
    string temp = word;
    stack<Node> back;
    for (int i = 0; i < N.word.size();i++){
        for (int j = 0; j < 26;j++){
            if(word[i]!=('a'+j)){
                temp = word;
                temp[i] = 'a' + j;
                if(in(temp)){
                    if(datalist.at(temp)==0){
                        back.push(Node(temp, word));
                        if(maplist.count(temp)==0){
                            maplist[temp] = word;
                        }
                        datalist[temp] = 1;
                    }
                }
            }
        }
    }
    return back;
}
void NextStack(stack<Node> &before, string &back){
   
    Node aNode("None","None");

    stack<Node> backS;
    int sons=0;
    int nodes = before.size();
    while (!before.empty())
    {
        aNode = before.top();
        before.pop();
        stack<Node> Son=OnesSons(aNode);
        if(Son.empty()){
            sons++;
            // cout << datalist["aal"];
            // cout << datalist["aas"];
            // cout << endl;
            // back = "No way!";
        }
        while (!Son.empty())
        {
            aNode = Son.top();
            Son.pop();
            backS.push(aNode);
        }
    }
    if(sons==nodes){
        back = "No way!";
    }
    before = backS;

}
bool canfindway(queue<stack<Node>> &workQ,const string &end,string &back){
    stack<Node> temp;
    
    temp = workQ.front();
    stack<Node> next = temp;
    workQ.pop();
    

    Node aNode("None","None");
    while(!temp.empty()){
        aNode = temp.top();
        temp.pop();
        
        if(aNode.word==end){
            back = getway(aNode);
            return true;
        }
        //cout << i << endl;
    }
    
    NextStack(next,back);
    workQ.push(next);
    if(back=="No way!"){
        return false;
    }
    return canfindway(workQ, end, back);

}

bool findway(const string &begin,const string &end,string &back){
    if(begin.size()!=end.size()){
        back = "1";
        return false;
    }
    if(begin==end){
        back = "2";
        return false;
    }
    if(datalist.count(begin)==0||datalist.count(end)==0){
        back = "3";
        return false;
    }
    queue<stack<Node>> workQ;
    stack<Node> temp;
    temp.push(Node(begin,"No word"));
    datalist[begin] = 1;
    maplist[begin] = "No word";
    workQ.push(temp);

    if(canfindway(workQ,end,back)){
        return true;
    }
    return false;
}
int main(){
    
    cout << "Welcome to Word Ladder." << endl;
    cout << "Please give me two English words, and Iwill change the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;
    getdata();
    cout << datalist.size() << endl;
    string begin;
    string end;
    while(cin){
        // clock_t start_time = clock();
        map<string,int>::iterator it;
        it = datalist.begin();
        while(it != datalist.end())
        {
            it->second = 0;
            it ++;         
        }
        maplist.clear();
        getword(begin, end);
        clock_t start_time = clock();
        if(begin=="!"||end=="!"){
            break;
        }
        // clock_t start_time = clock();
        string back;
        bool haveway = findway(begin,end,back);
        if(haveway){
            cout << "A ladder from " << begin << " back to " << end << ":" << endl;
            cout << back<<endl;
        }
        else if(back=="1"){
            cout << "The two words must be the same length." << endl;
        }
        else if(back=="2"){
            cout << "The two words must be different." << endl;
        }
        else if(back=="3"){
            cout << "The two words must be both found in the dictionary." << endl;
        }
        else{
            cout << back<<endl;
        }
        // cout << endl;
        clock_t end_time = clock();
        double run_time = end_time - start_time;
        cout << "run time(from input word #2):" << run_time <<"ms"<< endl;
        cout << endl;
    }
    return 0;
}