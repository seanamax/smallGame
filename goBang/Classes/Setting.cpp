//
//  Setting.cpp
//  Gobang
//
//  Created by Chris on 16/8/26.
//
//

#include "Setting.hpp"


USING_NS_CC;
using namespace CocosDenshion;

bool Setting::effectSound = false;
bool Setting::backgroundMusic = false;

Scene * Setting::createScene()
{
    Scene * scene = Scene::create();
    
    Layer * layer = Setting::create();
    
    scene->addChild(layer);
    
    return scene;
}


bool Setting::init()
{
    if(!Layer::init()) {
        return false;
    }
    
    // 获得 窗口大小及其起点
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    // 音乐 按钮
    auto settingBackgroundMusicItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting::            MenuItemToggleSettingBackgroundMusic, this), MenuItemFont::create("音乐：On"),MenuItemFont::create("音乐：Off"), NULL);
    
    settingBackgroundMusicItem->setSelectedIndex(!Setting::backgroundMusic);
    
    
    // 音效 按钮
    auto settingSoundEffectItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Setting:: MenuItemToggleSettingSoundEffect,this),MenuItemFont::create("音效：On"),MenuItemFont::create("音效：Off"), NULL);
    
    settingSoundEffectItem->setSelectedIndex(!Setting::effectSound);
    
    
    // 确认 按钮
    MenuItemFont * confirmItem = MenuItemFont::create("确定", CC_CALLBACK_1(
                                                        Setting::MenuItemConfirmCallback, this));
    
    
    Menu * mn = Menu::create(settingBackgroundMusicItem, settingSoundEffectItem, confirmItem, NULL);
 
    
    // 设置 菜单 位置及其锚点
    mn->setPosition(Vec2(origin.x + visibleSize.width / 2,
                         origin.y + visibleSize.height / 2));
    mn->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    // 排列 按钮及其菜单
    mn->alignItemsVertically();
    
    this->addChild(mn);
    
    return true;
}


void Setting::MenuItemConfirmCallback(Ref * pSender)
{
    MenuItem * item = (MenuItem *)pSender;
    log("Setting::menuComfirmCallback %p", item);
    
    if(Setting::effectSound) {
        SimpleAudioEngine::getInstance()->playEffect("sounds/Blip.wav");
    }
    
    Director::getInstance()->popScene();
}

void Setting::MenuItemToggleSettingBackgroundMusic(Ref * pSender)
{
    MenuItem * item = (MenuItem *)pSender;
    log("Setting::toggleSettingBackgroundMusic %p", item);
    
    // 进行设置音乐
    Setting::backgroundMusic = !Setting::backgroundMusic;
    
    if(Setting::backgroundMusic) {
        SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/music_logo.mp3", true);
    }
    else {
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }
    
    if(Setting::effectSound) {
        SimpleAudioEngine::getInstance()->playEffect("sounds/Blip.wav");
    }
}

void Setting::MenuItemToggleSettingSoundEffect(Ref * pSender)
{
    MenuItem * item = (MenuItem *)pSender;
    log("Setting::toggleSettingSoundEffect %p", item);
    
    Setting::effectSound = !Setting::effectSound;
    
    if(Setting::effectSound) {
        SimpleAudioEngine::getInstance()->playEffect("sounds/Blip.wav");
    }
}

void Setting::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    log("Setting::onEnterTransitionDidFinish()");
    
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    if(Setting::backgroundMusic) {
        SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/music_logo.mp3", true);
    }
}


