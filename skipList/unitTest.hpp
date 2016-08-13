//
//  unitTest.hpp
//  skipList
//
//  Created by Chris on 16/8/9.
//  Copyright © 2016年 Chris. All rights reserved.
//

#ifndef unitTest_hpp
#define unitTest_hpp

#include "skipList.hpp"

namespace std
{
    
    /* 单元测试， 各种测试 */
    void unitTest();

    /* skipListNode 测试 */
    void skipListNodeTest();

    /* skipListNode 自定义比较函数 */
    bool skipListNode__cmp(int var1, int var2);
    
    
    /* 测试 skipList 的 构造函数 和 析构函数 */
    void skipListFirstTest();
    
    
    /* int 类型比较 */
    bool intCmp(int var1, int var2);
    
}

#endif /* unitTest_hpp */
