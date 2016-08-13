//
//  skipList.hpp
//  skipList
//
//  Created by Chris on 16/8/9.
//  Copyright © 2016年 Chris. All rights reserved.
//

#ifndef skipList_hpp
#define skipList_hpp

#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <cassert>

//typedef struct __skipListNode skipListNode;



template < typename __T >
struct __skipListNode
{
    __T * __t;
    struct __skipListNode < __T > * next;
    
    
    
    /* 构造函数， 初始化 */
    __skipListNode(__T __t) {
        
        this->next =  NULL;
        
        this->__t = new __T;
        
        // 进行 错误 处理
        assert(this->__t);
        if(!this->__t) {
            fprintf(stderr, "Cann't new mem in struct __skipListNode construction");
        }
        
        *this->__t = __t;
        
    }
    
    /* 构造函数， 初始化2 */
    __skipListNode() {
        this->next = NULL;
        this->__t = NULL;
    }
    
};


template < typename __T, typename __Compare = std::less< __T > >
class skipList
{

public:
    // 构造函数, 输入 skipList 有 规模有多大
    skipList(unsigned int maxNum)
    {
        getMaxLevel(maxNum);
        this->head = new __skipListNode < __T >  [this->maxLevel+1];
        this->recordPath = new __skipListNode < __T > * [this->maxLevel+1];
        
        // 若分配 内存 失败， 进行错误处理
        if(!this->head) {
            fprintf(stderr, "Cann't new head array mem in skipList construction");
        }
        assert(this->head);
        
        if(!this->recordPath) {
            fprintf(stderr, "Cann't new recordPath array variable mem in skipList construction");
        }
        assert(this->recordPath);
        
        // 初始化 head 和 recordPath 数组指针
        //memset(this->recordPath, 0, maxLevel * sizeof(__skipListNode < __T > *));
        //memset(this->head, 0, maxLevel * sizeof(__skipListNode < __T > *));
        for(unsigned int i=0; i < this->maxLevel; ++ i) {
            this->head[i].next = NULL;
            //this->head[i].__t = new __T;
            //memset(this->head[i].__t, 0, sizeof __T);
        }
        
        // 初始化 random_0_1() 模拟硬币投掷函数
        time_t seedRandom = time(NULL);
        srand(seedRandom);
    }
    
    // 析构函数
    ~skipList()
    {
        // 利用 删除函数， 遍历所有头节点， 将其 删除
        for(unsigned int i=0; i < this->maxLevel; ++ i) {
            while(this->head[i].next) {
                this->del(*this->head[i].next->__t);
            }
        }
    }
    
    
    
    // 查询所要 节点
    bool find(__T & __t, __T & result) {
        
        // 初始化 返回值
        bool isFound = false;
        
        // 记录头节点
        this->recordPath[0] = this->head;
        
        // 查找， 若找到， 直接 跳出循环， 返回结果
        for(unsigned int i=0; i < this->maxLevel; ++ i) {
            
            if(i) {
                this->recordPath[i] = this->recordPath[i-1] + 1;
            }
            
            auto p__SkipListNode = this->recordPath[i]->next;
            while(p__SkipListNode && this->Comp(*p__SkipListNode->__t, __t)) {
                this->recordPath[i] = p__SkipListNode;
                p__SkipListNode = p__SkipListNode->next;
            }
            
            p__SkipListNode = this->recordPath[i]->next;
            if(p__SkipListNode) {
                if(!this->Comp(*p__SkipListNode->__t, __t) && !this->Comp(__t, *p__SkipListNode->__t)) {
                    result = *p__SkipListNode->__t;
                    isFound = true;
                    break;
                }
            }
            
        }
        
        return isFound;
    }
    
