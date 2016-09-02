//
//  PlayingWithComputer.cpp
//  Gobang
//
//  Created by Chris on 16/8/27.
//
//

#include "PlayingWithComputer.hpp"
#include "MainMenu.hpp"
#include "Setting.hpp"
#include "SelectedPlayingLevel.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

int PlayingWithComputer::_level = k_Difficult;

bool PlayingWithComputer::getStopFind()
{
    return this->_Naina.getStop();
}

int PlayingWithComputer::getLevel()
{
    return this->_level;
}

void PlayingWithComputer::setLevel(int playingLevel)
{
    _level = playingLevel;
        
}

void PlayingWithComputer::setStopFind(bool stopFind)
{
    this->_Naina.setStop(stopFind);
}

bool PlayingWithComputer::init()
{
    // 如果 初始化 失败， 直接返回 失败
    if(!Layer::init()) {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    auto chbg = Sprite::create("chessboard.png");
    chbg->setPosition(Vec2(origin.x + visibleSize.width / 2,
                           origin.y + visibleSize.height / 2));
    
    chbg->setTag(k_Bg);
    this->addChild(chbg);
    
    
    auto retractMoveItem = MenuItemFont::create("悔棋",
                                                CC_CALLBACK_1(PlayingWithComputer::menuRetractMoveCallback, this));
    retractMoveItem->setTag(k_RetractMove);
    
    
    auto refreshItem = MenuItemFont::create("新局",
                                            CC_CALLBACK_1(PlayingWithComputer::menuRefreshCallback,this));
    refreshItem->setTag(k_Refresh);
    
    
    auto settingItem = MenuItemFont::create("设定",
                                            CC_CALLBACK_1(PlayingWithComputer::menuSettingCallback, this));
    settingItem->setTag(k_Setting);
    
    
    auto tipsItem = MenuItemFont::create("提示",
                                         CC_CALLBACK_1(PlayingWithComputer::menuTipsCallback, this));
    tipsItem->setTag(k_Tips);
    
    
    auto cancelItem = MenuItemFont::create("返回",
                                           CC_CALLBACK_1(PlayingWithComputer::menuCancelCallback, this));
    cancelItem->setTag(k_Cancel);
    
    
    auto mn = Menu::create(tipsItem, retractMoveItem, refreshItem, settingItem, cancelItem, NULL);
    mn->setTag(k_MenuPlayingWithComputer);
    
    mn->alignItemsVertically();
    
    mn->setPosition(Vec2(origin.x + visibleSize.width - 100, origin.y + visibleSize.height - 300));
    //mn->setAnchorPoint(Vec2(1.0f, 1.0f));
    
    this->addChild(mn);
    
    
    this->initChessboard();
    this->_initNaina(k_White);
    
    //  设置 鼠标 点击 模式
    setTouchEnabled(true);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    
    return true;
}

Scene * PlayingWithComputer::createScene()
{
    
    auto scene = Scene::create();
    
    auto layer = PlayingWithComputer::create();
    
    assert(layer);
    
    scene->addChild(layer);
    
    return scene;
    
}


void PlayingWithComputer::menuRetractMoveCallback(Ref * pSender)
{
    
    auto item = (MenuItem *)pSender;
    log("PlayingWithComputer::menuRetractMoveCallback %p", item);
    
    if(Setting::effectSound) {
        SimpleAudioEngine::getInstance()->playEffect("sounds/Blip.wav");
    }
    
    
}

// 新局
void PlayingWithComputer::menuRefreshCallback(Ref * pSender)
{
    
    auto item = (MenuItem *)pSender;
    log("PlayingWithComputer::menuRefreshCallback %p", item);
    
    if(Setting::effectSound) {
        SimpleAudioEngine::getInstance()->playEffect("sounds/Blip.wav");
    }
    
    // 停止查找
    // 移除 画面上 所有的棋子
    // 初始化 棋盘矩阵数组
    PlayingWithComputer::setStopFind(true);
    this->removeAllBWByMatrix();
    this->initChessboard();
    
    // 设置 可 鼠标点击
    // 设置 单点模式
    setTouchEnabled(true);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    
}


void PlayingWithComputer::menuSettingCallback(Ref * pSender)
{
    
    auto item = (MenuItem *)pSender;
    log("PlayingWithComputer::menuSettingCallback %p", item);
    
    if(Setting::effectSound) {
        SimpleAudioEngine::getInstance()->playEffect("sounds/Blip.wav");
    }
    
    auto scene = Setting::createScene();
    auto sc = TransitionFadeUp::create(1.0f, scene);
    Director::getInstance()->pushScene(sc);
    
}


void PlayingWithComputer::menuTipsCallback(Ref * pSender)
{
    
    auto item = (MenuItem *)pSender;
    log("PlayingWithComputer::menuTipsCallback %p", item);
    
    if(Setting::effectSound) {
        SimpleAudioEngine::getInstance()->playEffect("sounds/Blip.wav");
    }
    
    
}


void PlayingWithComputer::menuCancelCallback(Ref * pSender)
{
    
    auto item = (MenuItem *)pSender;
    log("PlayingWithComputer::menuTipsCallback %p", item);
    
    if(Setting::effectSound) {
        SimpleAudioEngine::getInstance()->playEffect("souns/Blip.wav");
    }
    
    auto scene = MainMenu::createScene();
    auto sc = TransitionFade::create(1.0f, scene);
    
    Director::getInstance()->replaceScene(sc);
}

void PlayingWithComputer::onEnterTransitionDidFinish()
{
    
    log("PlayingWithComputer::onEnterDidFinish");
    
    Layer::onEnterTransitionDidFinish();
    
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    if(Setting::backgroundMusic) {
        SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/Recollection.mp3");
    }
    
}

void PlayingWithComputer::_initNaina(int flag)
{
    
    _Naina.setFlag(flag);
    _Naina.initFirstFind(this->chessboard);
    
    if(_level == k_Simple) {
        
        _Naina.setDeepth(SIMPE_DEEPTH);
        _Naina.setWidth(SIMPE_WIDTH);

    }
    
    else if(_level == k_Ordinary) {
        
        _Naina.setDeepth(ORDINAY_DEEPTH);
        _Naina.setWidth(ORDINAY_WIDTH);
        
    }
    
    else if(_level == k_Difficult) {
        
        _Naina.setDeepth(DIFFICULT_DEEPTH);
        _Naina.setWidth(DIFFICULT_WIDTH);
        
    }
}


bool PlayingWithComputer::onTouchBegan(Touch * touch, Event * event)
{
    log("PlayingWithComputer::onTouchBegan");
    
    auto location = touch->getLocationInView();
    
    location = Director::getInstance()->convertToGL(location);
    
    if(this->rectContainsPoint(location, k_Bg)) {
        
        auto pos = this->convertToMatrix(location, k_Bg);
        
        if(JUDGE_EDGE(pos) && this->chessboard[(int)pos.x][(int)pos.y] == k_Null) {
            
            this->chessboard[(int)pos.x][(int)pos.y] = k_Black;
            this->showBWByMatrix(pos, k_Bg);
            
            log("Show black in chessBoard");
            
            int tag = this->win(pos);
            
            if(tag) {
                
                this->showLineByPos(pos, tag);
                
                this->setTouchEnabled(false);
                
                log("Show black win");
                
                return false;
            }
            
            pos = this->_Naina.findBestNext(pos);
            

            this->chessboard[(int)pos.x][(int)pos.y] = k_White;
            this->showBWByMatrix(pos, k_Bg);
            log("Show white in chessboard");
            
            tag = this->win(pos);
            
            if(tag && !this->_Naina.getStop()) {
                
                this->showLineByPos(pos, tag);
                
                this->setTouchEnabled(false);
                
                log("Show white win");
            }
        }
    }
    
    return false;
}