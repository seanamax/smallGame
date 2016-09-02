//
//  ChessBoard.hpp
//  Gobang
//
//  Created by Chris on 16/8/29.
//
//

#ifndef ChessBoard_hpp
#define ChessBoard_hpp


#include "cocos2d.h"



// 计算 棋子
#define CALC_BW_TAG(x, y) \
(10 * x + y )

// 判断 出界
#define JUDGE_EDGE(pos) \
(0 <= pos.x && pos.x < ChessBoard::LIMIT_CHESSBOARD \
&& 0 <= pos.y && pos.y < ChessBoard::LIMIT_CHESSBOARD)


#define ConvertToVec2(i) \
cocos2d::Vec2(ChessBoard::moveX[i], ChessBoard::moveY[i])

// 八个方向
enum
{
    k_12OD = 1,             //  12点钟方向
    k_1AndHalfOD,           //  1半点钟方向
    k_3OD,                  //  3点钟方向
    k_4AndHaleOD,           //  4点半钟方向
    k_6OD,                  //  6点钟方向
    k_7AndHalfOD,           //  7点半钟方向
    k_9OD,                  //  9点钟方向
    k_10AndHalfOD,          //  10半点钟方向
};

// 精灵 tag
enum
{
    k_Bg = 101,
    k_Line,
    
};

// 棋子类型
enum
{
    k_Null = 0,
    k_Black = 1000,
    k_White,
    k_Except
    
};




class ChessBoard : public cocos2d::Layer
{
    
private:
    
    size_t calcBWNumByDirect(cocos2d::Vec2 centre, size_t direct);
    
    void showOneDirectLineByPos(cocos2d::Vec2 pos, int tag);
    
    
public:
    
    
    static bool hitChessBoard;
    
    static const unsigned int LIMIT_CHESSBOARD = 19;
    
    static const unsigned int LIMIT_DIRECTION = 8;
    
    static const unsigned int LIMIT_NUM_BW = 5;
    
    //  第一位 置0 忽略， 12点钟方向为起点， 顺时针旋转， 共 8 个 方向
    static int moveX[9];
    static int moveY[9];
    
    
    
    // 游戏下棋的历史记录
    std::stack < cocos2d::Vec2 > historyOperation;
    
    // 内部棋盘
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
    
    // 换算屏幕点 到 矩阵点
    cocos2d::Vec2 convertToMatrix(cocos2d::Vec2 pos, int tag);
    
    // 判断 位置是否在对象上
    bool rectContainsPoint(cocos2d::Vec2 pos, int tag);
    
    // 各种显示棋子的方式
    void showBWByMatrix(cocos2d::Vec2 pos, int tag);
    
    void showBWByGLCoord(cocos2d::Vec2 pos, int BW, int tag);
    
    void showBWAllByMatrix(int tag);
    
    // 从屏幕上移除棋子的方式
    void removeBWByMatrixCoord(cocos2d::Vec2 pos);
    
    void removeAllBWByMatrix();
    
    // 判断是否胜利， 若是胜利， 返回非零， 数字代表方向
    int win(cocos2d::Vec2 pos);
    
    // 获得 点 坐标
    cocos2d::Vec2 getPointByWinPos(cocos2d::Vec2 pos, int tag);
    
    // 显示 线 位置， 形参分别 为 矩阵点坐标， 直线 类型
    void showLineByPos(cocos2d::Vec2 pos, int tag);
    
    // 初始化 棋盘
    void initChessboard();
    
    
    CREATE_FUNC(ChessBoard);
};


#endif /* ChessBoard_hpp */
