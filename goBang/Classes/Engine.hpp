//
//  Engine.hpp
//  Gobang
//
//  Created by Chris on 16/8/30.
//
//

#ifndef Engine_hpp
#define Engine_hpp

#include "cocos2d.h"
#include "ChessBoard.hpp"


typedef struct _Score Score;

#define MAX_DEEPTH 100
#define MAX_WIDTH 100
#define MAX_LEVEL 100
#define NUM_BW 2

// 五元组 集合 评分表
enum
{
    k_Empty = 7,                // 空
    
    k_X = 35,                   // 只有一个白棋子
    k_XX = 800,
    k_XXX = 15000,
    k_XXXX = 800000,
    
    k_Y = 15,                   // 只有一个黑棋子
    k_YY = 400,
    k_YYY = 1800,
    k_YYYY = 100000,
    
    k_Virtual = 0,
    k_Polluted = 0              // 至少有一个白棋子和黑棋子
};


struct _Score
{
    cocos2d::Vec2 pos;
    int score;
    bool used;
};

class Naina
{
private:
    
    static int _stop;
    
    int _flag;
    int _currentFlag;
    int _deepth;
    int _width;
    
    int _recordAllChessBoard[MAX_LEVEL][ChessBoard::LIMIT_CHESSBOARD][ChessBoard::LIMIT_CHESSBOARD];
    int _recordAllChessScore[NUM_BW][MAX_LEVEL][ChessBoard::LIMIT_CHESSBOARD][ChessBoard::LIMIT_CHESSBOARD];
    
    
    Score _recordTmpChessScore[ChessBoard::LIMIT_CHESSBOARD * ChessBoard::LIMIT_CHESSBOARD];
    Score _recordPathScore[MAX_DEEPTH][MAX_WIDTH];
    
    
    // 计算 该点 得分 类型
    void calcScoreInPos(int deepth, cocos2d::Vec2 pos, int tag);
    
    // 遍历 米 字类型 得分
    void calcMWordInChessBoard(int deepth, cocos2d::Vec2 pos, int tag);
    
    // 机器人 递归 寻找 最佳得分点
    int calcScoreInEveryStep(int stepNum, int tag, cocos2d::Vec2 pos);
    
    // 拷贝 棋盘得分 以及 排序
    void copyChessScoreAndSort(int deepth, int tag);
    
    // 递归 过程， 数据之间的转移
    void copyChessScoreAndBoardToRecursive(int deepth);
    
    // 计算 5 元组数据
    int calcFiveTupleScore(int tag, int BWtag, int BWNum);
    
    
public:
    
    static bool cmpScore(Score & var1, Score & var2);
    
    int switchTag(int tag);
    
    // 设置 机器人 棋手 为 黑白棋
    // 设置 是否停止运行
    void setFlag(int tag);
    
    void setStop(bool stop);
    
    // 设置 深度广度
    void setWidth(int width);
    
    void setDeepth(int deepth);
    
    // 获得 深度广度
    int getDeepth();
    
    int getWidth();
    // 获得 机器人 棋手 类型， 为黑白棋
    // 获得 运行 情况
    int getFlag();
    
    int getStop();
    
    // 寻找 最佳 下棋位置
    cocos2d::Vec2 findBestNext(cocos2d::Vec2 pos);
    
    // 初始化 已有棋盘， 第一次启用机器人
    void initFirstFind(int cheboard[][ChessBoard::LIMIT_CHESSBOARD]);
    
    
    // 构造类型
    //Naina(int deepth, int width, int flag);

};



#endif /* Engine_hpp */
