//
//  MainGame.cpp
//  AAHvoidance
//
//  Created by Johnny Murphy on 20/12/2012.
//
//

#include "MainGame.h"



#include "AnalyticX.h"
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include "SimpleAudioEngine.h"
#include "MainMenu.h"
#include "ObjCCalls.h"
#include "Globals.h"
#include "farway.h"

#include "SimpleAudioEngine.h"

#define PTM_RATIO 32
using namespace cocos2d;
using namespace CocosDenshion;

#define DEGTORAD 0.0174532925199432957f

MainGame::MainGame()
{
    if (CCLayerColor::initWithColor( ccc4(170,55,43,255)));
    
    //205-92-92
	setTouchEnabled( true);
    size = CCDirector::sharedDirector()->getWinSize();
    visibleOrigin=CCDirector::sharedDirector()->getVisibleOrigin();
    visibleSize=CCDirector::sharedDirector()->getVisibleSize();
    
    
    scaleX = size.width/960;
    scaleY = size.height/640;
    score = 0;
    timecheck = 0;
    level = 1;
    
    levelcheck = false;
    //musicon = true;
    //soundson = true;
    
    /*
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
    */
    shapes = new CCArray();
    
    mright = false;
    mleft = false;
    
    nobonus = false;
    
    newbg = false;
    
    speed = 1;
    bonusSpeed = 3;
    speedupspeed = 10;
    
    moving = false;
    
    check10 = false;
    check100 = false;
    check1000 = false;
    check10000 = false;
    check100000 = false;
    check1000000 = false;
    
    
    
    
    
    //int w = (int)size.width;
    //int random_integer = rand() % w  + -(size.width*1.5);
    
    /*
    farway* fway = new farway(world,ccp(size.width/2-(100*scaleX),size.height/2+(100*scaleY)),8,0);
    fway->retain();
    fway->setObjectTexture();
    fway->setScaleX(scaleX);
    fway->setScaleY(scaleY);
    fway->setPosition(ccp(fway->getPositionX(),fway->getPositionY()));
    fway->setOriginalPosition(fway->getPosition());
    fway->addBody();
    this->addChild(fway,1);
    shapes->addObject(fway);
    
    farway* fway1 = new farway(world,ccp(size.width/2+(100*scaleX),size.height/2-(100*scaleY)),8,0);
    fway1->retain();
    fway1->setObjectTexture();
    fway1->setScaleX(scaleX);
    fway1->setScaleY(scaleY);
    fway1->setPosition(ccp(fway1->getPositionX(),fway1->getPositionY()));
    fway1->setOriginalPosition(fway1->getPosition());
    fway1->addBody();
    this->addChild(fway1,1);
    shapes->addObject(fway1);
    
    */
    
    
    
    /*
    CCSprite* bground = CCSprite::create("bground.png");
    bground -> setPosition(ccp(size.width/2, (size.height/2)));
    bground->setScaleX(scaleX);
    bground->setScaleY(scaleY);
    secondbg = bground;
    this->addChild(secondbg,0);
    
    CCSprite* bground1 = CCSprite::create("bground.png");
    bground1 -> setPosition(ccp(size.width/2, size.height+(size.height/2)));
    bground1->setScaleX(scaleX);
    bground1->setScaleY(scaleY);
    mainbg = bground1;
    this->addChild(mainbg,0);
    */
    
    
    tuttouchright= CCSprite::create("Tuttouchright.png");
    tuttouchright -> setPosition(ccp(visibleOrigin.x+visibleSize.width/4*3, size.height/2));
    tuttouchright->setScaleX(scaleX);
    tuttouchright->setScaleY(scaleY);
    tuttouchright->setVisible(false);
    this->addChild(tuttouchright,100);
    
    
    tuttouchleft= CCSprite::create("Tuttouchleft.png");
    tuttouchleft -> setPosition(ccp(visibleOrigin.x+visibleSize.width/4, size.height/2));
    tuttouchleft->setScaleX(scaleX);
    tuttouchleft->setScaleY(scaleY);
    tuttouchleft->setVisible(false);
    this->addChild(tuttouchleft,100);
    
    
    tutavoid= CCSprite::create("Tutavoid.png");
    tutavoid -> setPosition(ccp(size.width/2, size.height/2));
    tutavoid->setScaleX(scaleX);
    tutavoid->setScaleY(scaleY);
    tutavoid->setVisible(false);
    this->addChild(tutavoid,100);
    
    
    tuthelp = CCSprite::create("Tuthelp.png");
    tuthelp -> setPosition(ccp(size.width/2, size.height/2));
    tuthelp->setScaleX(scaleX);
    tuthelp->setScaleY(scaleY);
    tuthelp->setVisible(false);
    this->addChild(tuthelp,100);
    
    go = CCSprite::create("Go.png");
    go -> setPosition(ccp(size.width/2, size.height/2));
    go->setScaleX(scaleX);
    go->setScaleY(scaleY);
    go->setVisible(false);
    this->addChild(go,100);
    
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
    
    srand((unsigned)time(0));
	// Define the gravity vector.
	b2Vec2 gravity;
	gravity.Set(0.0f, -30.0f);
	
	// Do we want to let bodies sleep?
	bool doSleep = true;

    
    
    world = new b2World(gravity);
    world->SetAllowSleeping(doSleep);
	world->SetContinuousPhysics(true);
    world->SetContactListener(&contactListenerInstance);
    
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
    
    p = new Player(world,ccp(size.width/2,(visibleOrigin.y+50*scaleY)),3,0);
    p->retain();
    p->setObjectTexture();
    p->setScaleX(scaleX);
    p->setScaleY(scaleY);
    p->setPosition(ccp(p->getPositionX(),p->getPositionY()));
    p->setOriginalPosition(p->getPosition());
    p->addBody();
    this->addChild(p,100);
    
    
    
    shieldbonus= CCSprite::create("shield.png");
    shieldbonus->setPosition(ccp(size.width-(200*scaleX), size.height+shieldbonus->getContentSize().height/2));
    shieldbonus->setScaleX(scaleX);
    shieldbonus->setScaleY(scaleY);
    shieldbonus->setVisible(false);
    this->addChild(shieldbonus,200);
    
    smallbonus= CCSprite::create("small.png");
    smallbonus->setPosition(ccp(size.width-(200*scaleX), size.height+shieldbonus->getContentSize().height/2));
    smallbonus->setScaleX(scaleX);
    smallbonus->setScaleY(scaleY);
    smallbonus->setVisible(false);
    this->addChild(smallbonus,200);
    
    gunbonus= CCSprite::create("gun.png");
    gunbonus->setPosition(ccp(size.width-(200*scaleX), size.height+shieldbonus->getContentSize().height/2));
    gunbonus->setScaleX(scaleX);
    gunbonus->setScaleY(scaleY);
    gunbonus->setVisible(false);
    this->addChild(gunbonus,200);
    
    rotatebonus= CCSprite::create("rotate.png");
    rotatebonus->setPosition(ccp(size.width-(200*scaleX), size.height+shieldbonus->getContentSize().height/2));
    rotatebonus->setScaleX(scaleX);
    rotatebonus->setScaleY(scaleY);
    rotatebonus->setVisible(false);
    this->addChild(rotatebonus,200);
    
    
    
    
    string timeholder = convertIntToString(score);
    
    //timeholder.insert(2,":");
    
    timerdisplay = CCLabelTTF::create(timeholder.c_str(), "CornFed.ttf", 50);
    //CCLabelTTF::labelWithString(timeholder.c_str(),"Ariel", 40);
    timerdisplay->setScaleX(scaleX);
    timerdisplay->setScaleY(scaleY);
    timerdisplay->setPosition(ccp(visibleOrigin.x+220*scaleX,visibleOrigin.y+visibleSize.height-40*scaleY));
    //timerdisplay->setColor(ccc3(127,255,0));
    this->addChild(timerdisplay, 1000);
    
    
    /*
    CCLabelTTF* score = CCLabelTTF::create("Score:", "Ariel", 50);
    score->setScaleX(scaleX);
    score->setScaleY(scaleY);
    score->setPosition(ccp(score->getContentSize().width/2,size.height-(score->getContentSize().height/2)));
    score->setColor(ccc3(0,0,0));
    this->addChild(score, 1000);
    */
    
    
    CCSprite* scoreimage= CCSprite::create("score.png");
    scoreimage->setPosition(ccp(visibleOrigin.x+ 100*scaleX,visibleOrigin.y+visibleSize.height-40*scaleY));
    scoreimage->setScaleX(scaleX);
    scoreimage->setScaleY(scaleY);
    //scoreimage->setColor(ccc3(127,255,0));
    this->addChild(scoreimage,200);
    
    hscoreimage= CCSprite::create("highs.png");
    hscoreimage->setPosition(ccp(visibleOrigin.x+160*scaleX,visibleOrigin.y+visibleSize.height-90*scaleY));
    hscoreimage->setScaleX(scaleX);
    hscoreimage->setScaleY(scaleY);
    hscoreimage->setVisible(false);
    //scoreimage->setColor(ccc3(127,255,0));
    this->addChild(hscoreimage,200);
    
    string highsholder = convertIntToString(CCUserDefault::sharedUserDefault()->getIntegerForKey("highscore"));
    
    //timeholder.insert(2,":");
    
    highsdisplay = CCLabelTTF::create(highsholder.c_str(), "CornFed.ttf", 50);
    //CCLabelTTF::labelWithString(timeholder.c_str(),"Ariel", 40);
    highsdisplay->setScaleX(scaleX);
    highsdisplay->setScaleY(scaleY);
    highsdisplay->setPosition(ccp(visibleOrigin.x+330*scaleX,visibleOrigin.y+visibleSize.height-90*scaleY));
    //timerdisplay->setColor(ccc3(127,255,0));
    highsdisplay->setVisible(false);
    this->addChild(highsdisplay, 1000);
    
    
    
    
    levelimage= CCSprite::create("level.png");
    levelimage->setPosition(ccp(visibleOrigin.x+100*scaleX,visibleOrigin.y+40*scaleY));
    levelimage->setScaleX(scaleX);
    levelimage->setScaleY(scaleY);
    this->addChild(levelimage,200);
    
    string levelholder = convertIntToString(level);
    
    //timeholder.insert(2,":");
    
    levelsdisplay = CCLabelTTF::create(levelholder.c_str(), "CornFed.ttf", 50);
    //CCLabelTTF::labelWithString(timeholder.c_str(),"Ariel", 40);
    levelsdisplay->setScaleX(scaleX);
    levelsdisplay->setScaleY(scaleY);
    levelsdisplay->setPosition(ccp(visibleOrigin.x+220*scaleX,visibleOrigin.y+40*scaleY));
    //timerdisplay->setColor(ccc3(127,255,0));
    this->addChild(levelsdisplay, 1000);
    
    
    
    
    dierestart = CCMenuItemImage::create(
                                                    "dierestart.png",
                                                    "dierestart.png",
                                                    this,
                                                    menu_selector(MainGame::dierestartchosen));
    dierestart->setPosition(ccp(0,100*scaleY));
    dierestart->setScaleX(scaleX);
    dierestart->setScaleY(scaleY);
    dierestart->setVisible(false);
    dierestart->setEnabled(false);
    
    diemenu = CCMenuItemImage::create(
                                                    "diemenu.png",
                                                    "diemenu.png",
                                                    this,
                                                    menu_selector(MainGame::diemenuchosen));
    
    diemenu->setPosition(ccp(0,-100*scaleY));
    diemenu->setScaleX(scaleX);
    diemenu->setScaleY(scaleY);
    diemenu->setVisible(false);
    diemenu->setEnabled(false);
    
    
    diehighscore = CCMenuItemImage::create(
                                      "highscores.png",
                                      "highscores.png",
                                      this,
                                      menu_selector(MainGame::diehighchosen));
    
    diehighscore->setPosition(ccp(130*scaleX,visibleOrigin.y+visibleSize.height/2-550*scaleY));
    diehighscore->setScaleX(scaleX);
    diehighscore->setScaleY(scaleY);
    diehighscore->setVisible(false);
    diehighscore->setEnabled(false);
    
    
    CCMenu* menu = CCMenu::create();
    menu->addChild(dierestart,3);
    menu->addChild(diemenu,3);
    menu->addChild(diehighscore,3);
    this->addChild(menu,2000);
    
    
    
    
    
    pauseresume = CCMenuItemImage::create(
                                           "pauseresume.png",
                                           "pauseresume.png",
                                           this,
                                           menu_selector(MainGame::pauseresumechosen));
    pauseresume->setPosition(ccp(0,120*scaleY));
    pauseresume->setScaleX(scaleX);
    pauseresume->setScaleY(scaleY);
    pauseresume->setVisible(false);
    pauseresume->setEnabled(false);
    
    
    pauserestart = CCMenuItemImage::create(
                                         "pauserestart.png",
                                         "pauserestart.png",
                                         this,
                                         menu_selector(MainGame::pauserestartchosen));
    pauserestart->setPosition(ccp(130*scaleX,-100*scaleY));
    pauserestart->setScaleX(scaleX);
    pauserestart->setScaleY(scaleY);
    pauserestart->setVisible(false);
    pauserestart->setEnabled(false);
    
    pausemenu = CCMenuItemImage::create(
                                      "pausemenu.png",
                                      "pausemenu.png",
                                      this,
                                      menu_selector(MainGame::pausemenuchosen));
    
    pausemenu->setPosition(ccp(-130*scaleX,-100*scaleY));
    pausemenu->setScaleX(scaleX);
    pausemenu->setScaleY(scaleY);
    pausemenu->setVisible(false);
    pausemenu->setEnabled(false);
    
    
    music = CCMenuItemImage::create(
                                        "music.png",
                                        "music.png",
                                        this,
                                        menu_selector(MainGame::musiconoff));
    
    music->setPosition(ccp(-visibleSize.width/2+60*scaleX,-visibleSize.height/2+(50*scaleY)));
    music->setScaleX(scaleX/2);
    music->setScaleY(scaleY/2);
    music->setVisible(false);
    music->setEnabled(false);
    
    
    sounds = CCMenuItemImage::create(
                                        "sounds.png",
                                        "sounds.png",
                                        this,
                                        menu_selector(MainGame::soundsonoff));
    
    sounds->setPosition(ccp(-visibleSize.width/2+160*scaleX,-visibleSize.height/2+(50*scaleY)));
    sounds->setScaleX(scaleX/2);
    sounds->setScaleY(scaleY/2);
    sounds->setVisible(false);
    sounds->setEnabled(false);
    
    
    CCMenu* menu1 = CCMenu::create();
    menu1->addChild(pauseresume,4);
    menu1->addChild(pauserestart,3);
    menu1->addChild(pausemenu,3);
    menu1->addChild(music,3);
    menu1->addChild(sounds,3);
    this->addChild(menu1,2000);
    
    
    pause = CCMenuItemImage::create(
                                        "pause.png",
                                        "pause.png",
                                        this,
                                        menu_selector(MainGame::pausemenuPopUp));
    
    pause->setPosition(ccp(visibleSize.width/2-(50*scaleX), visibleSize.height/2-60*scaleY));
    pause->setScaleX(scaleX);
    pause->setScaleY(scaleY);
    //pause->setColor(ccc3(127,255,0));
    
    CCMenu* menu2 = CCMenu::create();
    menu2->addChild(pause,3);
    this->addChild(menu2,2000);
    
    schedule( schedule_selector(MainGame::tick) );
    
    if(CCUserDefault::sharedUserDefault()->getBoolForKey("tutcomplete"))
    {
        
        this->removeChild(tuthelp);
        this->removeChild(tuttouchright);
        this->removeChild(tuttouchleft);
        this->removeChild(tutavoid);
        this->removeChild(go);
    
        schedule( schedule_selector(MainGame::speedUp), speedupspeed);
        schedule( schedule_selector(MainGame::releaseBlocks), speed );
        schedule( schedule_selector(MainGame::releaseBonuses), bonusSpeed );
        schedule( schedule_selector(MainGame::releasePlates), bonusSpeed );
        schedule( schedule_selector(MainGame::releaseBlood), 1.0 );
        schedule( schedule_selector(MainGame::releasefarways), 2 );
        schedule(schedule_selector(MainGame::timers), .1 );
    }
    
    else
    {
        schedule( schedule_selector(MainGame::Tutorial), 3);
    }
    
}

