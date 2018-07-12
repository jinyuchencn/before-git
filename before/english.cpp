#include<iostream>
#include<vector>
#include <cstdio>  
#include <iomanip>

using namespace std;

int main(){
    int order = 7;

    /*cout << "Please input the order of magic squares: " << endl;
    cin >> order;*/
    vector<vector<int> >magic(order, vector<int>(order, 0));
    
    for (int i = 0; i < order ; i++)
    {
        for (int j = 0; j < order; j++)
        {
            magic[i][j] = 0;
        }
    }
    int row = 0;
    int col = order / 2;

    magic[row][col] = 1;
    for (int i = 2; i < order*order + 1; i++)
    {
        if (magic[(row - 1 + order) % order][(col + 1) % order] == 0)
        {
            row = (row - 1 + order) % order;
            col = (col + 1) % order;
        }
        else
        {
            row = (row + 1) % order;
        }
        magic[row][col]=i;
        //cout << row << col << magic[row][col] << endl;
    }
    for (int i = 0; i < order ; i++)
    {
        for (int j = 0; j < order; j++)
        {
            cout <<setw(4)<< magic[i][j];
        }
        cout << endl;
    }
    char ch;
    cin >> ch;
    return 0;
}