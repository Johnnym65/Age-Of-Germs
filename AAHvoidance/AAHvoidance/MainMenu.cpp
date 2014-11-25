//
//  MainMenu.cpp
//  AAHvoidance
//
//  Created by Johnny Murphy on 28/12/2012.
//
//

#include "AnalyticX.h"
#include "MainMenu.h"
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include "SimpleAudioEngine.h"
#include "MainGame.h"
#include "ObjCCalls.h"
#include "Globals.h"

#define PTM_RATIO 32
using namespace cocos2d;
using namespace CocosDenshion;

#define DEGTORAD 0.0174532925199432957f

MainMenu::MainMenu()
{
    //if (CCLayerColor::initWithColor( ccc4(255,255,255,255)));
    
	setTouchEnabled( true);
    size = CCDirector::sharedDirector()->getWinSize();
    visibleOrigin=CCDirector::sharedDirector()->getVisibleOrigin();
    visibleSize=CCDirector::sharedDirector()->getVisibleSize();
    
    
    scaleX = size.width/960;
    scaleY = size.height/640;
    
    std::string s;
    std::stringstream out;
    out << size.width;
    s = out.str();
    CCLog(s.c_str());
    
    std::string s1;
    std::stringstream out1;
    out1 << size.height;
    s1 = out.str();
    CCLog(s1.c_str());
    
    shapes = new CCArray();
    
    mright = false;
    mleft = false;
    
    nobonus = false;
    
    newbg = false;
    
    speed = .5;
    
    
    CCSprite* title = CCSprite::create("Title.png");
    title -> setPosition(ccp(size.width/2, size.height-size.height/6));
    title->setScaleX(scaleX);
    title->setScaleY(scaleY);
    //mainbg = title;
    this->addChild(title,400);
    
    
    
    CCSprite* bground = CCSprite::create("bground.png");
    bground -> setPosition(ccp(size.width/2, (size.height/2)));
    bground->setScaleX(scaleX);
    bground->setScaleY(scaleY);
    secondbg = bground;
    this->addChild(secondbg,-1);
    
    CCSprite* bground1 = CCSprite::create("bground.png");
    bground1 -> setPosition(ccp(size.width/2, size.height+(size.height/2)
                                ));
    bground1->setScaleX(scaleX);
    bground1->setScaleY(scaleY);
    mainbg = bground1;
    this->addChild(mainbg,-1);
    
    /*
     CCSprite* bground2 = CCSprite::create("bground.png");
     bground2 -> setPosition(ccp(size.width/2, (size.height/2)));
     latsecondbg = bground2;
     this->addChild(latsecondbg,0);
     
     
     CCSprite* bground3 = CCSprite::create("bground.png");
     bground3 -> setPosition(ccp(-size.width/2, size.height));
     latmainbg = bground3;
     this->addChild(latmainbg,0);
     */
    
  
    
    /*
     m_debugDraw = new GLESDebugDraw( PTM_RATIO );
     world->SetDebugDraw(m_debugDraw);
     
     uint32 flags = 0;
     flags += b2Draw::e_shapeBit;
     flags += b2Draw::e_jointBit;
     flags += b2Draw::e_aabbBit;
     flags += b2Draw::e_pairBit;
     flags += b2Draw::e_centerOfMassBit;
     m_debugDraw->SetFlags(flags);
     */
    
        
    
    CCMenuItemImage* play = CCMenuItemImage::create(
                                                         "menuplay.png",
                                                         "menuplay.png",
                                                         this,
                                                         menu_selector(MainMenu::playChosen));
    play->setPosition(ccp(0,75*scaleY));
    play->setScaleX(scaleX/1.1);
    play->setScaleY(scaleY/1.1);
    
    CCMenuItemImage* high = CCMenuItemImage::create(
                                                    "menuhigh.png",
                                                    "menuhigh.png",
                                                    this,
                                                    menu_selector(MainMenu::viewHighScores));
    
    high->setPosition(ccp(0,-125*scaleY));
    high->setScaleX(scaleX/1.1);
    high->setScaleY(scaleY/1.1);
    
    
    CCMenuItemImage* more = CCMenuItemImage::create(
                                                    "moregames.png",
                                                    "moregames.png",
                                                    this,
                                                    menu_selector(MainMenu::moregames));
    
    more->setPosition(ccp(visibleSize.width/2-(120*scaleX),-225*scaleY));
    more->setScaleX(scaleX/1.1);
    more->setScaleY(scaleY/1.1);
    
    
    CCMenu* menu = CCMenu::create();
    menu->addChild(play,100);
    menu->addChild(high,100);
    menu->addChild(more,100);
    this->addChild(menu,100);
    
  
    
    if(!ipadRet)
    {
       schedule( schedule_selector(MainMenu::tick) );
    }
    
    
    
    
    
    
    
    //schedule( schedule_selector(MainMenu::releaseBlocks), .5 );
    //schedule( schedule_selector(MainMenu::releaseBonuses), 1 );
    
    //schedule( schedule_selector(MainMenu::releaseBlood), 1.0 );
    
    
}

MainMenu::~MainMenu()
{
	
    
}


CCScene* MainMenu::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    MainMenu* mainMenu = new MainMenu();
    scene->addChild(mainMenu,0,0);
    mainMenu->release();
    
    return scene;
}


void MainMenu::tick(float dt)
{
    
        
    /*
     if(latsecondbg->getPositionY() <size.width)
     {
     
     
     
     }
     
     */
    mainbg->setPositionY(mainbg->getPositionY()-2);
    secondbg->setPositionY(secondbg->getPositionY()-2);
    if(mainbg->getPositionY()<=size.height/2)
    {
        //this->removeChild(newbground);
        //this->removeChild(secondbg);
        
        newbground = CCSprite::create("bground.png");
        newbground->setScaleX(scaleX);
        newbground->setScaleY(scaleY);
        newbground -> setPosition(ccp(size.width/2, size.height+(size.height/2)));
        this->addChild(newbground,-1);
        
        
        
        
        secondbg = mainbg;
        mainbg = newbground;
        
        
        //this->addChild(secondbg);
    }
    
    
    

    
}










void MainMenu::playChosen()
{
    AnalyticX::flurryLogEventTimed("Play button chosen", true);
    CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(1, MainGame::scene(), ccc3(0, 0, 0)));
}

void MainMenu::viewHighScores()
{
    AnalyticX::flurryLogEventTimed("High scores button chosen", true);
    
    ObjCCalls* objc = new ObjCCalls();
    objc->ShowLeaderboard();
    //objc->LinkAdd();
    delete objc;
    objc = NULL;
}

void MainMenu::moregames()
{
    AnalyticX::flurryLogEventTimed("More game button chosen", true);
    
    ObjCCalls* objc = new ObjCCalls();
    //objc->ShowLeaderboard();
    objc->LinkAdd();
    delete objc;
    objc = NULL;
}


string MainMenu::convertIntToString(int number)
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