MainGame::~MainGame()
{
	
    
}


CCScene* MainGame::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    MainGame* mainGame = new MainGame();
    scene->addChild(mainGame,0,0);
    mainGame->release();
    
    return scene;
}

//FIX TIME STEP
///////--->>>>>>>>>>>>>
const float32 FIXED_TIMESTEP = 1.0f / 60.0f;

// Minimum remaining time to avoid box2d unstability caused by very small delta times
// if remaining time to simulate is smaller than this, the rest of time will be added to the last step,
// instead of performing one more single step with only the small delta time.
const float32 MINIMUM_TIMESTEP = 1.0f / 600.0f;

const int32 VELOCITY_ITERATIONS = 8;
const int32 POSITION_ITERATIONS = 8;

// maximum number of steps per tick to avoid spiral of death
const int32 MAXIMUM_NUMBER_OF_STEPS = 25;



void MainGame::step(float dt) {
    float32 frameTime = dt;
    int stepsPerformed = 0;
    while ( (frameTime > 0.0) && (stepsPerformed < MAXIMUM_NUMBER_OF_STEPS) ){
        float32 deltaTime = std::min( frameTime, FIXED_TIMESTEP );
        frameTime -= deltaTime;
        if (frameTime < MINIMUM_TIMESTEP) {
            deltaTime += frameTime;
            frameTime = 0.0f;
        }
        world->Step(deltaTime,VELOCITY_ITERATIONS,POSITION_ITERATIONS);
        stepsPerformed++;
       // this->afterStep(); // process collisions and result from callbacks called by the step
    }
    world->ClearForces ();
}

