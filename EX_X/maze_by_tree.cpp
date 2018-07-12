#include <iostream>
#include <string>
#include <random>
#include<stack>
#include<queue>
#include<vector>
#include<map>
#include <algorithm> 
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
    Point pos;
    // int data;
    Node *father;
    vector<Node*> children;
};

class Tree{
    private:
        Node *root;
    public:
        Tree(vector<vector<int>> &maze, Point start);
        Tree(Node *a,int s) { root = a; }
        ~Tree();

        Node *DFS(Point end,stack<Point> &Dway);
        stack<Point> getway(Node* end);
        Node *BFS(Point end);
};

bool in(Point t,const vector<vector<int>> &maze){
    int height = maze.size();
    int width = maze[0].size();
    if(t.X>=0 && t.X<height && t.Y>=0 &&  t.Y<=width ){
        return true;
    }
    else{
        return false;
    }
}
vector<Node *> findall(Node* node,const vector<vector<int>> &maze){
    
    Point temp = node->pos;
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
    vector<Node *> back;
    while(back.size()!=0){
        back.pop_back();
    }

    for (int i = 0; i < 8; i++) //8个点
    {
        test = Points[i];
        if(in(test,maze)){
            if(maze[test.X][test.Y]==1){
                Node *one = new Node;
                one->pos = test;
                back.push_back(one);
            }
        }
    }
    random_shuffle(back.begin(),back.end());
    return back;
}

void BFG(Node* &root,vector<vector<int>> &maze){
/* 1、找到与root相连的所有点，将其设为root的children，其父设为root
 * 2、这些点在maze中设为已用
 * 3、这些点的下一个点
 */
    queue<Node *> Q;
    Q.push(root);
    maze[root->pos.X][root->pos.Y] = 2;
    while(!Q.empty()){
        Node *temp = Q.front();
        Q.pop();


        vector<Node *> next = findall(temp,maze);
        if(next.size()!=0){
            for (int i = 0; i < next.size();i++){

                maze[next[i]->pos.X][next[i]->pos.Y] = 2;
                temp->children.push_back(next[i]);
                next[i]->father = temp;
                
                Q.push(next[i]);
            }
        }
    }

}

Tree::Tree(vector<vector<int>> &maze, Point start){
    Node *top = new Node;
    top->pos = start;
    // top->data = maze[start.X][start.Y];
    top->father = NULL;
    while(top->children.size()!=0){
        top->children.pop_back();
    }
    root = top;
    BFG(root, maze);
}

Tree::~Tree(){
    // root

}

Node* Tree::DFS(Point end,stack<Point> &Dway){
    if(root->pos==end){
        Dway.push(root->pos);
        return root;
    }
    else if(root->children.size()!=0){
        Dway.push(root->pos);
        vector<Node*> vs = root->children;
        random_shuffle(vs.begin(),vs.end());
        for (int i = 0; i < vs.size();i++){
            if (vs[i] != NULL){
                Dway.push(vs[i]->pos);
            }
            Tree temp_Tree(vs[i],0);
            Node *s = temp_Tree.DFS(end,Dway);
            if(s!=NULL){
                if(s->pos==end){
                    return s;
                }
            }
            //Dway.pop();
        }
    }
    return NULL;
    
}
stack<Point> Tree::getway(Node* end){
    stack<Point> way;
    if(end==NULL){
        return way;
    }
    while(end!=NULL){
        way.push(end->pos);
        end = end->father;
    }
    return way;
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
    vector<vector<int>> maze;
    int width;
    int height;
    getsize(width,height);

    mt19937 rng;
    rng.seed(random_device()());
    uniform_int_distribution<int> distribution(0, 9);
    maze = generate(width, height);

    vector<vector<int>> maze0=maze;
    draw(maze);

    int x1;
    int y1;
    int x2;
    int y2;

    getpos(x1,y1,x2,y2);
/*1、根据起点跟maze生成一棵树
 *2、找终点是否在树上
 *3、树应有的功能  
 *     a能查找
 *     b能返回路径
 *4、要能产生多种路径，则随机走
 *  a生成树可以随机
 *  b遍历树可以随机
 *5、最佳方案用BFS
 */
    map<int, vector<vector<int>>> result;
    
    for (int i = 0; i < 10;i++){
        maze = maze0;
       
        Tree aTree(maze, Point(x1, y1));

        // aTree.~Tree();

        stack<Point> backway;
        Node *end = aTree.DFS(Point(x2, y2),backway);
        stack<Point> way = aTree.getway(end);

        int size = way.size();
        if(i!=0){
            way = backway;
            size = backway.size();
        }
        vector<vector<int>> maze1=maze0;
        while(!way.empty()){
            Point temp = way.top();
            way.pop();
            maze1[temp.X][temp.Y]=5;
        }
        if(size!=0){
            result[size] = maze1;

        }
    }
    int i=0;
    map<int, vector<vector<int>>>::iterator iter;
    if(result.size()>=3){
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
    else{
        cout << "No way!" << endl;
    }
    char ch;
    cin >> ch;
    return 0;
}
