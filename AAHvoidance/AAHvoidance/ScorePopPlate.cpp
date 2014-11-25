//
//  ScorePopPlate.cpp
//  AAHvoidance
//
//  Created by Johnny Murphy on 03/01/2013.
//
//

#include "ScorePopPlate.h"
#include <iostream>

#define PTM_RATIO 32

ScorePopPlate::ScorePopPlate(void)
{
    schedule( schedule_selector(ScorePopPlate::tick) );
}
ScorePopPlate::ScorePopPlate(b2World* world,CCPoint pos,int ID,int rotation):PhysicsObject(world,pos,ID,rotation)
{
    
    
    schedule( schedule_selector(ScorePopPlate::tick) );
    time = 0;
}
ScorePopPlate::~ScorePopPlate(void)
{
}
/*
 void Platform::setObjectTexture()
 {
 this->texture = CCTextureCache::sharedTextureCache()->addImage(IDs.find(ID)->second);
 
 initWithTexture(texture);
 }*/

/*
 CCRect Platform::rect()
 {
 CCSize s = getTexture()->getContentSize();
 return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
 }
 */

void ScorePopPlate::tick(float dt)
{
    this->setPositionY(this->getPositionY()+1);
    this->setOpacity(this->getOpacity()-5);
    
    if(this->getOpacity() < 20)
    {
        this->getParent()->removeChild(this);
    }
    
}

void ScorePopPlate::setObjectTexture()
{
    this->texture = CCTextureCache::sharedTextureCache()->addImage("scorepopplat.png");
    initWithTexture(texture);
}

