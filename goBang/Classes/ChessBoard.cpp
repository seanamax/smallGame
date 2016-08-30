//
//  ChessBoard.cpp
//  Gobang
//
//  Created by Chris on 16/8/29.
//
//

#include "ChessBoard.hpp"
#include "SimpleAudioEngine.h"
#include "MainMenu.hpp"
#include "Setting.hpp"
#include <stack>


USING_NS_CC;
using namespace CocosDenshion;

bool ChessBoard::hitChessBoard = true;

Scene * ChessBoard::createScene()
{
    auto scene = Scene::create();
    
    auto layer = ChessBoard::create();
    
    scene->addChild(layer);
    
    return scene;
}


bool ChessBoard::init()
{
    
    if(!Layer::init()) {
        
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite * bg = Sprite::create("chessboard.png");
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
                         origin.y + visibleSize.height / 2));
    
    bg->setTag(k_Bg);
    this->addChild(bg);
    
    
    MenuItemFont * cancelItem = MenuItemFont::create("返回",
                                                     CC_CALLBACK_1(ChessBoard::menuCancelCallback, this));
    
    cancelItem->setPosition(Vec2(origin.x + visibleSize.width - 50.0f,
                                 origin.y + 50.0f));
    cancelItem->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    Menu * mn = Menu::create(cancelItem, NULL);
    
    mn->setPosition(Vec2::ZERO);
    
    this->addChild(mn);
    

    
    setTouchEnabled(true);
    
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
        
    
    this->initChessboard();
    
    return true;
}



void ChessBoard::menuCancelCallback(Ref * pSender)
{
    MenuItem * item = (MenuItem *)pSender;
    log("chessBoard::menuCancelCallback %p", item);
    
    if(Setting::effectSound) {
        SimpleAudioEngine::getInstance()->playEffect("sounds/Blip.wav");
    }
    
    Director::getInstance()->popScene();
}

// 层 转换动画过渡结束时，进行音乐操作
void ChessBoard::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    log("ChessBoard::onEnterTransitionDidFinish()");
    
    
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    if(Setting::backgroundMusic) {
        SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/Recollection.mp3", true);
    }
}

bool ChessBoard::onTouchBegan(Touch * touch, Event * event)
{
    log("ChessBoard::onTouchBegan");
    
    auto location = touch->getLocationInView();
    
    location = Director::getInstance()->convertToGL(location);
    
    if(this->rectContainsPoint(location, k_Bg)) {
        
        
        auto pos = this->convertToMatrix(location, k_Bg);
        
        if(JUDGE_EDGE(pos)) {
            
            //pos.y = 18 - pos.y;
            if(this->chessboard[(int)pos.x][(int)pos.y] == k_Null) {
                
                this->chessboard[(int)pos.x][(int)pos.y] = k_Black;
                this->showBWByMatrix(Vec2(pos.x, pos.y), k_Bg);
                
                log("test1");
                
            }
            
            else {
                this->chessboard[(int)pos.x][(int)pos.y] = k_Null;
                this->removeBWByMatrixCoord(pos);
            }
            
            //log("test win() %d", win(Vec2((int)pos.x, (int)pos.y)));
            log("%f %f", pos.x, pos.y);
            
            
            int tag = this->win(pos);
            
            if(tag) {
                
                //pos = this->getPointByWinPos(pos, tag);
                
                this->showLineByPos(pos, tag);
                
                this->setTouchEnabled(false);
                
            }
            
            
        }
        
    }
    
    return false;
}


void ChessBoard::onTouchMoved(Touch * touch, Event * event)
{
    log("ChessBoard::onTouchMoved()");
}

void ChessBoard::onTouchEnded(Touch * touch, Event * event)
{
    log("ChessBoard::onTouchEnded()");
}

// 判断点是否在对象上
bool ChessBoard::rectContainsPoint(Vec2 pos, int tag)
{
    auto item = this->getChildByTag(tag);
    
    Rect rect = item->boundingBox();
    
    if(rect.getMinX() <= pos.x && pos.x <= rect.getMaxX() &&
       rect.getMinY() <= pos.y && pos.y <= rect.getMaxY()) {
        
        return true;
        
    }
    
    return false;
}

// 通过 矩阵下表获得 并 设定 棋子
void ChessBoard::showBWByMatrix(Vec2 pos, int tag)
{
    
    Vec2 pos2 = convertToGL(pos, tag);
    
    this->showBWByGLCoord(pos2, this->chessboard[(int)pos.x][(int)pos.y], CALC_BW_TAG(pos.x, pos.y));
    
}

