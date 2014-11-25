//
//  MainGame.h
//  AAHvoidance
//
//  Created by Johnny Murphy on 20/12/2012.
//
//

#ifndef __AAHvoidance__MainGame__
#define __AAHvoidance__MainGame__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Square.h"
#include "Box2D.h"

#include "GameObject.h"
#include "PhysicsObject.h"
#include "Player.h"
#include "Bonus.h"
#include "GLES-Render.h"
#include "ContactListener.h"
#include "Blood.h"
#include "Platelet.h"

using namespace cocos2d;

class MainGame : public cocos2d::CCLayerColor
{
public:
    ~MainGame();
    MainGame();
    
    void step(float dt);
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
    
    //void draw();
    void tick(float dt);
    
    
    void releaseBlocks();
    void releaseBonuses();
    void releaseBlood();
    void releasePlates();
    void releasefarways();
    
    
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    
    void moveleft();
    void moveright();
    
    void speedUp();
    
    void dierestartchosen();
    void diemenuchosen();
    void diehighchosen();
    
    void pauseresumechosen();
    void pauserestartchosen();
    void pausemenuchosen();
    
    void musiconoff();
    void soundsonoff();
    
    void diemenuPopUp();
    void pausemenuPopUp();
    
    
    void pausec();
    
    void movebonus();
    void startback();
    void movebonusback();
    
    void Tutorial();
    
    
    bool mright;
    bool mleft;
    CCArray* shapes;
    
    void timers();
    string convertIntToString(int number);
    
    void addScore(int);
    
    void goddis();
    private:
    
    CCSize size;
    b2World* world;
    
    
    CCArray* bgrounds;
    Player* p;
    
    ContactListener contactListenerInstance;
    
    GLESDebugDraw *m_debugDraw;
    
    
    CCSprite *shieldbonus;
    CCSprite *smallbonus;
    CCSprite *gunbonus;
    CCSprite *rotatebonus;
    
    bool nobonus;
    bool newbg;
    
    CCSprite *mainbg;
    CCSprite *secondbg;
    
    CCSprite *latmainbg;
    CCSprite *latsecondbg;
    
    CCSprite* newbground;
    
    
    float speed;
    float bonusSpeed;
    float speedupspeed;
    //GLESDebugDraw *m_debugDraw;
    //CCTextFieldTTF* userfield;
    //CCMenuItemImage *username;
    
    
    float scaleX;
    float scaleY;
    
    int score;
    CCLabelTTF* timerdisplay;
    CCLabelTTF* highsdisplay;
    CCLabelTTF* levelsdisplay;
    
    CCMenuItemImage* dierestart;
    CCMenuItemImage* diemenu;
    CCMenuItemImage* diehighscore;
    
    CCMenuItemImage* pauserestart;
    CCMenuItemImage* pausemenu;
    CCMenuItemImage* pauseresume;
    
    CCMenuItemImage* pause;
    
    CCMenuItemImage* music;
    CCMenuItemImage* sounds;
    
    bool moving;
    
    bool check10;
    bool check100;
    bool check1000;
    bool check10000;
    bool check100000;
    bool check1000000;
    
    float timecheck;
    
    
    CCSprite* tuttouchright;
    CCSprite* tuttouchleft;
    CCSprite* tutavoid;
    CCSprite* tuthelp;
    CCSprite* go;
    
    int tutseq = 0;
    int level = 0;;
    
    CCSprite* hscoreimage;
    CCSprite* levelimage;
    
    CCPoint visibleOrigin;
    CCSize visibleSize;
    
    bool levelcheck;
    
    bool touched;
    //bool musicon;
    //bool soundson;
};




#endif /* defined(__AAHvoidance__MainGame__) */
