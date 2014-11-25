//
//  ScorePop.cpp
//  AAHvoidance
//
//  Created by Johnny Murphy on 28/12/2012.
//
//

#include "ScorePop.h"
#include <iostream>

#define PTM_RATIO 32

ScorePop::ScorePop(void)
{
    schedule( schedule_selector(ScorePop::tick) );
}
ScorePop::ScorePop(b2World* world,CCPoint pos,int ID,int rotation):PhysicsObject(world,pos,ID,rotation)
{
    
    
    schedule( schedule_selector(ScorePop::tick) );
    time = 0;
}
ScorePop::~ScorePop(void)
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

void ScorePop::tick(float dt)
{
    this->setPositionY(this->getPositionY()+1);
    this->setOpacity(this->getOpacity()-5);
    
    if(this->getOpacity() < 20)
    {
        this->getParent()->removeChild(this);
    }
    
}

void ScorePop::setObjectTexture()
{
    this->texture = CCTextureCache::sharedTextureCache()->addImage("scorepop.png");
    initWithTexture(texture);
}

