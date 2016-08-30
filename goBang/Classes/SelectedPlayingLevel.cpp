//
//  SelectedPlayingLevel.cpp
//  Gobang
//
//  Created by Chris on 16/8/27.
//
//

#include "SelectedPlayingLevel.hpp"
#include "PlayingWithComputer.hpp"
#include "MainMenu.hpp"
#include "SimpleAudioEngine.h"
#include "Setting.hpp"
#include "Testing.hpp"

USING_NS_CC;
using namespace CocosDenshion;


Scene * SelectedPlayingLevel::createScene()
{
    auto scene = Scene::create();
    
    auto layer = SelectedPlayingLevel::create();
    
    scene->addChild(layer);
    
    return scene;
}


bool SelectedPlayingLevel::init()
{
    if(!Layer::init()) {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    
    MenuItemFont * simpleItem = MenuItemFont::create("简单", CC_CALLBACK_1(SelectedPlayingLevel::menuSimpleCallback, this));
    
    MenuItemFont * ordinaryItem = MenuItemFont::create("一般", CC_CALLBACK_1(
                                                    SelectedPlayingLevel::menuOrdinayCallback, this));
    
    MenuItemFont * difficultItem = MenuItemFont::create("困难", CC_CALLBACK_1(
                                                    SelectedPlayingLevel::menuDifficultCallback, this));
    
    MenuItemFont * cancelItem = MenuItemFont::create("返回", CC_CALLBACK_1(
                                                    SelectedPlayingLevel::menuCancelCallback, this));
    
    
    
    Menu * mn = Menu::create(simpleItem, ordinaryItem, difficultItem, cancelItem, NULL);
    
    mn->setPosition(Vec2(origin.x + visibleSize.width / 2,
                         origin.y + visibleSize.height / 2));
    
    mn->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    mn->alignItemsVertically();
    
    this->addChild(mn);
    
    return true;
}


void SelectedPlayingLevel::menuSimpleCallback(Ref * pSender)
{
    MenuItem * item = (MenuItem *)pSender;
    log("SelectedPlayingLevel::mennuSimpleCallback %p", item);
    
    if(Setting::effectSound) {
        SimpleAudioEngine::getInstance()->playEffect("sounds/Blip.wav");
    }
    
    // 设置 难度， 切换 特定场景
    PlayingWithComputer::setLevel(k_Simple);
    auto scene = PlayingWithComputer::createScene();
    auto sc = TransitionFade::create(1.0f, scene);
    
    Director::getInstance()->replaceScene(sc);
    
}


void SelectedPlayingLevel::menuOrdinayCallback(Ref * pSender)
{
    MenuItem * item = (MenuItem *)pSender;
    log("SeletedPlayingLevel::menuOrdinayCallback %p", item);
    
    if(Setting::effectSound) {
        SimpleAudioEngine::getInstance()->playEffect("sounds/Blip.wav");
    }
    
    // 设置 难度， 切换 特定场景
    PlayingWithComputer::setLevel(k_Ordinary);
    auto scene = PlayingWithComputer::createScene();
    auto sc = TransitionFade::create(1.0f, scene);
    
    Director::getInstance()->replaceScene(sc);
}


void SelectedPlayingLevel::menuDifficultCallback(Ref * pSender)
{
    MenuItem * item = (MenuItem *)pSender;
    log("SelectedPlayingLevel::menuDifficultCallback %p", item);
    
    if(Setting::effectSound) {
        SimpleAudioEngine::getInstance()->playEffect("sounds/Blip.wav");
    }
    
    // 设置 难度， 切换 特定场景
    PlayingWithComputer::setLevel(k_Difficult);
    auto scene = PlayingWithComputer::createScene();
    auto sc = TransitionFade::create(1.0f, scene);
    
    Director::getInstance()->replaceScene(sc);
    
}


void SelectedPlayingLevel::menuCancelCallback(Ref * pSender)
{
    MenuItem * item = (MenuItem *)pSender;
    log("SelectedPlayingLevel::menuCalcelCallback %p", item);
    
    if(Setting::effectSound) {
        SimpleAudioEngine::getInstance()->playEffect("sounds/Blip.wav");
    }
    
    Scene * secene = MainMenu::createScene();
    
    Scene * sc = TransitionFade::create(1.0f, secene);
    
    Director::getInstance()->replaceScene(sc);
}


void SelectedPlayingLevel::onEnterTransitionDidFinish()
{
    log("SelectedPlayingLevel::onEnterTransitionDidFinish()");
    Layer::onEnterTransitionDidFinish();
    
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    if(Setting::backgroundMusic) {
        SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/Synth.mp3", true);
    }
    
}