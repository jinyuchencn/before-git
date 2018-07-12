#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include<sstream>
#include<time.h>

using namespace std;

map<string, map<string, string>> order_map;
map<string, map<string, string>> buyer_map;
map<string, map<string, string>> good_map;

void order(string orderid){
    clock_t start_time = clock();
    string buyerid;
    string goodid;
    buyerid = order_map[orderid]["buyerid"];
    
    goodid = order_map[orderid]["goodid"];

    string s_price = good_map[goodid]["price"] ;
    string s_amount = order_map[orderid]["amount"];
    double price;
    double amount;
    stringstream ss;
    ss << s_price;
    ss >> price;
    ss.clear();
    ss<< s_amount;
    ss >> amount;
    cout << "orderid:" << orderid << endl;
    cout<< "buyername:" << buyer_map[buyerid]["buyername"] << endl;
    cout << "goodname:" << good_map[goodid]["good_name"] << endl;
    cout << "amount:"<<order_map[orderid]["amount"] << endl;
    cout << "price:" << good_map[goodid]["price"] << endl;
    cout  <<"amount*price:"<< amount * price << endl;

    clock_t end_time = clock();
    double run_time = end_time - start_time;
    
    cout << "time consuming:" << run_time <<"ms"<< endl;

}

void buyer(string buyerid){
    clock_t start_time = clock();
    double orders = 0;
    double payments = 0;
    map<string,map<string, string>>::iterator order_it;

    order_it = order_map.begin();
    while(order_it != order_map.end())
    {
        if(order_it->second["buyerid"]==buyerid){
            string orderid = order_it->first;
            string goodid = order_map[orderid]["goodid"];
            string s_price = good_map[goodid]["price"] ;
            string s_amount = order_map[orderid]["amount"];

            double price;
            double amount;

            stringstream ss;
            ss << s_price;
            ss >> price;
            ss.clear();
            ss<< s_amount;
            ss >> amount;

            orders++;
            payments += amount * price;
        }
        order_it ++;         
    }
    cout << "buyerid:" << buyerid << endl;
    cout<< "buyername:" << buyer_map[buyerid]["buyername"] << endl;
    cout << "the total number of orders:" << orders << endl;
    cout << "the total amount of payments::"<<payments << endl;

    clock_t end_time = clock();
    double run_time = end_time - start_time;

    cout << "time consuming:" << run_time <<"ms"<< endl;
}

void good(string goodid){
    clock_t start_time = clock();
    double orders = 0;
    double saled = 0;

    map<string,map<string, string>>::iterator order_it;
    order_it = order_map.begin();
    while(order_it != order_map.end())
    {
        if(order_it->second["goodid"]==goodid){
            string orderid = order_it->first;
            //string goodid = order_map[orderid]["goodid"];
            string s_price = good_map[goodid]["price"] ;
            string s_amount = order_map[orderid]["amount"];

            double price;
            double amount;

            stringstream ss;
            ss << s_price;
            ss >> price;
            ss.clear();
            ss<< s_amount;
            ss >> amount;

            orders++;
            saled += price * amount;

        }
        order_it ++;         
    }

    cout << "goodid:" << goodid << endl;
    cout<< "goodname:" << good_map[goodid]["good_name"] << endl;
    cout << "the total number of orders:" << orders << endl;
    cout << "the total number of saled:" << saled << endl;

    clock_t end_time = clock();
    double run_time = end_time - start_time;

    cout << "time consuming:" << run_time <<"ms"<< endl;
}

double getamount(string buyerid){
    // clock_t start_time = clock();
    double orders = 0;
    double payments = 0;
    map<string,map<string, string>>::iterator order_it;

    order_it = order_map.begin();
    while(order_it != order_map.end())
    {
        if(order_it->second["buyerid"]==buyerid){
            string orderid = order_it->first;
            string goodid = order_map[orderid]["goodid"];
            string s_price = good_map[goodid]["price"] ;
            string s_amount = order_map[orderid]["amount"];

            double price;
            double amount;

            stringstream ss;
            ss << s_price;
            ss >> price;
            ss.clear();
            ss<< s_amount;
            ss >> amount;

            orders++;
            payments += amount * price;
        }
        order_it ++;         
    }
    return payments;

}

map<int,int> output(){
    map<int, int> back;
    map<string, map<string, string>>::iterator it;

    it = buyer_map.begin();
    int temp=0;
    while(it != buyer_map.end())
    {
        if(temp%100==0){
            cout << "I'm working!" << endl;
        }
        double a=getamount(it->first);
        for (int i = 0; i < 10;i++)
        {
            if(a<200000*(i+1)&&a>=200000*i){
                if(back.count(1000000*i)==0){
                    back[200000 * i] = 1;
                    break;
                }
                else{
                    back[200000 * i] += 1;
                    break;
                }
                // break;
                // back[1000000 * i] += 1;
            }
        }
            it++;
            temp++;
    }
    return back;
}

