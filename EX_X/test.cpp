#include <string>  
 #include <vector> 
 #include <algorithm> 
 #include <iostream>  
using namespace std; 
 int main()  {  
  vector<string> vs; 
  vs.push_back(string ("1"));  
  vs.push_back (string ("2"));
  vs.push_back (string ("3"));
  vs.push_back (string ("4"));
  vs.push_back (string ("5"));
  vs.push_back (string ("6"));
  vs.push_back (string ("7"));
  random_shuffle(vs.begin(),vs.end()); /* 打乱顺序 */  
  for (int i = 0; i < 7; i++)  {
     cout<<vs[i]<<" ";
   } /* 显示打乱顺序后的元素 */
   cout << endl;
   random_shuffle(vs.begin(),vs.end()); /* 打乱顺序 */  
  for (int i = 0; i < 7; i++)  {
     cout<<vs[i]<<" ";
   } /* 显示打乱顺序后的元素 */
  cin.get();
  return 0;
 }
