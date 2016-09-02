//
//  Engine.cpp
//  Gobang
//
//  Created by Chris on 16/8/30.
//
//

#include "Engine.hpp"
#include <Algorithm>

USING_NS_CC;

int  Naina::_stop = false;

void Naina::setFlag(int tag)
{
    this->_flag = tag;
}

int Naina::getFlag()
{
    return this->_flag;
}

int Naina::getStop()
{
    return this->_stop;
}

//Naina::Naina(int deepth, int width, int flag)
//{
//    
//    this->_flag = flag;
//    this->_currentFlag = flag;
//    this->_deepth = deepth;
//    this->_width = width;
//    
//
//}


void Naina::setWidth(int width)
{
    if(width > MAX_WIDTH) {
        width = MAX_WIDTH - 1;
    }
    
//    else if(width < 2) {
//        width = 2;
//    }
    
    this->_width = width;
}

void Naina::setDeepth(int deepth)
{
    if(deepth > MAX_DEEPTH) {
        deepth = MAX_DEEPTH;
    }
    
//    else if(deepth < 2) {
//        deepth = 2;
//    }
    
    this->_deepth = deepth;
}


int Naina::getWidth()
{
    return this->_width;
}

int Naina::getDeepth()
{
    return this->_deepth;
}

// 整理， 排序
void Naina::copyChessScoreAndSort(int deepth, int tag)
{
    
    for(size_t i=0, k=0; i < ChessBoard::LIMIT_CHESSBOARD; ++ i) {
        for(size_t j=0; j < ChessBoard::LIMIT_CHESSBOARD; ++ j, ++ k) {
            
            this->_recordTmpChessScore[k].pos.x = i;
            this->_recordTmpChessScore[k].pos.y = j;
            
            this->_recordTmpChessScore[k].score = this->_recordAllChessScore[(tag == this->_flag)][deepth][i][j];
            
            this->_recordTmpChessScore[k].used = (this->_recordAllChessBoard[deepth][i][j] != k_Null);
            
        }
    }
    
//    if(this->_stop) {
//        return ;
//    }
    
    //this->setFlag(tag);
    std::sort(_recordTmpChessScore, _recordTmpChessScore + (ChessBoard::LIMIT_CHESSBOARD - 1) *
         (ChessBoard::LIMIT_CHESSBOARD - 1), cmpScore);
    
    for(size_t i=0; i < this->_width; ++ i) {
        this->_recordPathScore[deepth][i] = this->_recordTmpChessScore[i];
    }
}

// 积分比较函数
bool Naina::cmpScore(Score & var1, Score & var2)
{
    
    if(var1.used) {
        return 0;
    }
    
    if(var2.used) {
        return 1;
    }
    

    return var1.score > var2.score;

}

Vec2 Naina::findBestNext(Vec2 pos)
{
    // 设定 棋手 下棋
    // 计算 黑白棋 得分
    this->_recordAllChessBoard[this->_deepth][(int)pos.x][(int)pos.y] = this->switchTag(this->_flag);
    this->calcMWordInChessBoard(this->_deepth, pos, this->_flag);
    this->calcMWordInChessBoard(this->_deepth, pos, this->switchTag(this->_flag));
    
    // 拷贝得分
    this->copyChessScoreAndSort(this->_deepth, this->_flag);
    
    
    for(size_t i=0; i < this->_width; ++ i) {
        
        Vec2 tmpPos = this->_recordPathScore[this->_deepth][i].pos;
        
        this->_recordAllChessBoard[this->_deepth][(int)tmpPos.x][(int)tmpPos.y] = this->_flag;
        
        this->_recordPathScore[this->_deepth][i].score -=
                                        this->calcScoreInEveryStep(this->_deepth-1,
                                        this->switchTag(this->_flag), tmpPos);
        
        this->_recordAllChessBoard[this->_deepth][(int)tmpPos.x][(int)tmpPos.y] = k_Null;
        
    }
    
    // 所得 结果进行 排序
    //setFlag(this->_flag);
    std::sort(this->_recordPathScore[this->_deepth], this->_recordPathScore[this->_deepth] +
         this->_width, cmpScore);
    
    Vec2 tmpPos = this->_recordPathScore[this->_deepth][0].pos;
    
    this->_recordAllChessBoard[this->_deepth][(int)tmpPos.x][(int)tmpPos.y] = this->_flag;
    this->calcMWordInChessBoard(this->_deepth, tmpPos, this->_flag);
    this->calcMWordInChessBoard(this->_deepth, tmpPos, this->switchTag(this->_flag));
    
//    log("In findBestnext() pos.x = %d, pos.y = %d", (int)tmpPos.x, (int)tmpPos.y);
//    log("In findBestnext() score %d", this->_recordPathScore[this->_deepth][0].score);
//    log("In findBEstnext() this->_flag = %d", this->_flag);
//    log("In findBestnext() this->chessscore[this->_flag][9][9] = %d", this->_recordAllChessScore[1][this->_deepth][9][9]);
//    log("In findBestnext() this->chessscore[this->_flag][9][8] = %d", this->_recordAllChessScore[1][this->_deepth][9][8]);
//    log("In findBestnext() this->chessscore[this->_flag][9][7] = %d", this->_recordAllChessScore[1][this->_deepth][9][7]);
//    log("In findBestnext() this->chessscore[this->_flag][9][6] = %d", this->_recordAllChessScore[1][this->_deepth][9][6]);
//    log("In findBestnext() this->chessscore[this->_flag][9][5] = %d", this->_recordAllChessScore[1][this->_deepth][9][5]);
    log("In findBestnext() this->_deepth = %d, this->_width = %d", this->_deepth, this->_width);
    
    return tmpPos;
}

