//
//  Square.h
//  AAHvoidance
//
//  Created by Johnny Murphy on 20/12/2012.
//
//

#ifndef __AAHvoidance__Square__
#define __AAHvoidance__Square__


#include <iostream>
#include "cocos2d.h"

#include "PhysicsObject.h"
//#include "../Utilities/ImageScaler/ImageScaler.h"


using namespace cocos2d;

class Square : public PhysicsObject
{
public:
    Square();
    Square(b2World* world,CCPoint pos,int ID,int rotation);
    virtual ~Square(void);
    
     void tick(float dt);
    
    virtual void setObjectTexture();
    //virtual void setObjectTexture();
    /*virtual CCRect rect();*/
    
    bool movingleft;
    bool movingright;
    bool straight;
    
    int type;
    
    virtual void addBody();
    
    int slowdown;
    
    float scaleX;
    float scaleY;
    bool move;
    void explode();
private:
    CCSize size;
    //ccColor3B myColor;
    ccColor4F C;
    
    
    
    
    
};

#endif /* defined(__AAHvoidance__Square__) */
