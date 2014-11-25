//
//  ScorePopPlate.h
//  AAHvoidance
//
//  Created by Johnny Murphy on 03/01/2013.
//
//

#ifndef __AAHvoidance__ScorePopPlate__
#define __AAHvoidance__ScorePopPlate__

#include <iostream>
#include "cocos2d.h"

#include "PhysicsObject.h"
//#include "../Utilities/ImageScaler/ImageScaler.h"


using namespace cocos2d;

class ScorePopPlate : public PhysicsObject
{
public:
    ScorePopPlate();
    ScorePopPlate(b2World* world,CCPoint pos,int ID,int rotation);
    virtual ~ScorePopPlate(void);
    
    void tick(float dt);
    
    virtual void setObjectTexture();
    
    
    
private:
    CCSize size;
    
    float time;
    
    
    
};

#endif /* defined(__AAHvoidance__Bullet__) */
