class Token{                //定义Token类，用来表示读入的单个数据
public:
    char kind;
    double value;
    Token(char ch):         //Token分两种，一种为字符型，如：+，—，*。一种为数字型，如：4.34。
        kind(ch),value(0){}
    Token(char ch,double val):
        kind(ch),value(val){}
};

class Token_stream{          //定义Token_stream类，用来表示读入的数据流
    public:
        Token_stream();           
        Token get();         //读取一个Token
        void clear();        //清空Token_stream
        void putback(Token t);   //将未使用的Token返回
    private:                 //full表示Token_stream是否为空，buffer用来记录当前读入的Token
        bool full;         
        Token buffer;
};

Token_stream ts;             //声明使用的Token_stream

Token_stream::Token_stream():full(false),buffer(0){}        //Token_stream的构造函数，full设为false,buffer设为0