// 通过 GL 坐标 设定 棋子
void ChessBoard::showBWByGLCoord(cocos2d::Vec2 pos, int BW, int tag)
{
    if(BW == k_Black) {
        
        auto black = Sprite::create("black.png");
        
        black->setPosition(pos);
        
        black->setTag(tag);
        
        this->addChild(black);
    }
    
    else if(BW == k_White) {
        
        auto white = Sprite::create("white.png");
        
        white->setPosition(pos);
        
        white->setTag(tag);
        
        this->addChild(white);
    }
    
    
}

// 通过矩阵 获得并显示 棋子
void ChessBoard::showBWAllByMatrix(int tag)
{
    for(size_t i=0; i < this->LIMIT_CHESSBOARD; ++ i) {
        for( size_t j=0; j < this->LIMIT_CHESSBOARD; ++ j) {
            showBWByMatrix(Vec2(i, j), tag);
        }
    }
    
}

// 棋子 通过 矩阵下表 移除
void ChessBoard::removeBWByMatrixCoord(Vec2 pos)
{
    int tag = CALC_BW_TAG(pos.x, pos.y);
    
    auto item = this->getChildByTag(tag);
    
    if(item) {
        
        this->removeChild(item);
        
    }
}

// 清屏
void ChessBoard::removeAllBWByMatrix()
{
    for(size_t i=0; i < this->LIMIT_CHESSBOARD; ++ i) {
        for(size_t j=0; j < this->LIMIT_CHESSBOARD; ++ j) {
            
            if(this->chessboard[i][j] != k_Null) {
                this->removeBWByMatrixCoord(Vec2(i, j));
            }
        }
    }
}


size_t ChessBoard::calcBWNumByDirect(Vec2 centre, size_t direct)
{
    size_t count = 0;
    
    for(Vec2 pos = Vec2(centre.x + this->moveX[direct],
                        centre.y + this->moveY[direct]);
        JUDGE_EDGE(pos);
        pos += Vec2(this->moveX[direct], this->moveY[direct])) {
        
        if(this->chessboard[(int)pos.x][(int)pos.y] == this->chessboard[(int)centre.x][(int)centre.y]) {
            ++ count;
        }
        
        else {
            break;      // 若不是己方棋子， 跳出， 不再循环查找
        }
    }
    
    return count;
}


int ChessBoard::win(cocos2d::Vec2 pos)
{
    int direct = 0;
    
    if(this->chessboard[(int)pos.x][(int)pos.y] == k_Null) {
        return direct;
    }
    
    if(this->calcBWNumByDirect(pos, k_12OD) + this->calcBWNumByDirect(pos, k_6OD) +
       1 >= LIMIT_NUM_BW) {
        
        direct = k_12OD;
    }
    
    else if(this->calcBWNumByDirect(pos, k_1AndHalfOD) + this->calcBWNumByDirect(pos, k_7AndHalfOD) +
            1 >= LIMIT_NUM_BW) {
        
        direct = k_1AndHalfOD;
    }
    
    else if(this->calcBWNumByDirect(pos, k_3OD) + this->calcBWNumByDirect(pos, k_9OD) +
            1 >= LIMIT_NUM_BW) {
        
        direct = k_3OD;
    }
    
    else if(this->calcBWNumByDirect(pos, k_4AndHaleOD) + this->calcBWNumByDirect(pos, k_10AndHalfOD) +
            1 >= LIMIT_NUM_BW) {
        
        direct = k_4AndHaleOD;
    }
    
    return direct;
}


Vec2 ChessBoard::convertToGL(cocos2d::Vec2 pos, int tag)
{
    auto item = this->getChildByTag(tag);
    
    Vec2 pos2 = Vec2::ZERO;
    
    assert(item);
    
    if(item) {
        
        Rect rect = item->boundingBox();
        
        float interval = (rect.getMaxX() - rect.getMinX()) / (float)(this->LIMIT_CHESSBOARD + 1);
        
        // 换算成 GL坐标的值
        pos2 = Vec2(pos.x * interval + rect.getMinX() + interval,
                    pos.y * interval + rect.getMinY() + interval);
        
    }
    
    return pos2;
}


Vec2 ChessBoard::convertToMatrix(cocos2d::Vec2 pos, int tag)
{
    Vec2 pos2 = Vec2::ZERO;
    
    auto item = this->getChildByTag(tag);
    
    assert(item);
    
    if(item) {
        
        Rect rect = item->boundingBox();
        
        float interval = (rect.getMaxX() - rect.getMinX()) / (float)(this->LIMIT_CHESSBOARD + 1);
        
        pos2 = Vec2((pos.x - rect.getMinX()) / interval,
                    (pos.y - rect.getMinY()) / interval);
        
        
        // 修正 偏差
        if(pos2.x - (int)pos2.x >= 0.5f) {
            pos2.x = 1 + (int)pos2.x;
        }
        else {
            pos2.x = (int)pos2.x;
        }
        
        if(pos2.y - (int)pos2.y >= 0.5f) {
            pos2.y = 1 + (int)pos2.y;
        }
        else {
            pos2.y = (int)pos2.y;
        }
        
        pos2 -= Vec2(1.0f, 1.0f);
    }
    
    return pos2;
}


