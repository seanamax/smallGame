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

// 判断 出界
#define JUDGE_EDGE(pos) \
    (0 <= pos.x && pos.x < LIMIT_CHESSBOARD \
    && 0 <= pos.y && pos.y < LIMIT_CHESSBOARD)

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
    
private:
    
    //  第一位 置0 忽略， 12点钟方向为起点， 顺时针
    int moveX[9] = {0, 0, 1, 1, 1, 0, -1, -1, -1};
    int moveY[9] = {0, 1, 1, 0, -1, -1, -1, 0, 1};
    
    size_t calcBWNumByDirect(cocos2d::Vec2 centre, size_t direct);
    
    
public:
    
    static bool hitChessBoard;
    
    static const unsigned int LIMIT_CHESSBOARD = 19;
    
    static const unsigned int LIMIT_NUM_BW = 5;
    
    int chessboard[ LIMIT_CHESSBOARD ][ LIMIT_CHESSBOARD ];
    
    static cocos2d::Scene * createScene();
    
    virtual bool init();
    
    void menuCancelCallback(Ref * pSender);
    
    void onEnterTransitionDidFinish();
    
    virtual bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);
    
    virtual void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event);
    
    virtual void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event);
    
    // 换算矩阵点 到 实际屏幕点
    cocos2d::Vec2 convertToGL(cocos2d::Vec2 pos, int tag);

    
    // 判断 位置是否在对象上
    bool rectContainsPoint(cocos2d::Vec2 pos, int tag);
    
    // 各种显示棋子的方式
    void showBWByMatrix(cocos2d::Vec2 pos, int tag);
    
    void showBWByGLCoord(cocos2d::Vec2 pos, int BW, int tag);
    
    void showBWAllByMatrix(int tag);
    
    // 从屏幕上移除棋子的方式
    void removeBWByMatrixCoord(cocos2d::Vec2 pos);
    
    void removeAllBWByMatrix();
    
    int win(cocos2d::Vec2 pos);
    
    
    CREATE_FUNC(ChessBoard);
};


#endif /* Testing_hpp */
