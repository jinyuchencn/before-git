#include<iostream>
#include<vector>
using namespace std;
int main()
{
    static vector<vector<int> >magic1(3, vector<int>(3, 0));
    vector<vector<int> >magic2(3, vector<int>(3, 0));
    vector<vector<int> >magic3(3, vector<int>(3, 0));

    magic1[0][1] = 6;
    magic1[1][0] = 4;
    magic1[0][2] = 10;

    magic2[1][0] = 6;
    magic2[2][0] = 23;
    magic2[2][1] = 8;

    magic3[0][0] = 12;
    magic3[1][2] = 13;
    magic3[2][0] = 16;

    if (((magic1[1][0] == 0) && (magic1[0][1] != 0) && (magic1[2][2] != 0))||
    ((magic1[1][0] != 0) && (magic1[0][1] == 0) && (magic1[2][2] != 0))||
    ((magic1[1][0] != 0) && (magic1[0][1] != 0) && (magic1[2][2] == 0)))        
    {
        if (((magic1[1][0] == 0) && (magic1[0][1] != 0) && (magic1[2][2] != 0)))
        {
            magic1[1][0] = magic1[2][2] * 2 - magic1[0][1];
        }
        else if ((magic1[1][0] != 0) && (magic1[0][1] == 0) && (magic1[2][2] != 0))
        {
            magic1[0][1] = magic1[2][2] * 2 - magic1[1][0];
        }
        else 
        {
            magic1[2][2] = (magic1[1][0] + magic1[0][1])/2;
        }
    }
    if (((magic1[0][1] == 0) && (magic1[1][2] != 0) && (magic1[2][0] != 0))||
    ((magic1[0][1] != 0) && (magic1[1][2] == 0) && (magic1[2][0] != 0))||
    ((magic1[0][1] != 0) && (magic1[1][2] != 0) && (magic1[2][0] == 0)))        
    {
        if (((magic1[0][1] == 0) && (magic1[1][2] != 0) && (magic1[2][0] != 0)))
        {
            magic1[0][1] = magic1[2][0] * 2 - magic1[1][2];
        }
        else if ((magic1[0][1] != 0) && (magic1[1][2] == 0) && (magic1[2][0] != 0))
        {
            magic1[1][2] = magic1[2][0] * 2 - magic1[0][1];
        }
        else 
        {
            magic1[2][0] = (magic1[0][1] + magic1[1][2])/2;
        }
    }
     if (((magic1[1][2] == 0) && (magic1[2][1] != 0) && (magic1[2][0] != 0))||
    ((magic1[1][2] != 0) && (magic1[2][1] == 0) && (magic1[2][0] != 0))||
    ((magic1[1][2] != 0) && (magic1[2][1] != 0) && (magic1[2][0] == 0)))        
    {
        if (((magic1[1][2] == 0) && (magic1[2][1] != 0) && (magic1[2][0] != 0)))
        {
            magic1[1][2] = magic1[2][0] * 2 - magic1[2][1];
        }
        else if ((magic1[1][2] != 0) && (magic1[2][1] == 0) && (magic1[2][0] != 0))
        {
            magic1[2][1] = magic1[2][0] * 2 - magic1[1][2];
        }
        else 
        {
            magic1[2][0] = (magic1[1][2] + magic1[2][1])/2;
        }
    }
    

    
}
/*int role1(int point1,int point2,int point3){
    if (((point1 == 0) && (point2 != 0) && (point3 != 0))||
    ((point1 != 0) && (point2 == 0) && (point3 != 0))||
    ((point1 != 0) && (point2 != 0) && (point3 == 0)))        
    {
        if (((point1 == 0) && (point2 != 0) && (point3 != 0)))
        {
            point1 = point3 * 2 - point2;
            return 1, point1;
        }
        else if ((point1 != 0) && (point2 == 0) && (point3 != 0))
        {
            point2 = point3 * 2 - point1;
            return 2, point2;
        }
        
        else 
        {
            point3 = (point1 + point2)/2;
            return 3, point3;
        }
    }
}               */