Vec2 ChessBoard::getPointByWinPos(cocos2d::Vec2 centre, int tag)
{
    
    for(Vec2 pos = centre; JUDGE_EDGE(pos); pos += Vec2(this->moveX[tag],
                                                        this->moveY[tag])) {
        
        if(this->chessboard[(int)pos.x][(int)pos.y] ==
           this->chessboard[(int)centre.x][(int)centre.y]) {
            
            centre = pos;
            
        }
        
        else {
            
            break;
            
        }
    }
    
    
    return centre;
    
}

void ChessBoard::showLineByPos(cocos2d::Vec2 pos, int tag)
{
    
    // 从 组成的线段的两个端点分别划线， 使得出现超过 5个点 的时候， 不会出现一些点没有被连到
    //log("ChessBoard::showLineByPos and before this->showOneDirectLineByPos");
    log("ChessBoard::showLineByPos pos.x=%f  pos.y=%f tag=%d", pos.x, pos.y, tag);
    // 从 默认 的端点 划线
    this->showOneDirectLineByPos(pos, tag);
    
    // 从另外一端点 划线
    // 转换 端点 的类型
    if(tag <= this->LIMIT_DIRECTION / 2) {
        tag += this->LIMIT_DIRECTION / 2;
    }
    else {
        tag -= this->LIMIT_DIRECTION / 2;
    }
    
    this->showOneDirectLineByPos(pos, tag);
}

void ChessBoard::initChessboard()
{
    
    memset(this->chessboard, k_Null, sizeof(chessboard));
    
}

void ChessBoard::showOneDirectLineByPos(cocos2d::Vec2 pos, int tag)
{
    // 获得线段端点
    pos = this->getPointByWinPos(pos, tag);
    
    // 转换成 GL坐标点
    pos = this->convertToGL(pos, k_Bg);
    
    log("ChessBoard::showOneDirectLineByPos pos.x=%f pos.y=%f", pos.x, pos.y);
    
    switch(tag) {
            
        case k_12OD:
        {
            
            log("test k_12OD 1");
            
            
            auto item = Sprite::create("12ODRedLine.png");
            item->setPosition(pos);
            item->setAnchorPoint(Vec2(0.5f, 1.0f));
            item->setTag(tag);
            
            this->addChild(item);
            
            log("test k_12OD 2");
            
            break;
            
        }
            
            
        case k_1AndHalfOD:
        {
            
            auto item = Sprite::create("1AndHalfODRedLine.png");
            item->setPosition(pos);
            item->setAnchorPoint(Vec2(1.0f, 1.0f));
            item->setTag(tag);
            
            this->addChild(item);
            
            break;
            
        }
            
        case  k_3OD:
        {
            
            auto item = Sprite::create("3ODRedLine.png");
            item->setPosition(pos);
            item->setAnchorPoint(Vec2(1.0f, 0.5f));
            item->setTag(tag);
            
            this->addChild(item);
            
            break;
            
        }
            
        case k_4AndHaleOD:
        {
            
            auto item = Sprite::create("10AndHalfODRedLine.png");
            item->setPosition(pos);
            item->setAnchorPoint(Vec2(1.0f, 0.0f));
            item->setTag(tag);
            
            this->addChild(item);
            
            break;
            
        }
            
            
        case k_6OD:
        {
            
            auto item = Sprite::create("12ODRedLine.png");
            item->setPosition(pos);
            item->setAnchorPoint(Vec2(0.5f, 0.0f));
            item->setTag(tag);
            
            this->addChild(item);
            
            break;
            
        }
            
            
        case k_7AndHalfOD:
        {
            
            auto item = Sprite::create("1AndHalfODRedLine.png");
            item->setPosition(pos);
            item->setAnchorPoint(Vec2(0.0f, 0.0f));
            item->setTag(tag);
            
            this->addChild(item);
            
            break;
            
        }
            
            
        case k_9OD:
        {
            
            auto item = Sprite::create("3ODRedLine.png");
            item->setPosition(pos);
            item->setAnchorPoint(Vec2(0.0f, 0.5f));
            item->setTag(tag);
            
            this->addChild(item);
            
            break;
            
        }
            
            
        case k_10AndHalfOD:
        {
            
            auto item = Sprite::create("10AndHalfODRedLine.png");
            item->setPosition(pos);
            item->setAnchorPoint(Vec2(0.0f, 1.0f));
            item->setTag(tag);
            this->addChild(item);
            
            break;
            
        }
            
            
        default:
        {
            
            break;
            
        }
    }
    
    
}


