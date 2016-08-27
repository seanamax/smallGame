#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "MainMenu.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

static cocos2d::Size normalSize = cocos2d::Size(960, 640);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    if(!glview) {
        glview = GLViewImpl::create("五子棋");
        director->setOpenGLView((glview));
        glview->setFrameSize(normalSize.width, normalSize.height);
    }

    director->setDisplayStats(false);
    
    director->setAnimationInterval(1.0f/60);
    
    auto scene = MainMenu::createScene();
    
    //auto sc = TransitionSlideInL::create(1.0f, scene);
    
    director->runWithScene(scene);
    
    // 加载背景音乐
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sounds/arena.mp3");
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sounds/music_logo.mp3");
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sounds/Synth.mp3");
    
    
    // 加载音乐
    SimpleAudioEngine::getInstance()->preloadEffect("sounds/Blip.wav");
    
    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
