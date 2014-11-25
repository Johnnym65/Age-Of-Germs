//
//  ContactListener.h
//  MakeALevel
//
//  Created by darren mckeever on 01/11/2012.
//
//

#ifndef __MakeALevel__ContactListener__
#define __MakeALevel__ContactListener__

#include <iostream>
#include "cocos2d.h"
#include "Box2D.h"

#include "GameObject.h"
#include "PhysicsObject.h"
#include "Player.h"
#include "Platelet.h"

using namespace cocos2d;



class ContactListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact);    
    void EndContact(b2Contact* contact);
    
    void handleSensorContact( b2Fixture* fixture ,GameObject* bodyUserData,b2Contact* contact);
    void handleEndSensorContact( b2Fixture* fixture ,GameObject* bodyUserData);
    
    void handleContact( GameObject* bodyAUserData ,GameObject* bodyBUserData,b2Contact* contact);
    void handleEndContact( GameObject* bodyAUserData ,GameObject* bodyBUserData);
    
    int teleportTouches = 1;
    
    float scaleX;
    float scaleY;
    
    CCSize size;
};

#endif /* defined(__MakeALevel__ContactListener__) */