/*
void MainGame::draw()
{
    //
    // IMPORTANT:
    // This is only for debug purposes
    // It is recommend to disable it
    //
    CCLayer::draw();
    
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    
    kmGLPushMatrix();
    
    // line: color, width, aliased
    // glLineWidth > 1 and GL_LINE_SMOOTH are not compatible
    // GL_SMOOTH_LINE_WIDTH_RANGE = (1,1) on iPhone
    //    glDisable(GL_LINE_SMOOTH);
    glLineWidth( 1.0f );
    ccDrawColor4B(0,0,0,255);
 
    
    //ccDrawLine( ccp(0, size.height/2), ccp(size.width*2, size.height/2) );
    
    world->DrawDebugData();
    
    kmGLPopMatrix();
    
    CCLog("dsfdsfgdsgvdfsvdfgvdfs");
}

*/
void MainGame::tick(float dt)
{
    
    float dtStep=dt;
    
    step(dtStep);
    
    /*
    if(latsecondbg->getPositionY() <size.width)
    {
        
        
     
    }
    
    */
    /*
    mainbg->setPositionY(mainbg->getPositionY()-1);
    secondbg->setPositionY(secondbg->getPositionY()-1);
    if(mainbg->getPositionY()<=size.height/2)
    {
        //this->removeChild(newbground);
        //this->removeChild(secondbg);
        
        newbground = CCSprite::create("bground.png");
        newbground->setScaleX(scaleX);
        newbground->setScaleY(scaleY);
        newbground -> setPosition(ccp(size.width/2, size.height+(size.height/2)));
        this->addChild(newbground,0);
        
        
            
        
        secondbg = mainbg;
        mainbg = newbground;
    
        
        //this->addChild(secondbg);
    }
    

    */
    /*
    if(p->getOpacity() == 50)
    {
        CCSprite* 
        //bonusSprite->set
        bonusSprite->setVisible(true);
    }
    */
    
    if(p->invinciblebonusOn || p->smallbonusOn || p->shootOn || p->slowdownOn)
    {
        nobonus = true;
        
        
    }
    else
    {
        nobonus = false;
        moving = false;
    }
    
        if(p->invinciblebonusOn)
        {
            shieldbonus->setVisible(true);
            
            if(!moving)
            {
                schedule(schedule_selector(MainGame::movebonus), .01 );
                moving = true;
                
                this->runAction(CCSequence::create(CCDelayTime::create(9.5),CCCallFunc::create(this,callfunc_selector(MainGame::startback)),NULL));
            }
            
        }
        else
        {
            shieldbonus->setVisible(false);
            
        }
        
        if(p->smallbonusOn)
        {
            smallbonus->setVisible(true);
            
            if(!moving)
            {
                schedule(schedule_selector(MainGame::movebonus), .01 );
                moving = true;
                this->runAction(CCSequence::create(CCDelayTime::create(9.5),CCCallFunc::create(this,callfunc_selector(MainGame::startback)),NULL));
            }
        }
        else
        {
            smallbonus->setVisible(false);
         
        }
        
        if(p->shootOn)
        {
            gunbonus->setVisible(true);
            
            if(!moving)
            {
                schedule(schedule_selector(MainGame::movebonus), .01 );
                moving = true;
                this->runAction(CCSequence::create(CCDelayTime::create(9.5),CCCallFunc::create(this,callfunc_selector(MainGame::startback)),NULL));
            }
        }
        else
        {
            gunbonus->setVisible(false);
            
        }
        
        if(p->slowdownOn)
        {
            rotatebonus->setVisible(true);
            
            if(!moving)
            {
                schedule(schedule_selector(MainGame::movebonus), .01 );
                moving = true;
                this->runAction(CCSequence::create(CCDelayTime::create(9.5),CCCallFunc::create(this,callfunc_selector(MainGame::startback)),NULL));
            }
        }
        else
        {
            rotatebonus->setVisible(false);
            
        }
    
    
    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
        
		if (b->GetUserData() != NULL) {
			//Synchronize the AtlasSprites position and rotation with the corresponding body
            GameObject* myActor = (GameObject*)b->GetUserData();
            
            
            myActor->setPosition( CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
            
            
            myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
            
            
            
            //remove object if tag is 1000,999
            if(myActor->getTag()==1000)
            {
                world->DestroyBody(b);
            }
            if(myActor->getTag()==999){
                /*int rowNumber=(myActor->getGameWorldCellPosition().y)/cellSize;
                 int colNumber=(myActor->getGameWorldCellPosition().x)/cellSize;
                 placedObjectsArray[rowNumber][colNumber]=NULL;*/
                
                world->DestroyBody(b);
                /*
                 if( myActor->retainCount()>1){
                 myActor->release();
                 }*/
                
                // myActor->autorelease();
                this->removeChild(myActor, false);
                //myActor->release();
            }
            
		}
	}
    
    
    
    
    
    CCObject* obj;
    CCARRAY_FOREACH(shapes,obj)
    {
        Square* s = (Square*) obj;
        if(p->slowdownOn)
        {
            s->slowdown = 0;
        }
        else
            s->slowdown = 1;
        
        if(mleft)
        {

            s->movingleft = true;
            s->movingright = false;
            s->straight = false;
            
        }
        if(mright)
        {
            s->movingright = true;
            s->movingleft = false;
            s->straight = false;
        }
        if(!mright && !mleft)
        {
            
            s->straight = true;
            s->movingleft = false;
            s->movingright = false;
            
        }
    }
    
    CCObject* obj1;
    CCARRAY_FOREACH(shapes,obj1)
    {
        GameObject* g = (GameObject*)obj1;
        
        if(g->getID() == 2 && nobonus)
        {
            g->setTag(999);
        }
    }
    
    
    
    
}



