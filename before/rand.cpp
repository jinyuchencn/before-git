#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<vector>
using namespace std;
int main(){
    int i;
    srand((unsigned long) time(NULL));
    printf("RAND_MAX=%d\n", RAND_MAX);
    vector<int> randnum;
    for (i = 0; i < 12;i++){
        int a = rand() / 522;
        while(in(randnum,a)){
            randnum.push_back(a);
            printf("random number %d:%d\n", i + 1, a);
        }

    return 0;
}