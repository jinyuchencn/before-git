#include<iostream>
#include<map>
#include<vector>
#include<fstream>
#include<queue>
#include<random>

using namespace std;

map<string, vector<string>> getbook(){
    ifstream file;
    string filename;
    map<string, vector<string>> data;
    cout << "Please input file name:";
    while(cin){
        cin >> filename;
        file.open(filename, ios::in);
        if(file.fail()){
            cout << endl;
            cout << "Unable to open that file.  Try again." << endl;
            cout << "Please input file name:";
        }
        else
        {
            int n;
            cout << "Please input value of N:";
            cin >> n;
            string str1;
            string s;
            int size = 0;
            while (!file.eof())
            {
                // 读n-1个，形成vector，读下一个，记为s
                // vector无，建新的，有，加上新的s，s有，计数加1
                while (size!=n-1)
                {
                    file >> s;
                    str1 += s;
                    str1 += " ";
                    size++;
                }
                file >> s;
                if(file.fail()){
                    break;
                }
                if(data.count(str1)!=0){   
                    data[str1].push_back(s) ;
                }
                else{
                    vector<string> map2;
                    map2.push_back(s);
                    data[str1] = map2;
                }
                while(true){
                    char ch = str1[0];
                    str1.erase(str1.begin(),str1.begin()+1);
                    if(ch==' '){
                        break;
                    }
                }
                str1 += s;
                str1 += " ";
            }
            break;
        }
    }
    cout <<"finish" <<endl;
    return data;
}
string findone(vector<string> data){
    int size = data.size();
    int seed = rand() % size;
    return data[seed];
}
string findone(map<string, vector<string>> &data){
    map<string, vector<string>>::iterator it;
    it = data.begin();
    int size = data.size();
    int seed;
    seed = ((rand()%10000)*10000+(rand()%10000) )% size;

    for (int i = 0; i < seed;i++){
        it++;
    }
    // int n;

    vector<string> vec = it->second;
    int size1 = data.size();
    int seed1 = rand() % size1;
    return vec[seed1];

}

string generate( map<string, vector<string>> &data){
    
    map<string, vector<string>>::iterator it;
    it = data.begin();
    int N = 0;
    for(char ch:it->first){
        if(ch==' '){
            N++;
        }
    }
    N += 1;
    int size = data.size();
    int seed;
    seed = ((rand()%10000)*10000+(rand()%10000) )% size;

    for (int i = 0; i < seed;i++){
        it++;
    }
    int n;
    string begin = it->first;
    cout << "# of random words to generate (0 to quit)?";
    cin >> n;
    if(n==0){
        return "No";
    }
    if(n<=N-1){
        cout << "error,n must bigger than N-1";
        return "no";
    }
    string back;
    back += begin;
    string s;
    for (int i = 0; i < n - (N - 1) + 1; i++)
    {
        if(data.count(begin)!=0){
            s = findone(data[begin]);
        }
        else{
            s = findone(data);
        }
        back += s;
        back += " ";
        begin += s;
        begin += " ";
        while(true){
            char ch = begin[0];
            begin.erase(begin.begin(),begin.begin()+1);
            if(ch==' '){
                break;
            }
        }
    }
    return back;
}

void output(const string &data){
    if(data=="No"){
        exit(0);
    }
    if(data=="no"){
        cout << endl;
    }
    cout << data;
    cout << endl;
}

int main(){
    map<string, vector<string>> book_map = getbook();
    cout << endl;
    while (cin)
    {
         string my_book = generate(book_map);
         output(my_book);
    }
    return 0;
}