    // 插入所要 节点
    bool insert(__T & __t) {
        
        // 初始化 状态值
        bool isInserted = false;
        
        // 获得 该 路径
        this->getRecordPath(__t);
        
        // 若 已经存在该节点， 直接 修改赋值， 返回结果
        auto p__SkipListNode = this->recordPath[this->maxLevel-1]->next;
        
        
        if(p__SkipListNode && !this->Comp(__t, *p__SkipListNode->__t) && !this->Comp(*p__SkipListNode->__t, __t)) {
            
            for(unsigned int i=0; i < this->maxLevel; ++ i) {
                
                p__SkipListNode = this->recordPath[i]->next;
                
                // 判断 指针是否存在 以及 是否 相等
                if(p__SkipListNode && !this->Comp(__t, *p__SkipListNode->__t) && !this->Comp(*p__SkipListNode->__t, __t)) {
                    
                    // 赋值
                    *p__SkipListNode->__t = __t;
                    
                    // 插入成功
                    isInserted = true;
                    
                    break;
                }
            }
        }
        
        // 若是 没有该节点， 直接建立节点
        else {
            
            // 随机 生成 层数
            unsigned int tmpLevel = this->getSkipListNodeLevel();
            
            // 申请 内存 空间
            auto p__SkipListNode = new __skipListNode < __T > [ tmpLevel ];
            __T * p__t = new __T;
            
            // 判断 节点有没有生成
            assert(p__SkipListNode);
            if(!p__SkipListNode) {
                fprintf(stderr, "Cann't new mem in function insert from class skipList01");
                return isInserted;
            }
            
            assert(p__t);
            if(!p__t) {
                fprintf(stderr, "Can't new mem in function insert from class skipList02");
                return isInserted;
            }
            
            // 赋值
            *p__t = __t;
            
            // 链接
            for(unsigned int i=0, j=this->maxLevel-tmpLevel; i < tmpLevel; ++ i) {
                
                p__SkipListNode[i].__t = p__t;
                
                p__SkipListNode[i].next = this->recordPath[i+j]->next;
                this->recordPath[i+j]->next = p__SkipListNode + i;
            }
            
            // 插入 成功
            isInserted = true;
            
        }
        
        return isInserted;
    }
    
    
    // 删除 节点
    void del(__T __t)
    {
        // 获得 该路径
        this->getRecordPath(__t);
        
        // 简化 指针
        auto p__SkipListNode = this->recordPath[this->maxLevel-1]->next;
        
        // 判断 指针 是否 存在 以及 是否相等
        if(p__SkipListNode) {
            if(!this->Comp(*p__SkipListNode->__t, __t) && !this->Comp(__t, *p__SkipListNode->__t)) {
                
                __skipListNode < __T > * p__FirstSkipListNode = NULL;
                __T * p_t = NULL;
                bool isFirst = true;
                
                for(unsigned int i=0; i < this->maxLevel; ++ i) {
                    
                    p__SkipListNode = this->recordPath[i]->next;
                    
                    if(p__SkipListNode) {
                        
                        if(!this->Comp(*p__SkipListNode->__t, __t) && !this->Comp(__t, *p__SkipListNode->__t)) {
                            
                            if(isFirst) {
                                isFirst = false;
                                p_t = p__SkipListNode->__t;
                                p__FirstSkipListNode = p__SkipListNode;
                            }
                            
                            this->recordPath[i]->next = p__SkipListNode->next;

                        }
                    }
                }
                
                // 删除 整个 路径
                if(!isFirst) {
                   
                    delete p_t;
                    delete [] p__FirstSkipListNode;
                }
            }
        }
        
    }
    

    
private:
    // 定义最大层数
    unsigned int maxLevel;
    
    // 头节点， 开始节点
    __skipListNode < __T > * head;
    
    // 查询返回路径
    __skipListNode < __T > ** recordPath;
    
    
    // 获得 比较函数 指针
    __Compare Comp;
    
    
    // 随机数 0-1
    bool random_0_1()
    {
        return rand()&1;
    }
    
    // 获得 最大 层数， 由 客户 决定
    unsigned int getMaxLevel(unsigned int maxNum)
    {
        
        this->maxLevel = 0;
        
        while(maxNum) {
            
            maxNum >>= 1;
            ++ this->maxLevel;
 
        }
        
        // 若用户输入数目错误， 直接复制为1
        if(this->maxLevel == 0) {
            this->maxLevel = 1;
        }
        
        return this->maxLevel;
    }
    
    // 随机获得 SkipListNode 的 层数
    unsigned int getSkipListNodeLevel()
    {
        unsigned int tmpLevel = 0;
        while(random_0_1()) {
            ++ tmpLevel;
        }
        
        // 限制 节点 层数高过 最高层数
        if(tmpLevel > this->maxLevel) {
            tmpLevel = this->maxLevel;
        }
        
        // 若是投掷硬币， 结果为 0 层， 强制 为 1 层
        else if(!tmpLevel) {
            tmpLevel = 1;
        }
        
        return tmpLevel;
    }
    
    
    // 获得 关于 该 节点 的 查询路径， 是以后查询 或 插入 或 删除 的 基有函数
    void getRecordPath(__T &__t)
    {
        // 初始化 路径 数组, 直接复制 head 数组
        this->recordPath[0] = this->head;
        
        // 查找
        for(unsigned int i=0; i < this->maxLevel; ++ i) {
            
            // 节点下一层
            if(i) {
                this->recordPath[i] = this->recordPath[i-1] + 1;
            }
            
            // 实现 向右查找， 若 为空指针 或是 不满足比较函数， 直接跳出
            auto p__SkipListNode = this->recordPath[i]->next;
            while(p__SkipListNode && this->Comp(*p__SkipListNode->__t, __t)) {
                this->recordPath[i] = p__SkipListNode;
                p__SkipListNode = p__SkipListNode->next;
            }
        }
    }
};

#endif /* skipList_hpp */
