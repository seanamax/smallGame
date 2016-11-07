#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::cin;

int main(void)
{
//    vector<string> vec_str = { "a", "aa", "aaa" };
//
//    for(string tmp : vec_str) {
//        cout << tmp << endl;
//    }
//    
//    vector<int> v2(10, 1);
//    for(auto v : v2) {
//        cout << v << endl;
//    }
//
    
//    
//    vector<vector<int>> vec_vec_int;
//    vector<int> vec_int(10, 1);
//    
//    vec_vec_int.push_back(vec_int);
//    vec_vec_int.push_back(vec_int);
//    
//    for(auto i : vec_vec_int) {
//        for(auto j : i) {
//            cout << j << endl;
//        }
//    }

    
    vector <int> vec_int = {1, 2, 3, 4, 5};
    vec_int = {2, 3, 4};
    
    
    for(auto &v : vec_int) {
        cout << v;
    }
    cout << endl;
    
    
    
    return 0;
}