void MainGame::ccTouchesBegan( CCSet *pTouches, CCEvent *pEvent )
{
    //Add a new body/atlas sprite at the touched location
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = pTouches->begin(); it != pTouches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint location = touch->getLocationInView();
        
        location = CCDirector::sharedDirector()->convertToGL(location);
        
        if(location.x < size.width/2)
        {
            //CCLog("left");
            
            p->turnLeft();
            
                mright = true;
                mleft = false;
                /*
                Square* s = (Square*)obj;
                s->movingright = false;
                s->straight = false;
                s->movingleft = true;
                */
            
            
            //schedule( schedule_selector(MainGame::moveleft), .01 );
            
        }
        
        else
        {
            
            //CCLog("right");
            
            p->turnRight();
            
                mleft = true;
                mright = false;
                /*
                Square* s = (Square*)obj;
                s->movingright = true;
                s->straight = false;
                s->movingleft = false;
                */
            
            
        }
        
        
    }
}


void MainGame::ccTouchesMoved( CCSet *pTouches, CCEvent *pEvent )
{
}

void MainGame::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
    
}

void MainGame::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
{
    
    
    p->setObjectTexture();
        mleft = false;
        mright = false;
    
    p->lookingLeft = false;
    p->lookingRight = false;
    
}




void MainGame::releaseBlocks()
{
    
    /*
    srand((unsigned)time(0));
    int random_integer;
    int lowest=0, highest=size.width;
    int range=(highest-lowest)+1;
    random_integer = lowest+int(range*rand()/(size.width + 1.0));
    */
    int w = (int)size.width*4;
    int random_integer = rand() % w  + -(size.width*1.5);
   
    int rscale = rand() % 250  + 100;
    
    rscale /= 100;
    Square* s = new Square(world,ccp(random_integer,size.height+(200*scaleY)),1,0);
    s->retain();
    s->setObjectTexture();
    s->setScaleX(scaleX);
    s->setScaleY(scaleY);
    s->setPosition(ccp(s->getPositionX(),s->getPositionY()));
    s->setOriginalPosition(s->getPosition());
    
    s->setScaleX(s->getScaleX()*rscale);
    s->setScaleY(s->getScaleY()*rscale);
    s->addBody();
    //s->getBody()->s
    this->addChild(s,100);
    shapes->addObject(s);
    //s->setRotation(45*DEGTORAD);
}

