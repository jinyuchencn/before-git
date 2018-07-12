#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
void insertsort(vector<string> &Words,vector<int> &WordsNumber ){
    int num = 0;
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
            cout << num;
            num++;
        }
    }
}
int main(){
    ifstream SSstream;
    vector<string> Words;
    vector<int> WordsNumber;
    string data;

    SSstream.open("shakespeare.txt",ios::in);
    int num = 0;

    while(!SSstream.eof()){
        SSstream >> data;
        if(count(Words.begin(),Words.end(),data)!=0){
            int index = 0;
            for (int i = 0; i < Words.size(); i++)
            {
                if (Words[i]!=data){
                    index += 1;
                }
                else{
                    break;
                }
            }
            WordsNumber[index] += 1;
        }
        else{
            Words.push_back(data);
            WordsNumber.push_back(1);   
        }  
        cout << num<<endl;
        num++;
    }
    insertsort(Words, WordsNumber);
    for (int i = 0; i < 10; i++)
        {
            cout << Words[i] << WordsNumber[i] << endl;
        }

    char ch;
    cin >> ch;
    return 0;
}