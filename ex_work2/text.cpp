#include<iostream>
#include<string>
int main(){
    std::string s1 = "abcd";
    std::string s = s1.substr(1,2);
    std::cout << s << std::endl;
    return 0;
}
