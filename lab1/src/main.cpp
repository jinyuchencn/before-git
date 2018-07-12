#include <iostream>
#include<class.h>
#include<function.h>

using namespace std;
Token_stream ts;             //声明使用的Token_stream
int main(){                 //主函数
    double val = 0;         //定义val记录结果
    while(cin){
        cout << '>' ;       //输入提示符

        Token t = ts.get();   //读取Token

        while (t.kind == ';') //读入的Token若为';'，则表示表达式已结束
            t = ts.get();     //读取下一个Token

        if (t.kind == 'q')     //读入的Token若为q，则退出
            break;

        ts.putback(t);          //将t放回Token_stream,并进行计算  

        val = expression();           //val记录表达式的值

        if(isok=='Y')cout << '='<<val << endl;  //判断计算过程中是否出错

        else{                         //若计算出错，则清空输入流，Token_stream
            cin.clear();
            cin.sync();
            ts.clear();
        }

        ans = val;                   //保留上次计算结果

        isok = 'Y';                  //一次计算后，将判断变量设为'Y'

    }
}