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

int PlayingWithComputer::_playingLevel = k_Simple;
bool PlayingWithComputer::_stopFind = false;

bool PlayingWithComputer::getStopFind()
{
    return _stopFind;
}

int PlayingWithComputer::getLevel()
{
    return _playingLevel;
}

void PlayingWithComputer::setLevel(int playingLevel)
{
    
    _playingLevel = playingLevel;
    
}

void PlayingWithComputer::setStopFind(bool stopFind)
{
    _stopFind = stopFind;
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


