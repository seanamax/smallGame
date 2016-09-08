//
//  main.cpp
//  c++ primer 5th
//
//  Created by Chris on 16/9/7.
//  Copyright © 2016年 Chris. All rights reserved.
//

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::cin;
using std::string;

//
//    改写成 传统的 for 和 while 后， 代码比较麻烦和苦涩难懂
//


int main(int argc, const char * argv[]) {
    
    string str = "This is a string";
    
    cout << "Before change the string:"
    << str << endl;
    
    for(decltype(str.size()) index = 0;
        index < str.size(); ++index) {
        
        str[index] = 'X';
        
    }
    
    cout << "After changed the string:"
    << str << endl;
    
    cout << "Using the while loop" << endl;

    str = "This is a string";
    
    cout << "Before change the string:"
    << str << endl;
    
    decltype(str.size()) index = 0;
    while(index < str.size()) {
        str[index] = 'X';
        
        ++index;
    }
    cout << "After changed the string:"
    << str << endl;
    
    return 0;
}
