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

int main(int argc, const char * argv[]) {
    
    string str = "This is a string";
    
    cout << "Before change the string:"
    << str << endl;
    
    // using reference and to change
    for(auto &ch : str) {
        ch = 'X';
    }
    
    cout << "After changed the string:"
    << str << endl;
    
    return 0;
}
