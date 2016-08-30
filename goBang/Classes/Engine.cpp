//
//  Engine.cpp
//  Gobang
//
//  Created by Chris on 16/8/30.
//
//

#include "Engine.hpp"
#include <Algorithm>

int Naina::_flag = k_Black;
int Naina::_currentFlag = k_Black;

void Naina::switchFlag()
{
    if(this->_currentFlag == k_White) {
        this->_currentFlag = k_Black;
    }
    
    else {
        this->_currentFlag = k_White;
    }
}



Naina::Naina(int deepth, int width, int flag)
{
    
    this->_flag = flag;
    this->_currentFlag = flag;
    this->_deepth = deepth;
    this->_width = width;
    

}



// 整理， 排序
void Naina::copyChess(int deepth, int tag)
{
    for(size_t i=0, k=0; i < ChessBoard::LIMIT_CHESSBOARD; ++ i) {
        for(size_t j=0; j < ChessBoard::LIMIT_CHESSBOARD; ++ j, ++ k) {
            this->_recordTmpChessScore[k].pos.x = i;
            this->_recordTmpChessScore[k].pos.y = j;
            this->_recordTmpChessScore[k].score = this->_recordAllChessScore[deepth][i][j];
        }
    }
    
    std::sort(_recordTmpChessScore, _recordTmpChessScore + (ChessBoard::LIMIT_CHESSBOARD - 1) *
         (ChessBoard::LIMIT_CHESSBOARD - 1), cmpScore);
    
    for(size_t i=0; i < this->_width; ++ i) {
        this->_recordPathScore[deepth][i] = this->_recordTmpChessScore[i];
    }
}

// 积分比较函数
bool Naina::cmpScore(Score & var1, Score & var2)
{
    if(_currentFlag == _flag) {
        return var1.score > var2.score;
    }
    
    else {
        return var1.score < var2.score;
    }
}

