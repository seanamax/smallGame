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
#include "Engine.hpp"

#define SIMPE_WIDTH 3
#define SIMPE_DEEPTH 4

#define ORDINAY_WIDTH  3
#define ORDINAY_DEEPTH 7

#define DIFFICULT_WIDTH 3
#define DIFFICULT_DEEPTH 10

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
    
    Naina _Naina;
    
    static int _level;
    
    void _initNaina(int flag);
    
public:
    
    
    virtual bool init();
    
    static cocos2d::Scene * createScene();
    
    static void setLevel(int playingLevel);
    
    void setStopFind(bool stopFind);
    
    bool getStopFind();
    
    int getLevel();
    
    void menuRetractMoveCallback(Ref * pSender);
    
    void menuRefreshCallback(Ref * pSender);
    
    void menuSettingCallback(Ref * pSender);
    
    void menuTipsCallback(Ref * pSender);
    
    void menuCancelCallback(Ref *pSender);
    
    void onEnterTransitionDidFinish();
    
    virtual bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);
    
    CREATE_FUNC(PlayingWithComputer);
};

#endif /* PlayingWithComputer_hpp */
