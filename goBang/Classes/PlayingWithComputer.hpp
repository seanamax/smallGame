//
//  PlayingWithComputer.hpp
//  Gobang
//
//  Created by Chris on 16/8/27.
//
//

#ifndef PlayingWithComputer_hpp
#define PlayingWithComputer_hpp

#include "cocos2d.h"
#include "ChessBoard.hpp"

enum
{
    k_RetractMove = 103,
    k_Refresh,
    k_Setting,
    k_Tips,
    k_Cancel,
    k_MenuPlayingWithComputer
};



class PlayingWithComputer : public ChessBoard
{
private:
    
    static int _playingLevel;
    
    static bool _stopFind;
    
public:
    
    virtual bool init();
    
    static cocos2d::Scene * createScene();
    
    static void setLevel(int playingLevel);
    
    static void setStopFind(bool stopFind);
    
    static bool getStopFind();
    
    static int getLevel();
    
    void menuRetractMoveCallback(Ref * pSender);
    
    void menuRefreshCallback(Ref * pSender);
    
    void menuSettingCallback(Ref * pSender);
    
    void menuTipsCallback(Ref * pSender);
    
    void menuCancelCallback(Ref *pSender);
    
    void onEnterTransitionDidFinish();
    
    //virtual bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);
    
    CREATE_FUNC(PlayingWithComputer);
};

#endif /* PlayingWithComputer_hpp */