void MainGame::releaseBonuses()
{
    //if(!nobonus)
   // {
        int w = (int)size.width*4;
        int random_integer = rand() % w  + -(size.width*1.5);
        
        Bonus* s = new Bonus(world,ccp(random_integer,size.height+(200*scaleY)),2,0);
        s->retain();
        s->setObjectTexture();
        s->setScaleX(scaleX);
        s->setScaleY(scaleY);
        s->setPosition(ccp(s->getPositionX(),s->getPositionY()));
        s->setOriginalPosition(s->getPosition());
        s->addBody();
        this->addChild(s,100);
        
        
        shapes->addObject(s);
        
    //}
}

void MainGame::releasefarways()
{
    //if(!nobonus)
    // {
    int w = (int)size.width*4;
    int random_integer = rand() % w  + -(size.width*1.5);
    
    farway* s = new farway(world,ccp(random_integer,size.height+(200*scaleY)),8,0);
    s->retain();
    s->setObjectTexture();
    s->setScaleX(scaleX);
    s->setScaleY(scaleY);
    s->setPosition(ccp(s->getPositionX(),s->getPositionY()));
    s->setOriginalPosition(s->getPosition());
    s->addBody();
    this->addChild(s,1);
    
    
    shapes->addObject(s);
    
    //}
}


