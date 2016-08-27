//
//  MainMenu.hpp
//  Gobang
//
//  Created by Chris on 16/8/25.
//
//

#ifndef MainMenu_hpp
#define MainMenu_hpp

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Setting.hpp"
#include "SelectedPlayingLevel.hpp"

class MainMenu : public cocos2d::Layer
{
public:
    
    static cocos2d::Scene * createScene();
    
    virtual bool init();
    
    // 退出按钮
    void menuCloseCallback(cocos2d::Ref * pSender);
    
    // 人机博弈按钮
    void menuPlayWithComputerCallback(cocos2d::Ref * pSender);
    
    // 测试按钮
    void menuTestCallback(cocos2d::Ref * pSender);
    
    // 设定按钮
    void menuSettingCallback(cocos2d::Ref * pSender);
    
    // 进入 场景 动画结束时 操作
    void onEnterTransitionDidFinish();
    
    CREATE_FUNC(MainMenu);
};

#endif /* MainMenu_hpp */
