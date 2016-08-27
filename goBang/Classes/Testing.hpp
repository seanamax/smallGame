//
//  Testing.hpp
//  Gobang
//
//  Created by Chris on 16/8/27.
//
//

#ifndef Testing_hpp
#define Testing_hpp

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MainMenu.hpp"
#include "Setting.hpp"

// 计算 棋子
#define CALC_BW_TAG(x, y) \
    (10 * x + y )


enum
{
    k_Bg = 101
};


enum
{
    k_Null,
    k_Black,
    k_White
};

class ChessBoard : public cocos2d::Layer
{
public:
    
    static bool hitChessBoard;
    
    static const unsigned int LIMIT_CHESSBOARD = 19;
    
    int chessboard[ LIMIT_CHESSBOARD ][ LIMIT_CHESSBOARD ];
    
    static cocos2d::Scene * createScene();
    
    virtual bool init();
    
    void menuCancelCallback(Ref * pSender);
    
    void onEnterTransitionDidFinish();
    
    virtual bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);
    
    virtual void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event);
    
    virtual void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event);
    
    
    // 判断 位置是否在对象上
    bool rectContainsPoint(cocos2d::Vec2 pos, int tag);
    
    
    void showBWByMatrix(cocos2d::Vec2 pos, int tag);
    
    void showBWByGLCoord(cocos2d::Vec2 pos, int BW, int tag);
    
    void showBWAllByMatrix(int tag);
    
    void removeBWByMatrixCoord(cocos2d::Vec2 pos);
    
    void removeAllBWByMatrix();
    
    CREATE_FUNC(ChessBoard);
};


#endif /* Testing_hpp */
