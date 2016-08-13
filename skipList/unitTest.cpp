//
//  unitTest.cpp
//  skipList
//
//  Created by Chris on 16/8/9.
//  Copyright © 2016年 Chris. All rights reserved.
//

#include "unitTest.hpp"
#include <string>

/* 进行各种单元测试 */
void std::unitTest()
{
    /* skipListNode 测试 */
    std::skipListNodeTest();
    
    /* 测试 skipList 的析构 和 构造函数 */
    std::skipListFirstTest();
    
}

/* 自定义函数测试 */
bool std::skipListNode__cmp(int var1, int var2)
{
    return var1 < var2;
}

/* skipListNode 测试 */
void std::skipListNodeTest()
{
    auto pVar1 = new __skipListNode < int > (4);
    auto pVar2 = new __skipListNode < int > (5);
    
    

    
    std::cout << *pVar1->__t << std::endl;
    std::cout << *pVar2->__t << std::endl;
}

template < typename __T >
struct __less {
    
    bool operator() (__T &var1, __T &var2) {
        return var1 < var2;
    }
};

typedef struct stu student;
struct stu {
    unsigned int ID;
    std::string name;
    char sex;
    unsigned int math;
    
    bool operator () (student & var1, student & var2) {
        return var1.ID < var2.ID;
    }
};


void std::skipListFirstTest()
{
    student a, b, c;
    skipList < student, student > * p = new skipList < student, student > ( 10 );
    
    a.ID = 1;
    a.name = "a";
    a.sex = 'N';
    a.math = 95;
    
    b.ID = 2;
    b.name = "b";
    b.sex = 'G';
    b.math = 5;
    
    p->insert(c);
    p->insert(b);
    
    c.ID = 1;
    c.name = "c";
    c.sex = 'G';
    c.math = 0;
    
    p->insert(a);
    std::cout << p->find(a, c) << std::endl;
    std::cout << c.ID << std::endl;
    std::cout << c.name << std::endl;
    std::cout << c.sex << std::endl;
    std::cout << c.math << std::endl;
    std::cout << std::endl;
    
    delete p;
}

