#include<iostream>
#include<stack>
using namespace std;
bool check(string s){
    stack<char> stack;

    for (int i = 0; i < s.size();i++){
        if (s[i]=='{'|s[i]=='['|s[i]=='('){
            stack.push(s[i]);
        }
        else if(s[i]==')'|s[i]==']'|s[i]=='}'){
            if(stack.size()!=0){
                char ch = stack.top();
                if(s[i]==')'){
                    if (ch!='('){
                        return false;
                    }
                    stack.pop();
                            }
                else if(s[i]==']'){
                    if(ch!='['){
                        return false;
                    }
                    stack.pop();
                }
                else{
                    if(ch!='{'){
                        return false;
                    }
                    stack.pop();
                }
            }
            else{
                return false;
            }
        }
    }
    if (stack.size()!=0)
        return false;
    return true;
}
int main(){
    cout << "Please input a expression:";
    int i = 1;
    string s;
    while (cin)
    {
        if(i==0){
            cout << "Please input a expression:";
            i = 1;
        }
        
        cin >> s;
        if(!check(s)){
            cout << "wrong!"<<endl;
        }
        else
        {
            cout << "ok!" << endl;
        }
        i = 0;
    }
    
}