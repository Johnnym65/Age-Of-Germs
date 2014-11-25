//
//  AAHvoidanceAppDelegate.cpp
//  AAHvoidance
//
//  Created by Johnny Murphy on 20/12/2012.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "MainGame.h"
#include "MainMenu.h"
#include "ObjCCalls.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "Globals.h"
#include "AnalyticX.h"


USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    
    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    // pDirector->enableRetinaDisplay(true);
    
    CCLog("size!");
    CCLog(convertIntToString(pEGLView->getFrameSize().width).c_str());
    
    if(pEGLView->getFrameSize().width == 2048)
    {
        ipadRet = true;
    }
    
    // Set the design resolution
    pEGLView->setDesignResolutionSize(480, 320,kResolutionNoBorder); //kResolutionShowAll);// kResolutionExactFit);// kResolutionNoBorder);
    
         
    
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("splat.wav");
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("splat.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("laser.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("poweron.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("poweroff.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("bonus.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("explosion.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("slowdown.wav");
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bground.wav", true);
    
    
    
    
    
    
    
    
    AnalyticX::flurrySetAppVersion("v_1_97");
    cocos2d::CCLog("--->>>get flurry version = %s", AnalyticX::flurryGetFlurryAgentVersion());
    AnalyticX::flurrySetDebugLogEnabled(false);
    AnalyticX::flurrySetSessionContinueSeconds(143);
    AnalyticX::flurrySetSecureTransportEnabled(false);
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        AnalyticX::flurryStartSession("8M3YQCF67NXWMBF2B3PJ");
    #endif
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        //AnalyticX::flurryStartSession("");
    #endif
    
    
    
    
    
    
    
    
    
    /*
    ObjCCalls* objc = new ObjCCalls();
    if( objc->IsGameCenterAPIAvailable() )
        objc->ShowAchievements();
    delete objc;
    objc = NULL;
    */
    /*
    ObjCCalls* objc = new ObjCCalls();
    objc->ShowGameCenter();
    delete objc;
    objc = NULL;
     */
    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = MainMenu::scene();

    // run
    pDirector->runWithScene(pScene);

    
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

std::string AppDelegate::convertIntToString(int number)
{
    string temp="";
    string returnvalue = "";
    
    if (number == 0)
    {
        return "0";
    }
    
    if(number < 0)
    {
        number *= -1;
        returnvalue.append("-");
    }
    
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0;i<temp.length();i++)
    {
        returnvalue+=temp[temp.length()-i-1];
    }
    temp.clear();
    return returnvalue;
}
