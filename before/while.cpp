#include<iostream>
using namespace std;
int main()
{
    int sum = 0;
    int i = 0;
    while (i <= 10)
    {
        sum += i;
        ++i;
    }
    cout << "the sum of 1 to 10 is " << sum << endl;
    char ch;
    cin >> ch;
    return 0;
}