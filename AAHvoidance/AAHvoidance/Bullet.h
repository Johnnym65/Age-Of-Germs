//
//  Bullet.h
//  AAHvoidance
//
//  Created by Johnny Murphy on 21/12/2012.
//
//

#ifndef __AAHvoidance__Bullet__
#define __AAHvoidance__Bullet__

#include <iostream>
#include "cocos2d.h"

#include "PhysicsObject.h"
//#include "../Utilities/ImageScaler/ImageScaler.h"


using namespace cocos2d;

class Bullet : public PhysicsObject
{
public:
    Bullet();
    Bullet(b2World* world,CCPoint pos,int ID,int rotation);
    virtual ~Bullet(void);
    
    void tick(float dt);
    
    virtual void setObjectTexture();
    
    virtual void addBody();
    
private:
    CCSize size;
    
    float time;
    
    
    
};

#endif /* defined(__AAHvoidance__Bullet__) */
