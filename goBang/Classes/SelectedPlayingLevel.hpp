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
#include "PlayingWithComputer.hpp"
#include "MainMenu.hpp"
#include "SimpleAudioEngine.h"

// 难度划分
enum {
    Simple = 3,
    Ordinary = 5,
    Difficult = 7
};

// 选择难度 层
class SelectedPlayingLevel : public cocos2d::Layer
{
public:
    
    // 选择难度
    static unsigned int playingWithComputerLevel;
    
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
