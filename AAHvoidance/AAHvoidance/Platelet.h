//
//  Platelet.h
//  AAHvoidance
//
//  Created by Johnny Murphy on 03/01/2013.
//
//

#ifndef __AAHvoidance__Platelet__
#define __AAHvoidance__Platelet__

#include <iostream>
#include "cocos2d.h"

#include "PhysicsObject.h"
//#include "../Utilities/ImageScaler/ImageScaler.h"


using namespace cocos2d;

class Platelet : public PhysicsObject
{
public:
    Platelet();
    Platelet(b2World* world,CCPoint pos,int ID,int rotation);
    virtual ~Platelet(void);
    
    void tick(float dt);
    
    virtual void setObjectTexture();
    virtual void addBody();
    void colors();
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
