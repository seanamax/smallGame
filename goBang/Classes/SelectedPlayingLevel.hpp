//
//  SelectedPlayingLevel.hpp
//  Gobang
//
//  Created by Chris on 16/8/27.
//
//

#ifndef SelectedPlayingLevel_hpp
#define SelectedPlayingLevel_hpp

#include "cocos2d.h"


// 难度划分
enum {
    k_Simple = 3,
    k_Ordinary = 5,
    k_Difficult = 7
};

// 选择难度 层
class SelectedPlayingLevel : public cocos2d::Layer
{
public:
    
    virtual bool init();
    
    static cocos2d::Scene * createScene();
    
    // 按钮选项
    void menuSimpleCallback(Ref * pSender);
    
    void menuOrdinayCallback(Ref * pSender);
    
    void menuDifficultCallback(Ref * pSender);
    
    void menuCancelCallback(Ref * pSender);
    
    
    void onEnterTransitionDidFinish();
    
    
    CREATE_FUNC(SelectedPlayingLevel);
};

#endif /* SelectedPlayingLevel_hpp */
