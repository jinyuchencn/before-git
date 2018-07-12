#include<vector>
#include<iostream>
using namespace std;
int main(){
    vector<int> a{1, 2, 3, 4, 5};
    a.erase(a.begin(), a.begin() + 1);
    cout << 0x7fff << "  " << a[0] << endl;
    return 0;
}