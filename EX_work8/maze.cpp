
#include <iostream>
#include <string>
#include <random>
#include <stack>
#include<map>
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

    bool operator< (const Point& point) const
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
    vector<int> use;
    for (int i = 0; i < 8; i++) //8个点
    {
        test = Points[i];
        if(test.X>=0 && test.X<height && test.Y>=0 &&  test.Y<=width &&  maze[test.X][test.Y]!=0 ){ //路
            if(maze[test.X][test.Y]==1){    //未走过的路(1)
                // return test;
                use.push_back(i);
            }
            if(maze[test.X][test.Y]==9){    //已走过不可走的路(9)
                t++;
            }
            n++;
        }
    }
    if(t==n){   //周围的路都不可走
        return Point(-2, -2);     //无路可走
    }
    if(use.size()!=0){
        int R = rand() % use.size();   //从可用点中返回一个点
        return Points[use[R]];
    }
    return Point(-1,-1);    //退回上一个点(2)
}


bool solve(vector<vector<int>> &maze, Point start, Point end,stack<Point> &path){
/*1、找到start，将其设为走过，压进stack
 *2、检测8个方向的点，随机选点检测，找到一个没走过的点，走过去，将其压入stack，设为N
 *3、重复2
 *4、走到周围没有没走过的点，从正在走的路退到上一个点,并将该点设为不可通过
 *5、
 */
    // Point temp;
    // temp = start;
    // Point next=find(start,maze);
    path.push(start);
    if (start == end) //到终点
    {
        maze[start.X][start.Y] = 2;
        return true;
    }

    else if (start == Point(-1, -1))   //此路不通，将该点设为不通，从上一个点继续找
    {
        path.pop();

        maze[path.top().X][path.top().Y] = 9;
        path.pop();
        // path.pop();
        Point next=find(path.top(),maze);
        return solve(maze, next, end, path);
    }

    else if(start==Point(-2,-2)){   //周围无路可走
        return false;
    }

    else{               //正常的点，将点设为走到，然后走下一个点
        maze[start.X][start.Y] = 2;
        Point next=find(start,maze);
        return solve(maze, next, end, path);
        
    }  
    
    // Point next=find(temp,maze);

    //return solve(vector<vector<int>> & maze, Point temp, Point end, stack<Point> & path);

    // if (next == Point(-1, -1))
    // {
    //     temp = path.top();
    //     maze[temp.X][temp.Y] = 9;
    //     path.pop();
    //     temp = path.top();
    // }
    // else if(next==Point(-2,-2)){
    //     return false;
    // }
    // else{
    //     temp = next;
    //     path.push(temp);
    //     maze[temp.X][temp.Y] = 2;
    // }  

}


vector<vector<int> > generate(int width, int height)
{
    mt19937 rng;
    rng.seed(random_device()());

    default_random_engine fixed;
    uniform_int_distribution<int> distribution(0, 9);

    vector<vector<int>> maze(height, vector<int>(width));
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            maze[i][j] = distribution(fixed) < DENSITY ? 1 : 0;
        }
    }

    return maze;
}
void getsize(int &width,int &height){
    cout << "Please input the width:" ;
    cin >> width;
    
    cout << "Please input the height:";
    cin >> height;
}

void draw(vector<vector<int>> &maze){
    int height = maze.size();
    int width = maze[0].size();
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if (maze[i][j]==0){
                set_console_color(7);
                cout<<maze[i][j];
            }
            else if (maze[i][j] == 1)
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
    set_console_color(7);
}
void getpos(int &x1,int &y1,int &x2,int &y2){
    // set_console_color(7);
    cout << "Please input the x of start point:";
    cin>>x1;
    cout<<"Please input the y of start point:";
    cin>>y1;
    cout<<"Please input the x of end point:";
    cin>>x2;
    cout<<"Please input the y of end point:";
    cin>>y2;
    cout << endl;
}

int main()
{
    int width;
    int height;

    getsize(width,height);

    mt19937 rng;
    rng.seed(random_device()());

    uniform_int_distribution<int> distribution(0, 9);

    vector<vector<int> > maze = generate(width, height);
    draw(maze);
   
    int x1;
    int y1;
    int x2;
    int y2;
    getpos(x1,y1,x2,y2);


    vector<stack<Point>> Paths;
    vector<vector<vector<int>>> mazes;
    for (int i = 0; i < 10; i++){
        stack<Point> path;
        vector<vector<int> > OneMaze = maze;
        
        if (solve(OneMaze, Point(x1, y1), Point(x2, y2), path))
        {
            mazes.push_back(OneMaze);
            Paths.push_back(path);
        }
    }

    cout << endl;
    if(mazes.size()==0){
        cout << "No way!" << endl;
    }
    else{
        map<int, vector<vector<int>>> result;
        for (int i = 0; i < Paths.size();i++){
            result[Paths[i].size()] = mazes[i];
        }
        map<int, vector<vector<int>>>::iterator iter;
        
        int i=0;
        for (iter = result.begin(); iter != result.end(); iter++)
        {
            if(i==3){
                break;
            }
            cout << iter->first << endl;
            draw(iter->second);
            i++;
        }

    }

    
    char ch;
    cin >> ch;
    return 0;
}
