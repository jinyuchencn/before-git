
#include <iostream>
#include <string>
#include <random>
#include <stack>
#include "stdio.h"
#include "windows.h"

#define DENSITY 5
#define RED     "2"
#define BLUE   "0"
#define YELLOW  "1"

//0 墙(白) 1 路(蓝) 9 此路不通(黄) 2 正在走的路(红)

 
using namespace std;
void set_console_color(unsigned short color_index)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_index);
}

class Point
{
    public:
        int X;
        int Y;
    
    Point (){

    }

    Point(int x, int y)
    {
        X = x;
        Y = y;
    }

    Point& operator= (const Point& point)
    {
        if (this == &point)
        {
            return *this;
        }

        X = point.X;
        Y = point.Y;

        return *this;
    }

    bool operator == (const Point& point) const
    {
        if (X == point.X && Y == point.Y)
        {
            return true;
        } else 
        {
            return false;
        }
    }

    bool operator != (const Point& point) const
    {
        return (X != point.X || Y != point.Y);
    }
};

Point find(Point temp,const vector<vector<int> > &maze){
    int height = maze.size();
    int width = maze[0].size();

    Point P1(temp.X,temp.Y-1);
    Point P2(temp.X-1,temp.Y-1);
    Point P3(temp.X-1,temp.Y);
    Point P4(temp.X-1,temp.Y+1);
    Point P5(temp.X,temp.Y+1);
    Point P6(temp.X+1,temp.Y+1);
    Point P7(temp.X+1,temp.Y);
    Point P8(temp.X+1,temp.Y-1);

    vector<Point> Points;

    Points.push_back(P1);
    Points.push_back(P2);
    Points.push_back(P3);
    Points.push_back(P4);
    Points.push_back(P5);
    Points.push_back(P6);
    Points.push_back(P7);
    Points.push_back(P8);

    Point test;

    int t = 0;
    int n = 0;

    for (int i = 0; i < 8; i++)
    {
        test = Points[i];
        if(test.X>=0 && test.X<width && test.Y>=0 &&  test.Y<=height &&  maze[test.X][test.Y]!=0 ){
            if(maze[test.X][test.Y]==1){
                return test;
            }
            if(maze[test.X][test.Y]==9){
                t++;
            }
            n++;
        }
    }
    if(t==n){
        return Point(-2, -2);
    }

    return Point(-1,-1);
}

bool solve(vector<vector<int> > &maze, Point start, Point end)
{
/*1、找到start，将其设为走过，压进stack
 *2、检测8个方向的点，从上开始，以顺时针检测，找到一个没走过的点，走过去，将其压入stack，设为N
 *3、重复2
 *4、走到周围没有没走过的点，从正在走的路退到上一个点,并将该点设为不可通过
 *5、
 */
    Point temp;
    temp = start;
    // int height = maze.size();
    // int width = maze[0].size();
    stack<Point> path; //记录正在走过的点
    path.push(temp);
    maze[temp.X][temp.Y] = 2;
    while (temp!=end)
    {
        Point next=find(temp,maze);
        if (next==Point(-1,-1)){
            temp = path.top();
            maze[temp.X][temp.Y] = 9;
            path.pop();
            temp = path.top();
        }
        else if(next==Point(-2,-2)){
            return false;
        }
        else{
            temp = next;
            path.push(temp);
            maze[temp.X][temp.Y] = 2;
        }
    }

    return true;
}


vector<vector<int> > generate(int width, int height)
{
    mt19937 rng;
    rng.seed(random_device()());

    default_random_engine fixed;
    uniform_int_distribution<int> distribution(0, 9);

    vector<vector<int> > maze(height, vector<int>(width));
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            maze[i][j] = distribution(rng) < DENSITY ? 1 : 0;
        }
    }

    return maze;
}

int main()
{
    int width;
    int height;

    cout<<"Please input the width:";
    cin>>width;
    cout<<"Please input the height:";
    cin>>height;

    mt19937 rng;
    rng.seed(random_device()());

    uniform_int_distribution<int> distribution(0, 9);

    vector<vector<int> > maze = generate(width, height);

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            //set_console_color(6);
            if (maze[i][j] == 1)
            {
                set_console_color(9);
                cout<<maze[i][j];
            } else{
                set_console_color(7);
                cout<<maze[i][j];
            }
        }

        cout<<endl;
    }
    int x1;
    int y1;
    int x2;
    int y2;
    cout<<"Please input the x of start point:";
    cin>>x1;
    cout<<"Please input the y of start point:";
    cin>>y1;
    cout<<"Please input the x of end point:";
    cin>>x2;
    cout<<"Please input the y of end point:";
    cin>>y2;
    cout << endl;

    if(solve(maze,Point(x1,y1),Point(x2,y2))){
        cout << "OK" << endl;
    }
    else{
        cout << "NO WAY!" << endl;
    }
    cout << endl;
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            //set_console_color(6);
            if (maze[i][j] == 1)
            {
                set_console_color(9);
                cout<<maze[i][j];
            } 
            else if(maze[i][j]==2){
                set_console_color(4);
                cout<<maze[i][j];
            }
            else if(maze[i][j]==9){
                set_console_color(6);
                cout<<maze[i][j];
            }
            else{
                set_console_color(7);
                cout<<maze[i][j];
            }
        }

        cout<<endl;
    }

    char ch;
    cin >> ch;
    return 0;
}
