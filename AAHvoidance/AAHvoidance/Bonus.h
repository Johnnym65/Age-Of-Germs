//
//  Bonus.h
//  AAHvoidance
//
//  Created by Johnny Murphy on 21/12/2012.
//
//

#ifndef __AAHvoidance__Bonus__
#define __AAHvoidance__Bonus__

#include <iostream>
#include "cocos2d.h"

#include "PhysicsObject.h"
//#include "../Utilities/ImageScaler/ImageScaler.h"


using namespace cocos2d;

class Bonus : public PhysicsObject
{
public:
    Bonus();
    Bonus(b2World* world,CCPoint pos,int ID,int rotation);
    virtual ~Bonus(void);
    
    void tick(float dt);
    
    virtual void setObjectTexture();
    //virtual void setObjectTexture();
    /*virtual CCRect rect();*/
    
    bool movingleft;
    bool movingright;
    bool straight;
    
    float scaleX;
    float scaleY;
    
    virtual void addBody();
    
private:
    CCSize size;
    
    
    
};


#endif /* defined(__AAHvoidance__Bonus__) */
