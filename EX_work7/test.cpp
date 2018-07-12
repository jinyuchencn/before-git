#include "stdio.h"
#include "windows.h"
#include<iostream>
using namespace std;
void set_console_color(unsigned short color_index)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_index);
}

int main()
{
    set_console_color(6);
    printf("%s", "hello");
    set_console_color(9);
    printf("%s\n", " world");
    char ch;
    cin >> ch;

    return 0;
}