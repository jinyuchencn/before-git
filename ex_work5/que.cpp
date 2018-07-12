#include <iostream>
#include <stack>
#include<string>
#include<queue>
#include<algorithm>
#include<deque>


using namespace std;
void reverse1(queue<char> &q){
    queue<char> q2;
    int size = q.size();
    char s[size];
    for (int i = 0; i < size;i++){
        s[i] = q.front();
        q.pop();
    }
    for (int i = 0; i < size;i++){
        q.push(s[size - i - 1]);
    }
}
void reverse2(queue<char> &q){
    stack<char> stack;
    int size = q.size();
    char s;
    for (int i = 0; i < size;i++){
        s = q.front();
        stack.push(s);
        q.pop();
    }
    for (int i = 0; i < size;i++){
        s = stack.top();
        q.push(s);
        stack.pop();
    }
}
void reverse3(queue<char> &q){
    if (q.size()==1){
    }
    else{
        char s = q.front();
        q.pop();
        reverse3(q);
        q.push(s);
    }
}
void print(queue<char> &q){
    char s;
    for (int i = 0; i < q.size();i++){
        s = q.front();
        q.pop();
        q.push(s);
        cout << s;
    }
    cout << endl;
    cout << endl;
}
int main(){
    queue<char> q1;
    cout << "Please input a string:";
    int i = 1;
    //string s;
    while (cin)
    {
        string s;
        if(i==0){
            cout << "Please input a string:";
            i = 1;
            }
        cin >> s;

        for (int i = 0; i < s.size(); i++)
            {
                q1.push(s[i]);
        }
        cout << "before reverse1 queue:";
        print(q1);
        reverse1(q1);
        
        cout << "after reverse1 queue:";
        print(q1);
        
        reverse2(q1);
        cout << "after reverse2 queue:";
        print(q1);

        reverse3(q1);
        cout << "after reverse3 queue:";
        print(q1);
        i = 0;
    }
    

    //q1.reverse(q1.begin(,q1.end());

}