void MainGame::moveleft()
{
    
}

void MainGame::moveright()
{
    
}



void MainGame::speedUp()
{
    if(levelcheck && !highsdisplay->isVisible())
    {
        level++;
        levelcheck= false;
    }
        
    
    levelsdisplay->setString(convertIntToString(level).c_str());
    
    speed*=.75;
    bonusSpeed*=.75;
    speedupspeed *=1.25;
    unschedule( schedule_selector(MainGame::releaseBlocks) );
    unschedule( schedule_selector(MainGame::releaseBonuses) );
    unschedule( schedule_selector(MainGame::speedUp) );
    
    schedule( schedule_selector(MainGame::releaseBlocks), speed );
    schedule( schedule_selector(MainGame::releaseBonuses), bonusSpeed );
    schedule( schedule_selector(MainGame::speedUp), speedupspeed );
    
    //CCLOG("SPEEDING UP!");
    
    levelcheck = true;
}


void MainGame::releaseBlood()
{
    int w = (int)size.width*4;
    int random_integer = rand() % w  + -(size.width*1.5);
    
    Blood* s = new Blood(world,ccp(random_integer,size.height+(200*scaleY)),6,0);
    s->retain();
    s->setObjectTexture();
    s->setScaleX(scaleX);
    s->setScaleY(scaleY);
    s->setPosition(ccp(s->getPositionX(),s->getPositionY()));
    s->setOriginalPosition(s->getPosition());
    s->addBody();
    this->addChild(s,2);
    
    
    shapes->addObject(s);
}

void MainGame::releasePlates()
{
    int w = (int)size.width*4;
    int random_integer = rand() % w  + -(size.width*1.5);
    
    Platelet* s = new Platelet(world,ccp(random_integer,size.height+(200*scaleY)),7,0);
    s->retain();
    s->setObjectTexture();
    s->setScaleX(scaleX);
    s->setScaleY(scaleY);
    s->setPosition(ccp(s->getPositionX(),s->getPositionY()));
    s->setOriginalPosition(s->getPosition());
    s->addBody();
    this->addChild(s,100);
    
    
    shapes->addObject(s);
}

string MainGame::convertIntToString(int number)
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

void MainGame::timers()
{
    
    timecheck +=1;
    
    //CCLOG(convertIntToString(timecheck).c_str());
    
    if(timecheck > speedupspeed)
    {
        timecheck = 0;
    }
    
        score+=1;
        
        string time = convertIntToString(score);
        //CCLog(time.c_str());
        timerdisplay->setString(time.c_str());
    
    if(score >= 10 && !check10)
    {
        timerdisplay->setPositionX(timerdisplay->getPositionX()+(10*scaleX));
        check10 = true;
    }
    if(score >= 100 && !check100)
    {
        timerdisplay->setPositionX(timerdisplay->getPositionX()+(10*scaleX));
        check100 = true;
    }
    if(score >= 1000 && !check1000)
    {
        timerdisplay->setPositionX(timerdisplay->getPositionX()+(10*scaleX));
        check1000 = true;
    }
    if(score >= 10000 && !check10000)
    {
        timerdisplay->setPositionX(timerdisplay->getPositionX()+(10*scaleX));
        check10000 = true;
    }
    if(score >= 100000 && !check100000)
    {
        timerdisplay->setPositionX(timerdisplay->getPositionX()+(10*scaleX));
        check100000 = true;
    }
    if(score >= 1000000 && !check1000000)
    {
        timerdisplay->setPositionX(timerdisplay->getPositionX()+(10*scaleX));
        check1000000 = true;
    }
    
    
    
}

void MainGame::addScore(int addition)
{
    score+= addition;
}


