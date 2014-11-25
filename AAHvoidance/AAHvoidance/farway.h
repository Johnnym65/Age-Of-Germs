//
//  farway.h
//  AAHvoidance
//
//  Created by Johnny Murphy on 03/01/2013.
//
//

#ifndef __AAHvoidance__farway__
#define __AAHvoidance__farway__

#include <iostream>
#include "cocos2d.h"

#include "PhysicsObject.h"
//#include "../Utilities/ImageScaler/ImageScaler.h"


using namespace cocos2d;

class farway : public PhysicsObject
{
public:
    farway();
    farway(b2World* world,CCPoint pos,int ID,int rotation);
    virtual ~farway(void);
    
    void tick(float dt);
    
    virtual void setObjectTexture();
    virtual void addBody();
    //virtual void setObjectTexture();
    /*virtual CCRect rect();*/
    
    bool movingleft;
    bool movingright;
    bool straight;
    
    
    
    float scaleX;
    float scaleY;
    //int type;
    
    //virtual void addBody();
    
    //int slowdown;
private:
    CCSize size;
    
    
    
    
};

#endif /* defined(__AAHvoidance__Square__) */
