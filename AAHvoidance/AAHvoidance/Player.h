//
//  Player.h
//  AAHvoidance
//
//  Created by Johnny Murphy on 20/12/2012.
//
//

#ifndef __AAHvoidance__Player__
#define __AAHvoidance__Player__

#include <iostream>
#include "cocos2d.h"

#include "PhysicsObject.h"
#include "Bullet.h"
#include "Shield.h"
//#include "MainGame.h"
//#include "../Utilities/ImageScaler/ImageScaler.h"


using namespace cocos2d;

class Player : public PhysicsObject
{
public:
    Player();
    Player(b2World* world,CCPoint pos,int ID,int rotation);
    virtual ~Player(void);
    
    void tick(float dt);
    
    virtual void setObjectTexture();
    
    virtual void addBody();
    
    
    void goNormal();
    
   
    void goVincible();
    
    
    void shootBullets();
    void stopShooting();
    
    
    void speedNormal();
    
    void randomBonus();
    void turnRight();
    void turnLeft();
    void explode();
    
    bool smallbonus;
    bool smallbonusOn;
    bool invinciblebonus;
    bool invinciblebonusOn;
    bool shoot;
    bool shootOn;
    bool slowdown;
    bool slowdownOn;
    
    
    float lookingRight;
    float lookingLeft;
    
    float scaleX;
    float scaleY;
    
    
    
private:
    CCSize size;
    
    Shield* shield;
    //CCSprite* bonus;
    
    CCArray* bullets;
    
    CCAction* straightA;
    CCAction* rightA;
    CCAction* leftA;
    
    
    
    
    
};


#endif /* defined(__AAHvoidance__Player__) */
