//
//  ScorePop.h
//  AAHvoidance
//
//  Created by Johnny Murphy on 28/12/2012.
//
//

#ifndef __AAHvoidance__ScorePop__
#define __AAHvoidance__ScorePop__

#include <iostream>
#include "cocos2d.h"

#include "PhysicsObject.h"
//#include "../Utilities/ImageScaler/ImageScaler.h"


using namespace cocos2d;

class ScorePop : public PhysicsObject
{
public:
    ScorePop();
    ScorePop(b2World* world,CCPoint pos,int ID,int rotation);
    virtual ~ScorePop(void);
    
    void tick(float dt);
    
    virtual void setObjectTexture();
    
    
    
private:
    CCSize size;
    
    float time;
    
    
    
};

#endif /* defined(__AAHvoidance__Bullet__) */