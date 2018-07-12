#include <iostream>
#include <string>
#include <random>
#include <stack>
#include<queue>
#include<map>
#include "stdio.h"
#include "windows.h"

#define DENSITY 5
#define RED     "2"
#define BLUE   "0"
#define YELLOW  "1"
using namespace std;

void set_console_color(unsigned short color_index)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_index);
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
            else if(maze[i][j]==5){
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
        if(X<point.X){
            return X < point.X;
        }
        else if(X==point.X) {
            return Y < point.Y;
        }
        else{
            return X < point.X;
        }
        
    }
};

struct Node{
    Point data;
    Point before;
    Node(Point p1,Point p2){
        data = p1;
        before = p2;
    }
};

map<Point, Point> maplist;
vector<vector<int>> maze;

stack<Node> find(Node tempN){
    int height = maze.size();
    int width = maze[0].size();
    Point temp = tempN.data;

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

   
    
    vector<int> use;
    for (int i = 0; i < 8; i++) //8个点
    {
        test = Points[i];
        if(test.X>=0 && test.X<height && test.Y>=0 &&  test.Y<=width &&  maze[test.X][test.Y]!=0 ){ //路
            if(maze[test.X][test.Y]==1){    //未走过的路(1)
                // return test;
                use.push_back(i);
                maze[test.X][test.Y] = 2;
                if(maplist.count(test)==0){
                    //map<Point, Point> m=maplist;
                    maplist[test] = temp;
                }
            }
            
          
        }
    }
    stack<Node> back;
    for (int p:use){
        Point t = Points[p];
        back.push(Node(t, temp));
    }
    return back;
}

stack<Point> getway(Node theOne){
    // string back;
    stack<Point> Sstack;
    map<Point, Point> m=maplist;
    //Node p = *theOne;
    while (theOne.before.X!=-3&&theOne.before.Y!=-3)
    {
        //draw(maze);
        // cout << maplist.size()<<endl;
        Sstack.push(theOne.data);
        theOne.data = theOne.before;
        theOne.before = maplist[theOne.before];
    }
    Sstack.push(theOne.data);
    
    return Sstack;
}

void NextStack(stack<Node> &before){
   
    Node aNode(Point(0,0),Point(0,0));

    stack<Node> backS;
    int sons=0;
    int nodes = before.size();
    while (!before.empty())
    {
        aNode = before.top();
        before.pop();
        stack<Node> Son=find(aNode);
        if(Son.empty()){
            sons++;
            // cout << datalist["aal"];
            // cout << datalist["aas"];
            // cout << endl;
            // back = "No way!";
        }
        while (!Son.empty())
        {
            aNode = Son.top();
            Son.pop();
            backS.push(aNode);
        }
    }
    if(sons==nodes){
        stack<Node> zero;
        before = zero;
    }
    before = backS;

}

bool canfindway(queue<stack<Node>> &workQ,Point end,stack<Point> &back){
    stack<Node> temp;
    
    temp = workQ.front();
    stack<Node> next = temp;
    workQ.pop();
    

    Node aNode(Point(0,0),Point(0,0));
    while(!temp.empty()){
        aNode = temp.top();
        temp.pop();
        
        if(aNode.data==end){
            back = getway(aNode);
            return true;
        }
        //cout << i << endl;
    }
    
    NextStack(next);

    workQ.push(next);
    if(next.empty()){
        return false;
    }
    return canfindway(workQ, end, back);

}

bool solve( Point start, Point end,stack<Point> &back){
    queue<stack<Node>> workQ;
    stack<Node> temp;
    temp.push(Node(start,Point(-3,-3)));
    maze[start.X][start.Y] = 2;
    maplist[start] = Point(-3,-3);
    workQ.push(temp);
    if(canfindway(workQ,end,back)){
        return true;
    }
    return false;
    
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

void getsize(int &width,int &height){
    cout << "Please input the width:" ;
    cin >> width;
    
    cout << "Please input the height:";
    cin >> height;
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
    maze = generate(width, height);

    vector<vector<int>> maze1=maze;
    draw(maze);

    int x1;
    int y1;
    int x2;
    int y2;

    getpos(x1,y1,x2,y2);
    stack<Point> back;
        
    if (solve( Point(x1, y1), Point(x2, y2), back))
    {
        cout << "OK" << endl;
    }
    cout << endl;

    Node temp(Point(0,0),Point(0,0));
    cout << back.size() << endl;
    while(!back.empty()){
        temp.data = back.top();
        back.pop();
        maze1[temp.data.X][temp.data.Y] = 5;
    }
    

    draw(maze1);
    char ch;
    cin >> ch;
    return 0;
}
