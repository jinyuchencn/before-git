#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;
void insertsort(vector<string> &Words,vector<int> &WordsNumber ){
    for(int i = 1;i < Words.size();++i){
        for(int j = i;j > 0;--j){
            if(WordsNumber[j] < WordsNumber[j - 1]){
                int temp = WordsNumber[j];
                string ss = Words[j];

                WordsNumber[j] = WordsNumber[j-1];
                Words[j] = Words[j - 1];

                WordsNumber[j-1] = temp;
                Words[j - 1] = ss;
            }
        }
    }
}
int main(){
    vector<int> array;
    int i;
    cin >> i;
    array.push_back(i);
    while (cin.get() != '\n')   { 
        cin >> i; 
        array.push_back(i);
    }
    insertsort(array.begin()+1, array.end());
    for (int i = 1; i < array.size(); i++)
    {
        if(i==1){
            if (array[i]!=array[i+1]){
                cout << array[i]<<endl;
            }
        }
        else if (i==array.size()-1){
            if (array[i]!=array[i-1]){
                cout << array[i]<<endl;
            }
        }
        else{
            if(array[i]!=array[i-1]&&array[i]!=array[i+1]){
            cout << array[i]<<endl;
            }
        }   
    }
    char ch;
    cin >> ch;

    return 0;
}