int Naina::switchTag(int tag)
{
    if(tag == k_White) {
        tag = k_Black;
    }
 
    else if(tag == k_Black) {
        tag = k_White;
    }
    
    return tag;
}



int Naina::calcScoreInEveryStep(int stepNum, int tag, Vec2 pos)
{
    
    static int ___time = 0;
    ++ ___time;
    log("Naina::calcScoreInEveryStep() %d", ___time);
    
    if(stepNum == 0 || _stop) {
        return 0;
    }
    
    // 拷贝上一个棋盘的格局 和 得分
    this->copyChessScoreAndBoardToRecursive(stepNum);
    
    // 对 所在 棋子进行 得分 计算
    this->calcMWordInChessBoard(stepNum, pos, tag);
    this->calcMWordInChessBoard(stepNum, pos, this->switchTag(tag));
    
    // 拷贝 全局 得分， 进行排序
    this->copyChessScoreAndSort(stepNum, tag);
    
    // 模拟下棋， 设置 flag 辨明 棋手
    // 递归 模拟 下棋
    // 获得 得分
    
    if(this->_flag == this->switchTag(tag)) {
        
        this->_recordPathScore[stepNum][0].score -= this->calcScoreInEveryStep(stepNum-1,
                                                                               this->switchTag(tag),
                                                                               this->_recordPathScore[stepNum][0].pos);
    }
    
    else {
        
        for(size_t i=0; i < this->_width; ++ i) {
            
            Vec2 pos = this->_recordPathScore[stepNum][i].pos;
            
            this->_recordAllChessBoard[stepNum][(int)pos.x][(int)pos.y] = tag;
            
            this->_recordPathScore[stepNum][i].score -=
            this->calcScoreInEveryStep(stepNum-1, this->switchTag(tag), pos);
            
            this->_recordAllChessBoard[stepNum][(int)pos.x][(int)pos.y] = k_Null;
            
        }
        
        // 设定 棋手 身份
        // 进行 排序
        // setFlag(this->_flag);
        std::sort(this->_recordPathScore[stepNum], this->_recordPathScore[stepNum]
                  + this->_width, cmpScore);
        
    }

    // 返回 最佳 得分
    return this->_recordPathScore[stepNum][0].score;
}

void Naina::setStop(bool stop)
{
    this->_stop = stop;
}



// 拷贝上一个递归下来的 上一个棋盘格局 和 得分
void Naina::copyChessScoreAndBoardToRecursive(int deepth)
{
    
    for(size_t i=0; i < ChessBoard::LIMIT_CHESSBOARD; ++ i) {
        for(size_t j=0; j < ChessBoard::LIMIT_CHESSBOARD; ++ j) {
            
            this->_recordAllChessScore[0][deepth][i][j] =
            this->_recordAllChessScore[0][deepth+1][i][j];
            
            this->_recordAllChessScore[1][deepth][i][j] =
            this->_recordAllChessScore[1][deepth][i][j];
            
            this->_recordAllChessBoard[deepth][i][j] =
            this->_recordAllChessBoard[deepth+1][i][j];
            
        }
    }
}



