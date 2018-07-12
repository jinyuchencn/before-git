#include<iostream>
#include<fstream>
#include<map>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
typedef pair<string, int> PAIR;  
bool cmp_by_value(const PAIR& lhs, const PAIR& rhs) {  
  return lhs.second < rhs.second;  
}  
struct CmpByValue {  
  bool operator()(const PAIR& lhs, const PAIR& rhs) {  
    return lhs.second < rhs.second;  
  }  
};   
int main(){
    ifstream SSstream;
    map<string,int> Words;
    string data;
    SSstream.open("D:\\my_vscode\\C++code\\ex_work1\\shakespeare.txt",ios::in);
    while(!SSstream.eof()){
        SSstream>>data;
        if(Words.count(data)!=0){
            Words[data] = Words[data] + 1;
        }
        else{
            Words[data] = 1;   
        }
    }
    vector<PAIR> Words_vec(Words.begin(), Words.end()); 
    sort(Words_vec.begin(), Words_vec.end(), CmpByValue());
    for (int i = Words_vec.size()-1; i >=Words_vec.size()-11; i--) {  
        cout <<Words_vec[i].first<<':'<<Words_vec[i].second << endl;  
    }
    int n;
    cin >> n;

    map<string,int>::iterator it;

    it = Words.begin();

    while(it != Words.end())
    {
        //it->first;
        //it->second;
        if(it->first.size()<n){

        }
        else if(it->first.substr()){

        }
        it ++;         
    }
    char ch;
    cin >> ch;
    return 0;
}