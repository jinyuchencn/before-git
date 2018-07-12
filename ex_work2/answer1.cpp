#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<time.h>
using namespace std;
int main(){
    clock_t start_time = clock();
    vector<string> file_name{
        "D:\\my_vscode\\C++code\\ex_work2\\buyer.0.0",
        "D:\\my_vscode\\C++code\\ex_work2\\buyer.1.1",
        "D:\\my_vscode\\C++code\\ex_work2\\good.0.0",
        "D:\\my_vscode\\C++code\\ex_work2\\good.1.1",
        "D:\\my_vscode\\C++code\\ex_work2\\good.2.2",
        "D:\\my_vscode\\C++code\\ex_work2\\order.0.0",
        "D:\\my_vscode\\C++code\\ex_work2\\order.0.3",
        "D:\\my_vscode\\C++code\\ex_work2\\order.1.1",
        "D:\\my_vscode\\C++code\\ex_work2\\order.2.2"};
    ifstream data_f;
    
    int order_number = 0;
    for (int i = file_name.size()-1; i >= file_name.size()-4; i--)
    {
        string order_data;
        data_f.open(file_name[i], ios::in);
        data_f.seekg(0, ios::end);
        if(data_f){
          
        data_f.seekg(0, ios::end);  
        order_data.resize(data_f.tellg());  
        data_f.seekg(0, ios::beg);  
        data_f.read(&order_data[0], order_data.size());  
        data_f.close();
        for (int j = 0; j < order_data.size(); j++)
        {
            if (order_data[j]=='\n'){
                order_number += 1;
                
            }
        }  
        }
    }

    cout << order_number << endl;

    
    clock_t end_time = clock();
    double run_time = end_time - start_time;
    cout << "The run time is:" << static_cast<double>(run_time)/CLOCKS_PER_SEC*1000 << "ms!" << endl;

    char ch;
    cin >> ch;
    return 0;
}