void MainGame::dierestartchosen()
{
     AnalyticX::flurryLogEventTimed("died restart chosen", true);
    CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(1, MainGame::scene(), ccc3(0, 0, 0)));
}
void MainGame::diemenuchosen()
{
     AnalyticX::flurryLogEventTimed("died menu chosen", true);
    CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(1, MainMenu::scene(), ccc3(0, 0, 0)));
}
void MainGame::diehighchosen()
{
    AnalyticX::flurryLogEventTimed("died highscores chosen", true);

    
    ObjCCalls* objc = new ObjCCalls();
    objc->ShowLeaderboard();
    //objc->LinkAdd();
    delete objc;
    objc = NULL;
}


void MainGame::pauseresumechosen()
{
    AnalyticX::flurryLogEventTimed("Paused resume", true);

    
    p->resumeSchedulerAndActions();
    this->resumeSchedulerAndActions();
    
    pauseresume->setVisible(false);
    pauseresume->setEnabled(false);
    
    pauserestart->setVisible(false);
    pauserestart->setEnabled(false);
    
    pausemenu->setVisible(false);
    pausemenu->setEnabled(false);
    
    pause->setEnabled(true);
    pause->setVisible(true);
    
    
    music->setVisible(false);
    music->setEnabled(false);
    
    sounds->setVisible(false);
    sounds->setEnabled(false);
    
    schedule( schedule_selector(MainGame::tick) );
    //CCLOG("check");
    //CCLOG(convertIntToString(timecheck).c_str());
    schedule( schedule_selector(MainGame::speedUp), timecheck);
    
    schedule( schedule_selector(MainGame::releaseBlocks), bonusSpeed );
    schedule( schedule_selector(MainGame::releaseBonuses), speed );
    
    schedule( schedule_selector(MainGame::releaseBlood), 1.0 );
    schedule( schedule_selector(MainGame::releasefarways), 2 );
    schedule(schedule_selector(MainGame::timers), .1 );
}

void MainGame::pauserestartchosen()
{
    AnalyticX::flurryLogEventTimed("Paused restart chosen", true);

    CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(1, MainGame::scene(), ccc3(0, 0, 0)));
}
void MainGame::pausemenuchosen()
{
    AnalyticX::flurryLogEventTimed("Paused back to main menu chosen", true);
    
    CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(1, MainMenu::scene(), ccc3(0, 0, 0)));
    
    
}


void MainGame::pausemenuPopUp()
{
    AnalyticX::flurryLogEventTimed("pause chosen", true);
    
    if(musicon)
    {
        music->setNormalImage(CCSprite::create("music.png"));

    }
    else
    {
        music->setNormalImage(CCSprite::create("musicoff.png"));
    }
    if(soundson)
    {
        sounds->setNormalImage(CCSprite::create("sounds.png"));
        
    }
    else
    {
        sounds->setNormalImage(CCSprite::create("soundoff.png"));
    }
    
    
    
    
    
    
    
    p->pauseSchedulerAndActions();
    this->pauseSchedulerAndActions();
    
    timecheck = speedupspeed- timecheck;
    
    pause->setEnabled(false);
    pause->setVisible(false);
    
    unschedule( schedule_selector(MainGame::tick) );
    
    
    unschedule( schedule_selector(MainGame::speedUp));
    
    unschedule( schedule_selector(MainGame::releaseBlocks));
    unschedule( schedule_selector(MainGame::releaseBonuses));
    
    unschedule( schedule_selector(MainGame::releaseBlood) );
    unschedule( schedule_selector(MainGame::releasefarways) );
    
    unschedule(schedule_selector(MainGame::timers));
    
    
    pauseresume->setVisible(true);
    pauseresume->setEnabled(true);
    
    pauserestart->setVisible(true);
    pauserestart->setEnabled(true);
    
    pausemenu->setVisible(true);
    pausemenu->setEnabled(true);
    
    music->setVisible(true);
    music->setEnabled(true);
    
    sounds->setVisible(true);
    sounds->setEnabled(true);
    
    //CCLOG("check");
    //CCLOG(convertIntToString(timecheck).c_str());
}



void MainGame::diemenuPopUp()
{
    AnalyticX::flurryLogEventTimed("The Player died", true);
    
    if(score> CCUserDefault::sharedUserDefault()->getIntegerForKey("highscore"))
    {
        highsdisplay->setString(convertIntToString(score).c_str());
        CCUserDefault::sharedUserDefault()->setIntegerForKey("highscore", score);
        CCUserDefault::sharedUserDefault()->flush();
    }
    
    
    
    if(CCUserDefault::sharedUserDefault()->getIntegerForKey("highscore") >= 10)
    {
        highsdisplay->setPositionX(highsdisplay->getPositionX()+(13*scaleX));
        
    }
    if(CCUserDefault::sharedUserDefault()->getIntegerForKey("highscore") >= 100)
    {
        highsdisplay->setPositionX(highsdisplay->getPositionX()+(13*scaleX));
        
    }
    if(CCUserDefault::sharedUserDefault()->getIntegerForKey("highscore") >= 1000)
    {
        highsdisplay->setPositionX(highsdisplay->getPositionX()+(13*scaleX));
        
    }
    if(CCUserDefault::sharedUserDefault()->getIntegerForKey("highscore") >= 10000)
    {
        highsdisplay->setPositionX(highsdisplay->getPositionX()+(13*scaleX));
        
    }
    if(CCUserDefault::sharedUserDefault()->getIntegerForKey("highscore") >= 100000)
    {
        highsdisplay->setPositionX(highsdisplay->getPositionX()+(13*scaleX));
        
    }
    if(CCUserDefault::sharedUserDefault()->getIntegerForKey("highscore") >= 1000000)
    {
        highsdisplay->setPositionX(highsdisplay->getPositionX()+(13*scaleX));
        
    }
    
    
    
    
    
    
    
    highsdisplay->setVisible(true);
    hscoreimage->setVisible(true);
    
    
    ObjCCalls* objc = new ObjCCalls();
    objc->ReportScore(score);
    objc->FullScreenAdd();
    delete objc;
    objc = NULL;
    
    dierestart->setVisible(true);
    dierestart->setEnabled(true);
    
    diemenu->setVisible(true);
    diemenu->setEnabled(true);
    
    diehighscore->setVisible(true);
    diehighscore->setEnabled(true);
    
    pause->setEnabled(false);
    pause->setVisible(false);
    
    
    
}

