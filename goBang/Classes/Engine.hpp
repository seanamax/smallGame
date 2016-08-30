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
#include "SelectedPlayingLevel.hpp"

typedef struct _Score Score;

#define MAX_DEEPTH 100
#define MAX_WIDTH 100
#define MAX_LEVEL 100
struct _Score
{
    cocos2d::Vec2 pos;
    int score;
};

class Naina
{
private:
    
    static int _flag;
    static int _currentFlag;
    int _stop;
    int _deepth;
    int _width;
    
    int _recordAllChessBoard[MAX_LEVEL][ChessBoard::LIMIT_CHESSBOARD-1][ChessBoard::LIMIT_CHESSBOARD-1];
    int _recordAllChessScore[MAX_LEVEL][ChessBoard::LIMIT_CHESSBOARD-1][ChessBoard::LIMIT_CHESSBOARD-1];
    
    Score _recordTmpChessScore[(ChessBoard::LIMIT_CHESSBOARD - 1) * (ChessBoard::LIMIT_CHESSBOARD - 1)];
    Score _recordPathScore[MAX_DEEPTH][MAX_WIDTH];
    
public:
    
    static bool cmpScore(Score & var1, Score & var2);
    
    void switchFlag();
    
    cocos2d::Vec2 findBestPos(cocos2d::Vec2 pos);
    
    void calcMWordInChessBoard(int che[][ChessBoard::LIMIT_CHESSBOARD], cocos2d::Vec2 pos);
    
    int calcScoreInEveryStep(int stepNum, int tag, cocos2d::Vec2 pos);
    
    Naina(int deepth, int width, int flag);
    
    void copyChess(int deepth, int tag);
    
    
    
    ~Naina();
};






#endif /* Engine_hpp */
