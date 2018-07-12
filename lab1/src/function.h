#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include<class.h>
void error(string s){                                       //报错函数
    cout << s << endl;
}

void Token_stream::putback(Token t){                        //将读入的未使用的Token放回Token流
    buffer = t;    //缓冲区设为未读入的Token t
    full = true;   //缓冲区设为满
}

Token Token_stream::get(){
    if(full){              //如果已得到一个Token，则只需将其返回
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch;

    switch(ch){             //缓冲区为空，则需读入新数据，并分情况处理
        case';':       
        case'q':
        case'A':case'N':case'S':
        case'(':case')':case'+':case'-':case'*':case'/':case'%':case'!':   //各种符号，直接作为字符型Token返回
            return Token(ch);
        case'0':case'1':case'2':case'3':case'4':           //数字型Token，返回这个Token，并读入其值
        case'5':case'6':case'7':case'8':case'9':{
            cin.putback(ch);
            double val;
            cin >> val;
            return Token('8', val);
        }
         
        default:{
            if(isok!='N')error("error");                //输入出错时，将isok设为‘N’，并报错
            isok = 'N';
        }
    }
    return 0;
}

void Token_stream::clear(){                                 //清空Token_stream的函数
    full = false;
    buffer = 0;
}

double jiecheng(double n){                                  //定义阶乘函数

    if (n!=int(n)||n<0){                                    //检测输入是否合法
        if(isok!='N')error("error");
        isok = 'N';
        return 0;
    }

    else{                                                  //for循环实现阶乘函数
        n = int(n);
        if (n==0)
            return 1;
        int val = 1;
        for (int i = 1; i < n+1; i++)
        {
            val *= i;
        }
        return double(val);
    }
    
}

double expression();                    //声明expression，便于函数调用 

double primary(){
    
    Token t = ts.get();                 //从token流中读取下一个token

    switch (t.kind)         //分情况讨论读入Token
    {
        case'(':{
            double d = expression();   //若为左括号则读入一个expression，并判断expression后是否为')'
            t = ts.get(); 
            
            if(t.kind!=')'){
                if(isok!='N')error("error");
                isok = 'N';
                ts.putback(t);
            }
            Token h = ts.get();
            if(h.kind=='!')
                return jiecheng(d);
            ts.putback(h);
            return d;
        }

        case'8':{                       //数字则直接返回
            
            Token d = ts.get();
            if(d.kind=='!'){
                return jiecheng(t.value);
            }
            ts.putback(d);
            return t.value;
        } 

        case'+':                       //处理一元加
            return primary();

        case'-':                       //处理一元减
            return -primary();

        case'A':{                      //处理ANS
            Token a = ts.get();
            Token b = ts.get();
            if (a.kind=='N'&&b.kind=='S'){
                Token d = ts.get();
                if(d.kind=='!'){
                    return jiecheng(ans);
                }
                ts.putback(d);
                return ans;
            }
        }

        default:{                            //错误处理
            if(isok!='N')error("error");            
            isok = 'N';
            }
            return 0;
    }
}

double term(){
    double left = primary();   //获得一个primary
    Token t = ts.get();        //从token流中读取下一个token
    while (true)
    {
        switch (t.kind)        //分情况处理T*P,T/P和T%P
        {
            case'*':           //处理*
                left *= primary();
                t = ts.get();
                break;

            case'/':{          //处理/ 
                double d= primary();
                if (d==0){
                    if(isok!='N')error("error");
                    //ts.clear();
                    isok = 'N';
                }
                left /= d;
                t = ts.get();
                break;
            }

            case'%':{         //处理%  
                double h = primary();
                int i1 = int(left);
                int i2 = int(h);
                if (i2==0||left!=int(left)||h!=int(h)){
                    if(isok!='N')error("error");
                    //ts.clear();
                    isok = 'N';
                    return 0;
                    break;
                    }
                left = i1 % i2;
                t = ts.get();
                break;
                }
                
            default:                //其他情况，将t放回Token_stream
                ts.putback(t);
                return left;
        }
    }
}

double expression(){
    double left = term();   //获得一个term
    Token t = ts.get();     //从token流中读取下一个token
    while (true)
    {
        switch (t.kind)     //分情况处理E+T和E-T
        {
            case'+':        //处理+
                left += term();
                t = ts.get();
                break;
            case'-':        //处理-
                left -= term();
                t = ts.get();
                break;
            default:        //其他情况将t放回Token_stream
                ts.putback(t);
            return left;
        }
    }
}
#endif
