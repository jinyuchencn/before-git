#include<iostream>
#include<cmath>
#include <iomanip>
using namespace std;
int main(){
    double a, b, c;    
    
    cin >> a >> b >> c;
    if (!cin){
        cout << "error" << endl;     
        return 0;
    }
    double delta;
    delta = b * b - 4 * a * c;
    
    if (delta>0)
    {
        double result1, result2;
        result1 = (-b - sqrt(delta)) / (2 * a);
        result2 = (-b + sqrt(delta)) / (2 * a);
        if (result1 < result2)
        {
            cout << setiosflags(ios::fixed)<<setprecision(2) << result2 << " ";
            cout<< setiosflags(ios::fixed)<<setprecision(2) << result1 << endl;
        }
        else
        {
            cout << setiosflags(ios::fixed)<<setprecision(2) << result1 << " ";
            cout << setiosflags(ios::fixed)<<setprecision(2) << result2 << endl;
        }
    }
    else if (delta==0)
    {
        double result1;
        result1 = -b / (2 * a);
        cout << setiosflags(ios::fixed)<<setprecision(2) <<result1 << endl;
    }
    else
    {
        cout << "invalid" << endl;
    }
    char ch;
    cin >> ch;
    return 0;
}