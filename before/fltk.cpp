#include <vector>
#include <FL/Fl.H>
#include <windows.h>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <math.h>
#include<iostream>

using namespace std;

// SIMPLE WIDGET THAT DRAWS AN 'X'
class line : public Fl_Widget {
public:
    line(int X, int Y, int W, int H, const char*L=0) : Fl_Widget(X,Y,W,H,L) {
    }
    void draw() {
        // DRAW BLACK 'X'
        fl_color(FL_BLACK);
        int x1 = x(),       y1 = y();
        int x2 = w(),       y2 = h();
        fl_line(x1, y1, x2, y2);

        //fl_line(x1, y2, x2, y1);
    }
};
vector<vector<int>> grow(vector<vector<int>> &TP){
    vector<vector<int>> Back;
    Back.push_back(TP[0]);
    vector<int> new1(2);
    vector<int> new2(2);
    vector<int> new3(2);
    int xd = (-TP[0][0] + TP[1][0]);
    int yd = (-TP[0][1] + TP[1][1]);
    double xyd = sqrt(xd * xd + yd * yd);
    

    double d = xyd / 3 * sqrt(3) / 2;
    cout << xyd << " " << d << endl;

    new1[0] = TP[0][0] + xd / 3;
    new1[1] = TP[0][1] + yd / 3;
    new3[0] = TP[0][0] + xd / 3 * 2;
    new3[1] = TP[0][1] + yd / 3 * 2;

    vector<double> dir(2);
    dir[0] = xd / xyd;
    dir[1] = yd / xyd;

    new2[0] = TP[0][0] + xd / 2 + d * (-dir[1]);
    new2[1] = TP[0][1] - yd / 2 - d * (dir[0]);

    Back.push_back(new1);
    Back.push_back(new2);
    Back.push_back(new3);
    Back.push_back(TP[1]);
    return Back;
}

int main() {
    
    Fl_Double_Window win(500,700,"Koch line");

    vector<vector<int>> points;
    vector<int> point1(2);
    vector<int> point2(2);
    point1[0] = 50;
    point1[1] = 400;
    point2[0] = 450;
    point2[1] = 400;
    points.push_back(point1);
    points.push_back(point2);
    
    vector<vector<int>> points_back;
    points_back = grow(points);

    //line X(points_back[0][0],points_back[0][1],points_back[1][0],points_back[1][1])
    line draw_1(points_back[0][0],points_back[0][1],points_back[1][0],points_back[1][1]);
    line draw_2(points_back[1][0],points_back[1][1],points_back[2][0],points_back[2][1]);
    line draw_3(points_back[2][0],points_back[2][1],points_back[3][0],points_back[3][1]);
    line draw_4(points_back[3][0],points_back[3][1],points_back[4][0],points_back[4][1]);

    //win.resizable(draw_x);
    win.show();
    return(Fl::run());
}