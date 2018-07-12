#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<int> a(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    a.insert(a.begin(), 111);
    for (int i = 0; i < a.size();i++){
        cout << a[i] << endl;
    }
    char ch;
    cin >> ch;
    return 0;
}