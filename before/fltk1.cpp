#include <FL/Fl.H>
#include <vector>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Value_Slider.H>
#include <windows.h>
#include <FL/fl_draw.H>
#include <math.h>
using namespace std;

Fl_Double_Window *form;             //建立窗口指针
Fl_Slider *sliders[5];              //设置滑块指针

//成长函数，用递归算法计算n取各值时，Koch曲线各点的坐标
vector<vector<int>> grow(vector<vector<int>> TP,int n ){          
  if (n==0){
    return TP;
  }
  else{
    vector<int> new1(2);              //新点一
    vector<int> new2(2);              //新点二
    vector<int> new3(2);              //新点三

    int xd = (-TP[0][0] + TP[1][0]);  //原两点x距离
    int yd = (-TP[0][1] + TP[1][1]);  //原两点y距离
    double xyd = sqrt(xd * xd + yd * yd);  //原两点距离
    double d = xyd / 3 * sqrt(3) / 2;      //长出点与原线段的距离
   
    new1[0] = TP[0][0] + xd / 3;           
    new1[1] = TP[0][1] + yd / 3;
    new3[0] = TP[0][0] + xd / 3 * 2;
    new3[1] = TP[0][1] + yd / 3 * 2;

    vector<double> dir(2);             //原线段方向向量

    dir[0] = xd / xyd;
    dir[1] = yd / xyd;

    new2[0] = TP[0][0] + xd / 2 + d * (dir[1]);
    new2[1] = TP[0][1] + yd / 2 + d * (-dir[0]);

    vector<vector<int>> AB;            //分别对新的四条线段调用grow函数，并合到一起
    vector<vector<int>> BC;
    vector<vector<int>> CD;
    vector<vector<int>> DE;

    AB.push_back(TP[0]);
    AB.push_back(new1);
    BC.push_back(new1);
    BC.push_back(new2);
    CD.push_back(new2);
    CD.push_back(new3);
    DE.push_back(new3);
    DE.push_back(TP[1]);

    AB = grow(AB, n - 1);
    BC = grow(BC, n - 1);
    CD = grow(CD, n - 1);
    DE = grow(DE, n - 1);

    vector<vector<int>> Back;

    Back.insert(Back.end(), AB.begin(),AB.end()-1);
    Back.insert(Back.end(), BC.begin(),BC.end()-1);
    Back.insert(Back.end(), CD.begin(),CD.end()-1);
    Back.insert(Back.end(), DE.begin(),DE.end());

    return Back;
  }
}

//画图类，用于画出Koch曲线
class Koch: public Fl_Double_Window {              
      void draw();
  public:
      Koch(int x,int y,int w,int h,const char *l=0):
      Fl_Double_Window(x,y,w,h,l) {}
}
*test;

//实现draw函数
void Koch::draw() {
    Fl_Double_Window::draw();         
    fl_color((uchar)(sliders[0]->value()),         //RGB调色
            (uchar)(sliders[1]->value()),
            (uchar)(sliders[2]->value()));

    int n = (int)sliders[3]->value();              //Koch曲线阶数

    int x1 = 40,       y1 = 160;                   //初始化原来的两点
    int x2 = 380,       y2 = 160;
    vector<vector<int>> points;
    vector<int> point1(2);
    vector<int> point2(2);
    point1[0] = x1;
    point1[1] = y1;
    point2[0] = x2;
    point2[1] = y2;
          
    points.push_back(point1);
    points.push_back(point2);
    points = grow(points,n);

  //根据n选择画线段的数量(4的n次方条线段)    
    for (int i = 0; i < pow(4,n);i++){
            fl_line(points[i][0],points[i][1],points[i+1][0],points[i+1][1]); 
        }
}

//重画函数
void do_redraw(Fl_Widget*,void*)
{
    test->redraw();
}
//整体框架
void makeform(const char *) {
    form = new Fl_Double_Window(700,220,"Koch Curve");    //窗口属性

    sliders[0]= new Fl_Value_Slider(480,30,180,30,"R");   //颜色及阶数属性
    sliders[0]->bounds(0,255);
    sliders[1]= new Fl_Value_Slider(480,60,180,30,"G");
    sliders[1]->bounds(0,255);
    sliders[2]= new Fl_Value_Slider(480,90,180,30,"B");
    sliders[2]->bounds(0,255);
    sliders[3]= new Fl_Value_Slider(480,150,180,30,"n");
    sliders[3]->bounds(0,4);

    for (int i=0;i<4;i++) {                             //滑块事件处理
        sliders[i]->type(1);
        sliders[i]->align(FL_ALIGN_LEFT);
        sliders[i]->callback((Fl_Callback*)do_redraw);
        sliders[i]->step(1);
    }

    sliders[0]->value(255);           // 设定初始值
    sliders[1]->value(100); 
    sliders[2]->value(100); 
    sliders[3]->value(1); 

    test = new Koch(0,0,400,200);     //画图区域 

    test->end();
    form->end();
}

int main(int argc, char **argv) {
    makeform(argv[0]);          //构造
    form->show(argc,argv);      //显示
    return Fl::run();           //跑起来
}
