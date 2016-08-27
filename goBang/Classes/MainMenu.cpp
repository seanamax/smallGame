//
//  MainMenu.cpp
//  Gobang
//
//  Created by Chris on 16/8/25.
//
//

#include "MainMenu.hpp"

USING_NS_CC;
using namespace CocosDenshion;

Scene * MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


// on 'init' you need to initialize your instance
bool MainMenu::init()
{
    
    ////////////////////
    // 1.super init first
    if(!Layer::init()) {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    MenuItemFont * playWithComputerItem = MenuItemFont::create("人机博弈",
                                                               CC_CALLBACK_1(MainMenu::menuPlayWithComputerCallback, this));
    
    MenuItemFont * testItem = MenuItemFont::create("测试",
                                                   CC_CALLBACK_1(MainMenu::menuTestCallback, this));
    
    MenuItemFont * settingItem = MenuItemFont::create("设定",
                                                      CC_CALLBACK_1(MainMenu::menuSettingCallback, this));
    
    MenuItemFont * closeItem = MenuItemFont::create("退出",
                                                    CC_CALLBACK_1(MainMenu::menuCloseCallback, this));
    
    
    Menu * mn = Menu::create(playWithComputerItem, testItem, settingItem, closeItem, NULL);
    mn->setPosition(Vec2(origin.x + visibleSize.width / 2,
                         origin.y + visibleSize.height / 2));
    
    mn->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    mn->alignItemsVertically();
    
    this->addChild(mn);
    
//    
//    auto bg = Sprite::create("chessboard.png");
//    
//    bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
//                         origin.y + visibleSize.height / 2));
//    
//    bg->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
//    
//    this->addChild(bg);
//    
//    
//    auto black = Sprite::create("black.png");
//    black->setPosition(origin.x + 54, origin.y + 54);
//    
//    this->addChild(black);
//    
//    auto white = Sprite::create("white.png");
//    white->setPosition(origin.x + 54, origin.y + 81);
//    
//    this->addChild(white);
//    
//    auto white2 = Sprite::create("white.png");
//    white2->setPosition(origin.x + 81, origin.y + 81);
//    
//    this->addChild(white2);
//    
//    auto white3 = Sprite::create("white.png");
//    white3->setPosition(origin.x + 81, origin.y + 54);
//    
//    this->addChild(white3);
//    
//    auto black2 = Sprite::create("white.png");
//    black2->setPosition(origin.x + 27, origin.y + 27);
//    this->addChild(black2);
//    
    return true;
}

void MainMenu::menuCloseCallback(Ref * pSender)
{
    
    Director::getInstance()->end();
    
    
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    
}

void MainMenu::menuTestCallback(Ref * pSender)
{
    MenuItem * item = (MenuItem *)pSender;
    log("MainMenu::menuTestCallback %p", item);
    
    if(Setting::effectSound) {
        SimpleAudioEngine::getInstance()->playEffect("sounds/Blip.wav");
    }
    
    auto scene = ChessBoard::createScene();
    auto sc = TransitionMoveInR::create(1.0f, scene);
    
    Director::getInstance()->pushScene(sc);
}

void MainMenu::menuPlayWithComputerCallback(Ref * pSender)
{
    MenuItem * item = (MenuItem *)pSender;
    log("MainMenu::menuPlayWithComputerCallback %p", item);
    
    if(Setting::effectSound) {
        SimpleAudioEngine::getInstance()->playEffect("sounds/Blip.wav");
    }
    
    auto scene = SelectedPlayingLevel::createScene();
    
    auto sc = TransitionFade::create(1.0f, scene);
    
    Director::getInstance()->replaceScene(sc);
}

void MainMenu::menuSettingCallback(Ref * pSender)
{
    MenuItem * item = (MenuItem *)pSender;
    log("MainMenu::menuSettingCallback %p", item);
    
    if(Setting::effectSound) {
        SimpleAudioEngine::getInstance()->playEffect("sounds/Blip.wav");
    }
    
    // 切换场景
    auto scene = Setting::createScene();
    
    auto sc = TransitionFade::create(1.0f, scene);
    
    Director::getInstance()->pushScene(sc);
    
}

void MainMenu::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    log("MainMenu::onEnterTransitionDidFinish()");
    
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    if(Setting::backgroundMusic) {
        SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/arena.mp3", true);
    }
}

