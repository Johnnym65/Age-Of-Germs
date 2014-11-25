//
//  Blood.h
//  AAHvoidance
//
//  Created by Johnny Murphy on 24/12/2012.
//
//

#ifndef __AAHvoidance__Blood__
#define __AAHvoidance__Blood__

#include <iostream>
#include "cocos2d.h"

#include "PhysicsObject.h"
//#include "../Utilities/ImageScaler/ImageScaler.h"


using namespace cocos2d;

class Blood : public PhysicsObject
{
public:
    Blood();
    Blood(b2World* world,CCPoint pos,int ID,int rotation);
    virtual ~Blood(void);
    
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

