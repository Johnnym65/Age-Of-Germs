//
//  MainMenu.h
//  AAHvoidance
//
//  Created by Johnny Murphy on 28/12/2012.
//
//

#ifndef __AAHvoidance__MainMenu__
#define __AAHvoidance__MainMenu__

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

using namespace cocos2d;

class MainMenu : public cocos2d::CCLayer
{
public:
    ~MainMenu();
    MainMenu();
    
  
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
    
    //void draw();
    void tick(float dt);
    
 
    
    
    void playChosen();
    void viewHighScores();
    void moregames();
    
    string convertIntToString(int number);
    //void speedUp();
    
    bool mright;
    bool mleft;
    CCArray* shapes;
    
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
    //GLESDebugDraw *m_debugDraw;
    //CCTextFieldTTF* userfield;
    //CCMenuItemImage *username;
    
    
    float scaleX;
    float scaleY;
    
    CCPoint visibleOrigin;
    CCSize visibleSize;
};




#endif /* defined(__AAHvoidance__MainGame__) */
