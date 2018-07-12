#include<iostream>
#include<vector>
using namespace std;
class Matrix{
    friend std::ostream & operator<< (std::ostream &out,const Matrix &M1);
    public:
      Matrix(int row, int col, vector<int> &values);
      void Tran();

    private:
      vector<vector<int>> matrix;
      char T;
};
Matrix::Matrix(int row,int col,vector<int> &values){
    
    int k = 0;
    for (int i = 0; i < row;i++){
        vector<int> temp;
        for (int j = 0; j < col;j++){
            temp.push_back(values[k]);
            k++;
        }
        matrix.push_back(temp);
    }
    T = 'A';
    
}
ostream & operator<<(ostream &out, const Matrix & M1)  
{
    int row = M1.matrix.size();
    int col = M1.matrix[0].size();
    if(M1.T!='A'){
        int k;
        k = row;
        row = col;
        col = k;
    }
    for (int i=0; i < row;i++){
        for (int j = 0; j < col; j++)
        {
            if(M1.T=='A'){
                out << M1.matrix[i][j] << " ";
            }
            else{
                out << M1.matrix[j][i] << " ";
            }
        }
        out << "\n";
    }
    return out;
}
void Matrix::Tran(){
    T = 'B';
    
}
int main(){
    while (cin)
    {
        vector<int> test_vec;
        int row;
        int col;
        int temp;
        cout << "Please input:row col vector:";
        cin >> row;
        cin >> col;
        for (int i=0; i < row * col;i++){
            cin >> temp;
            test_vec.push_back(temp);
        }
        Matrix M1(row, col, test_vec);
        cout << "before Tran:" << endl;
        cout << M1;
        M1.Tran();
        cout << "after Tran:" << endl;
        cout << M1;
    }
}