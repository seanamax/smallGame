//
//  Setting.hpp
//  Gobang
//
//  Created by Chris on 16/8/26.
//
//

#ifndef Setting_hpp
#define Setting_hpp

#include "cocos2d.h"

enum
{
    Chinese = 101,
    English,
    Japanse
};

class Setting : public cocos2d::Layer
{
    
public:
    
    static bool effectSound;
    
    static bool backgroundMusic;
    
    static cocos2d::Scene * createScene();
    
    virtual bool init();
    
    // 确认按钮
    void MenuItemConfirmCallback(Ref * pSender);
    
    // 设置背景音乐
    void MenuItemToggleSettingBackgroundMusic(Ref * pSender);
    
    // 设置音效
    void MenuItemToggleSettingSoundEffect(Ref * pSender);
    
    
    // 留坑，做个语言包
    void toggleSettingLanguage(Ref * pSender);
    
    void onEnterTransitionDidFinish();
    
    //void onExitTransitionDidStart();
    
    CREATE_FUNC(Setting);
    
};


#endif /* Setting_hpp */
