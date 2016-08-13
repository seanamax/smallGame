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
    
    
    /* 第一组测试 skipList */
    void skipListFirstTest();
    
    /* 第二组测试 skipList */
    void skipListSecondTest();
    
    /* int 类型比较 */
    bool intCmp(int var1, int var2);
    
}

#endif /* unitTest_hpp */
