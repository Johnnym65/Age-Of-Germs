//
//  Shield.h
//  AAHvoidance
//
//  Created by Johnny Murphy on 24/12/2012.
//
//

#ifndef __AAHvoidance__Shield__
#define __AAHvoidance__Shield__

#include <iostream>
#include "cocos2d.h"

#include "PhysicsObject.h"
//#include "../Utilities/ImageScaler/ImageScaler.h"


using namespace cocos2d;

class Shield : public PhysicsObject
{
public:
    Shield();
    Shield(b2World* world,CCPoint pos,int ID,int rotation);
    virtual ~Shield(void);
    
    void tick(float dt);
    
    virtual void setObjectTexture();
    
    virtual void addBody();
    
    void goinvisible();
    //void govisible();
    
private:
    CCSize size;
    
    float time;
    bool shutdown;
    bool startflicker;
    
    bool invisible;
    
    
};

#endif /* defined(__AAHvoidance__Bullet__) */