void MainGame::pausec()
{
    
}


void MainGame::movebonus()
{
    shieldbonus->setPositionY(shieldbonus->getPositionY()-(3*scaleY));
    gunbonus->setPositionY(gunbonus->getPositionY()-(3*scaleY));
    rotatebonus->setPositionY(rotatebonus->getPositionY()-(3*scaleY));
    smallbonus->setPositionY(smallbonus->getPositionY()-(3*scaleY));
    
    if(shieldbonus->getPositionY() < (visibleOrigin.y+visibleSize.height-(50*scaleY)))
    {
        shieldbonus->setPositionY(visibleOrigin.y+visibleSize.height-(50*scaleY));
        unschedule(schedule_selector(MainGame::movebonus));
    }
    
  
}

void MainGame::movebonusback()
{
    //moving = false;
    shieldbonus->setPositionY(shieldbonus->getPositionY()+(3*scaleY));
    gunbonus->setPositionY(gunbonus->getPositionY()+(3*scaleY));
    rotatebonus->setPositionY(rotatebonus->getPositionY()+(3*scaleY));
    smallbonus->setPositionY(smallbonus->getPositionY()+(3*scaleY));
    
    if(shieldbonus->getPositionY() > visibleSize.height+shieldbonus->getContentSize().height/2)
    {
        shieldbonus->setPositionY(visibleSize.height+shieldbonus->getContentSize().height/2);
        unschedule(schedule_selector(MainGame::movebonusback));
        
        
    }
    
    
}

void MainGame::startback()
{
    schedule(schedule_selector(MainGame::movebonusback),.01);
}

void MainGame::musiconoff()
{
    AnalyticX::flurryLogEventTimed("music ON/OFF", true);
    
    if(musicon)
    {
        music->setNormalImage(CCSprite::create("musicoff.png"));
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
        musicon = false;
    }
    else
    {
        music->setNormalImage(CCSprite::create("music.png"));
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(100);
        musicon = true;
    }
    
}

void MainGame::soundsonoff()
{
    AnalyticX::flurryLogEventTimed("sound ON/OFF", true);
    if(soundson)
    {
        sounds->setNormalImage(CCSprite::create("soundoff.png"));
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0);
        soundson = false;
        
    }
    else
    {
        sounds->setNormalImage(CCSprite::create("sounds.png"));
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(100);
        soundson = true;
    }
    
}

void MainGame::Tutorial()
{
    if(tutseq == 0)
    {
        tuttouchright->setVisible(true);
        tutseq++;
    }
    else if(tutseq == 1)
    {
        this->removeChild(tuttouchright);
        
        //tuttouchright->setVisible(false);
        tuttouchleft->setVisible(true);
        tutseq++;
    }
    else if(tutseq == 2)
    {
        this->removeChild(tuttouchleft);
        //tuttouchleft->setVisible(false);
        tutavoid->setVisible(true);
        tutseq++;
    }
    else if(tutseq == 3)
    {
        this->removeChild(tutavoid);
        //tutavoid->setVisible(false);
        tuthelp->setVisible(true);
        tutseq++;
    }
    else if(tutseq == 4)
    {
        
        CCUserDefault::sharedUserDefault()->setBoolForKey("tutcomplete", true);
        CCUserDefault::sharedUserDefault()->flush();
        
        this->removeChild(tuthelp);
        //tuthelp->setVisible(false);
        go->setVisible(true);
        tutseq++;
        unschedule( schedule_selector(MainGame::Tutorial));
        schedule( schedule_selector(MainGame::goddis),.01);

        schedule( schedule_selector(MainGame::speedUp), speedupspeed);
        schedule( schedule_selector(MainGame::releaseBlocks), speed );
        schedule( schedule_selector(MainGame::releaseBonuses), bonusSpeed );
        schedule( schedule_selector(MainGame::releasePlates), bonusSpeed );
        schedule( schedule_selector(MainGame::releaseBlood), 1.0 );
        schedule(schedule_selector(MainGame::timers), .1 );
    }
}

void MainGame::goddis()
{
    go->setOpacity(go->getOpacity()-5);
    if(go->getOpacity() <10)
    {
        unschedule( schedule_selector(MainGame::goddis));
        this->removeChild(go);
    }
}