int main(){

    map<string, string> zero_map;

    vector<string> file_name{
    "D:/my_vscode/C++code/ex_work2/buyer.0.0",
    "D:/my_vscode/C++code/ex_work2/buyer.1.1",
    "D:/my_vscode/C++code/ex_work2/good.0.0",
    "D:/my_vscode/C++code/ex_work2/good.1.1",
    "D:/my_vscode/C++code/ex_work2/good.2.2",
    "D:/my_vscode/C++code/ex_work2/order.0.0",
    "D:/my_vscode/C++code/ex_work2/order.0.3",
    "D:/my_vscode/C++code/ex_work2/order.1.1",
    "D:/my_vscode/C++code/ex_work2/order.2.2"
    };

    ifstream data_f;
    

 /*order_map <orderid,map<createtime,value>
                      map<buyerid,value>
                      map<goodid,value>
                      map<remark,value> 
                      map<amount,value>>*/
   for (int i = 5; i <= 8; i++) 
    {
        string data;
        string m0;
        string m10;
        string m11;

        data_f.open(file_name[i], ios::in);
        if (data_f.fail()) {
            cout << "fail";
        }
        while(!data_f.eof()){
        data_f>>data;

        if(data.substr(0,5)=="order"){
            m0 = data.substr(8);
            order_map[m0] = zero_map;
        }
        else if(data.substr(0,5)=="creat"){
            order_map[m0]["createtime"] = data.substr(11);
        }
        else if(data.substr(0,5)=="buyer"){
            order_map[m0]["buyerid"] = data.substr(8);
        }
        else if(data.substr(0,5)=="goodi"){
            order_map[m0]["goodid"] = data.substr(7);
        }
        else if(data.substr(0,5)=="amoun"){
            order_map[m0]["amount"] = data.substr(7);
        }
        else if(data.substr(0,5)=="remar"){
            order_map[m0]["remark"] = data.substr(7);
        }
        else if(data.substr(0,5)=="done:"){
            order_map[m0]["done"] = data.substr(5);
        }
        else {}
        
        }
        data_f.close();
    }
    

/*good_map <goodid,map<salerid,value>
                   map<good_name,value>
                   map<description,value>
                   map<price,value>>*/
    for (int i = 2; i <= 4; i++)
    {
        //cout << i << endl;
        string data;
        string m0;
        string m10;
        string m11;

        data_f.open(file_name[i], ios::in);
        if (data_f.fail()) {
            cout << "fail" << endl;
            
        }
        while(!data_f.eof()){
        data_f>>data;

        if(data.substr(0,6)=="goodid"){
            m0 = data.substr(7);
            good_map[m0] = zero_map;
        }
        else if(data.substr(0,6)=="saleri"){
            good_map[m0]["salerid"] = data.substr(8);
        }
        else if(data.substr(0,6)=="good_n"){
            good_map[m0]["good_name"] = data.substr(10);
        }
        else if(data.substr(0,6)=="price:"){
            good_map[m0]["price"] = data.substr(6);
        }
        else if(data.substr(0,6)=="descri"){
            good_map[m0]["description"] = data.substr(12);
        }
        else {}
        }   

        data_f.close();
    }

/*buyer_map <buyerid,map<contactphone,value>
                     map<address,value>
                     map<buyername,value>*/  
    for (int i = 0; i <= 1; i++)                                                                     
    {
        string data;
        string m0;
        string m10;
        string m11;

        data_f.open(file_name[i], ios::in);
        while(!data_f.eof()){
        data_f>>data;

        if(data.substr(0,7)=="buyerid"){
            m0 = data.substr(8);
            buyer_map[m0] = zero_map;
        }
        else if(data.substr(0,7)=="contact"){
            buyer_map[m0]["contactphone"] = data.substr(13);
        }
        else if(data.substr(0,7)=="address"){
            buyer_map[m0]["address"] = data.substr(8);
        }
        else if(data.substr(0,7)=="buyerna"){
            buyer_map[m0]["buyername"] = data.substr(10);
        }
        else {}
        }   
        data_f.close();
    }

    cout << "finish"<<"\n"<<"the size of order is:"<<order_map.size()<<" "
    <<"the size of good is:"<<good_map.size()<<" "
    <<"the size of order is:"<<buyer_map.size()<<endl;
    // cout << "please input orderid:XXXXXXXXX to get the information of order" << endl;
    // cout << "please input goodid:XXXXXXXXX to get the information of good" << endl;
    // cout << "please input buyerid:XXXXXXXXX to get the information of buyer" << endl;
    string inf;
    
    


    // while(cin >> inf){
    // if(inf.substr(0,3)=="ord"){
    //     order(inf.substr(8));
    // }
    // else if(inf.substr(0,3)=="buy")
    //     buyer(inf.substr(8));
    
    // else
    //     good(inf.substr(7))
    //     ;
    // }
    map<int, int> data;
    data=output();
    map<int,int>::iterator it;

    it = data.begin();

    while(it != data.end())
    {
        cout << it->first <<" "<<it->second << endl;
        it++;         
    }

    cin >> inf;
    return 0;
}