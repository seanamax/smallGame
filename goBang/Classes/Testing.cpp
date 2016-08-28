//
//  Testing.cpp
//  Gobang
//
//  Created by Chris on 16/8/27.
//
//

#include "Testing.hpp"

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
    
    
//    log("cancelItem width = %f, height = %f", cancelItem->getContentSize().width,
//        cancelItem->getContentSize().height);
//    
//    log("cancelItem x = %f, y = %f", cancelItem->getPosition().x,
//        cancelItem->getPosition().y);
//    
//    Vec2 p = convertToWorldSpace(cancelItem->getPosition());
//    log("test %f %f", p.x, p.y);

//    Rect rec = bg->getBoundingBox();
//    
//    log("%f %f %f %f", rec.getMinX(), rec.getMinY(), rec.getMaxX(), rec.getMaxY());
//    
    
    Menu * mn = Menu::create(cancelItem, NULL);
    
    mn->setPosition(Vec2::ZERO);
    
    this->addChild(mn);
    
    setTouchEnabled(true);
    
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    
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
    
    Rect rect = this->getChildByTag(k_Bg)->boundingBox();
    
    float interval = (rect.getMaxY() - rect.getMinY()) / 20.0f;
    
    
    if(this->rectContainsPoint(location, k_Bg)) {
        
        location.x = (location.x - rect.getMinX()) / interval - 1.0f;
        location.y = (location.y - rect.getMinY()) / interval - 1.0f;
        
        // 端点
        int x, y;
        
        // 对 x, y 修正
        if(location.x - (int)location.x > 0.5) {
            x = location.x + 1;
        }
        else {
            x = location.x;
        }
        
        if(location.y - (int)location.y > 0.5) {
            y = location.y + 1;
        }
        else {
            y = location.y;
        }
        
        
        if(x < 19 && y < 19) {
            
            auto pos = Vec2((x + 1) * interval + rect.getMinX(),
                            (y + 1) * interval + rect.getMinY());
            
            pos = Director::getInstance()->convertToGL(pos);
            
            //this->showBWByGLCoord(pos, k_White);
            
            y = 18 - y;
            if(this->chessboard[x][y] == k_Null) {
                
                this->chessboard[x][y] = k_Black;
                this->showBWByMatrix(Vec2(x, y), k_Bg);
                
                log("test1");
                
            }
            
            else if(this->chessboard[x][y] == k_Black) {
                
                this->removeChildByTag(1000);
                
                
                this->chessboard[x][y] = k_White;
                
                this->removeBWByMatrixCoord(Vec2(x, y));
                this->showBWByMatrix(Vec2(x, y), k_Bg);
                
                log("test2");
            }
            
            else {
                
                this->chessboard[x][y] = k_Null;
                //this->removeBWByMatrixCoord(Vec2(x, y));
                
                //log("test");
                
                auto redLine = Sprite::create("2ODRedLine.png");
                
                redLine->setTag(1000);
                
                redLine->setPosition(this->convertToGL(Vec2(x, y), k_Bg));
                redLine->setAnchorPoint(Vec2(1.0f, 1.0f));
                
                this->addChild(redLine);
                
                log("test3");
                
                
            }
            
            log("test win() %d", win(Vec2(x, y)));
            
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
    
    if(this->calcBWNumByDirect(pos, 1) + this->calcBWNumByDirect(pos, 5) +
       1 >= LIMIT_NUM_BW) {
        
        direct = 1;
    }
    
    else if(this->calcBWNumByDirect(pos, 2) + this->calcBWNumByDirect(pos, 6) +
            1 >= LIMIT_NUM_BW) {
        
        direct = 2;
    }
    
    else if(this->calcBWNumByDirect(pos, 3) + this->calcBWNumByDirect(pos, 7) +
            1 >= LIMIT_NUM_BW) {
        
        direct = 3;
    }
    
    else if(this->calcBWNumByDirect(pos, 4) + this->calcBWNumByDirect(pos, 8) +
            1 >= LIMIT_NUM_BW) {
        
        direct = 4;
    }
    
    return direct;
}


Vec2 ChessBoard::convertToGL(cocos2d::Vec2 pos, int tag)
{
    auto item = this->getChildByTag(tag);
    
    Vec2 pos2 = Vec2::ZERO;
    
    if(item) {
        
        Rect rect = item->boundingBox();
        
        float interval = (rect.getMaxX() - rect.getMinX()) / 20.0f;
        
        // 换算成 GL坐标的值
        pos2 = Vec2(pos.x * interval + rect.getMinX() + interval,
                         pos.y * interval + rect.getMinY() + interval);
        
    }
    
    return pos2;
}








