//
//  PhysicsObject.h
//  MakeALevel
//
//  Created by darren mckeever on 11/10/2012.
//
//

#ifndef __MakeALevel__PhysicsObject__
#define __MakeALevel__PhysicsObject__

#include <iostream>
#include "cocos2d.h"
#include "Box2D.h"

//#include "../Utilities/ImageScaler/ImageScaler.h"
#include "GameObject.h"

using namespace cocos2d;

//USING_NS_CC;

class PhysicsObject : public GameObject
{
    
public:
    PhysicsObject(void);
    PhysicsObject(b2World* world,CCPoint pos,int ID,int rotation);
    virtual ~PhysicsObject(void);
    
    virtual void addBody();
    
    void setPhysicsWorld(b2World* world);
    b2World* getPhysicsWorld();
    
    b2Body* getBody();
    virtual void inWater(bool b);
    virtual void boosting(bool b);
     int getObjectType();
    
protected:
    b2Body *body;
    b2World* world;
};



#endif /* defined(__MakeALevel__PhysicsObject__) */
