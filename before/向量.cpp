#include<iostream>
#include <vector>  
using std::vector;  
  
#define HEIGHT 5  
#define WIDTH 3  
  
int main() {  
    vector<vector<double> > array2D;  
  
    // 设置容器大小(HEIGHT x WIDTH)  
    array2D.resize(HEIGHT);  
    for (int i = 0; i < HEIGHT; ++i)  
        array2D[i].resize(WIDTH);  
  
    //放入一些数据  
    array2D[1][2] = 6.0;  
    array2D[3][1] = 5.5;  
  
    return 0;  
}  
