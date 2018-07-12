//实现一个基于命令行的文本化计算器,现在可以计算+-法
#include<iostream>
using namespace std;
int main(){
    double first, second, result;
    char fuhao;
    while(true){
        cout << "Please enter:" << endl;
        cin >> first >> fuhao >> second;
        if (fuhao=='+'){
            result = first + second;
        }
        else{
            result = first - second;
        }
        cout << result << endl;
    }
}