void Naina::calcScoreInPos(int deepth, Vec2 pos, int tag)
{
    // 总共 8 个 方向
    // 依次 顺时针 旋转
    
    Vec2 tmpPos;
    int BWNum;
    int BWTag;
    int score = 0;
    bool edge;
    
    for(size_t i=1; i <= ChessBoard::LIMIT_DIRECTION; ++ i) {
        
        BWNum = 0;
        BWTag = k_Empty;
    
        for(size_t j=1; j < ChessBoard::LIMIT_NUM_BW; ++ j) {
            
            tmpPos = j * ConvertToVec2(i) + pos;
            edge = JUDGE_EDGE(pos);
            
            if(edge) {
                // 判定 不是 第一次标记
                if(BWTag != k_Empty) {
                    
                    
                    if(BWTag != this->_recordAllChessBoard[deepth][(int)tmpPos.x][(int)tmpPos.y]) {
                        
                        if(this->_recordAllChessBoard[deepth][(int)tmpPos.x][(int)tmpPos.y] != k_Null) {
                            
                            BWTag = k_Except;
                            
                        }
                        
                        score += this->calcFiveTupleScore(tag, BWTag, BWNum);
                        break;
                    }
                    
                    else {
                        
                        ++ BWNum;
                    }
                }
                
                // 第一次标记
                else {
                    BWTag = this->_recordAllChessBoard[deepth][(int)tmpPos.x][(int)tmpPos.y];
                    ++ BWNum;
                }
                
            }
            
            // outside edge
            else {
                score += this->calcFiveTupleScore(tag, BWTag, BWNum);
                break;
                
            }
            
            if(edge && j + 1 == ChessBoard::LIMIT_NUM_BW) {
                score += this->calcFiveTupleScore(tag, BWTag, BWNum);
            }
            
        }
        

    }
    
    this->_recordAllChessScore[tag == this->_flag][deepth][(int)pos.x][(int)pos.y] = score;
    
}


void Naina::calcMWordInChessBoard(int deepth, Vec2 pos, int tag)
{
    Vec2 tmpPos;

    for(size_t i=1; i <= ChessBoard::LIMIT_DIRECTION; ++ i) {
        for(size_t j=1; j < ChessBoard::LIMIT_NUM_BW; ++ j) {
            
            tmpPos = pos + j * ConvertToVec2(i);
            
            if(JUDGE_EDGE(tmpPos) &&
               this->_recordAllChessBoard[deepth][(int)tmpPos.x][(int)tmpPos.y]
               == k_Null) {
                
                //this->_recordAllChessScore[tag==this->_flag][deepth][(int)tmpPos.x][(int)tmpPos.y] =
                this->calcScoreInPos(deepth, tmpPos, tag);
                
            }
        }
    }
}


int Naina::calcFiveTupleScore(int tag, int BWTag, int BWNum)
{
    
    int score;
    
    // 为 己方, 为 正风
    if(tag == this->_flag) {
        
        score = 7;
        
        if(BWTag == this->_flag) {
            
            if(BWNum == 1) {
                score = k_X;
            }
            
            else if(BWNum == 2) {
                score = k_XX;
            }
            
            else if(BWNum == 3) {
                score = k_XXX;
            }
            
            else if(BWNum == 4) {
                score = k_XXXX;
            }
            
        }
        
        else if(BWTag == this->switchTag(this->_flag)){
            
            if(BWNum == 1) {
                score = k_Y;
            }
            
            else if(BWNum == 2) {
                score = k_YY;
            }
            
            else if(BWNum == 3) {
                score = k_YYY;
            }
            
            else if(BWNum == 4) {
                score = k_YYYY;
            }
            
        }
        
        else if(BWTag == k_Except) {
            score = 0;
        }
    }
    
    // 为 敌方
    else {
        
        score = 7;
        if(BWTag == this->switchTag(this->_flag)) {
            
            if(BWNum == 1) {
                score =  k_X;
            }
            
            else if(BWNum == 2) {
                score =  k_XX;
            }
            
            else if(BWNum == 3) {
                score =  k_XXX;
            }
            
            else if(BWNum == 4) {
                score =  k_XXXX;
            }
            
        }
        
        else if(BWTag == this->_flag) {
            
            if(BWNum == 1) {
                
                score =  k_Y;
                
            }
            
            else if(BWNum == 2) {
                
                score =  k_YY;
                
            }
            
            else if(BWNum == 3) {
                
                score =  k_YYY;
                
            }
            
            else if(BWNum == 4) {
                
                score =  k_YYYY;
                
            }
            
        }
        
        else if(BWTag == k_Except) {
            
            score = 0;
            
        }
        
    }
    
    return score;
}


void Naina::initFirstFind(int cheboard[][ChessBoard::LIMIT_CHESSBOARD])
{
    
    // 复制 棋盘
    for(size_t i=0; i < ChessBoard::LIMIT_CHESSBOARD; ++ i) {
        for(size_t j=0; j < ChessBoard::LIMIT_CHESSBOARD; ++ j) {
            
            this->_recordAllChessBoard[this->_deepth][i][j] = cheboard[i][j];
            
        }
    }
    
    // 得分初始化为 0
    // 进行全盘 计算 米字 得分
    for(size_t i=0; i < ChessBoard::LIMIT_CHESSBOARD; ++ i) {
        for(size_t j=0; j < ChessBoard::LIMIT_CHESSBOARD; ++ j) {
            
            this->_recordAllChessScore[0][this->_deepth][i][j] = 0;
            this->_recordAllChessScore[1][this->_deepth][i][j] = 0;
            this->calcScoreInPos(this->_deepth, Vec2(i, j), this->_flag);
            
        }
    }
    
}


