//
//  Bonus.cpp
//  AAHvoidance
//
//  Created by Johnny Murphy on 21/12/2012.
//
//

#include "Bonus.h"
#include <iostream>

#define PTM_RATIO 32

Bonus::Bonus(void)
{
    
}
Bonus::Bonus(b2World* world,CCPoint pos,int ID,int rotation):PhysicsObject(world,pos,ID,rotation)
{
    //this->addBody();
    
    //not sure why this would cause crash
    //this->autorelease();
    size = CCDirector::sharedDirector()->getWinSize();
    movingleft = false;
    movingright = false;
    straight = true;
    //this->initwithc
    
    
    schedule( schedule_selector(Bonus::tick) );
}

Bonus::~Bonus(void)
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

void Bonus::tick(float dt)
{
    if(straight)
    {
        CCPoint p= ccpNormalize(ccpSub(ccp(this->getPosition().x, this->getPosition().y - size.height),this->getPosition()));
        p.x=p.x*300;
        p.y=p.y*300;
        this->getBody()->SetLinearVelocity(b2Vec2(p.x/PTM_RATIO,p.y/PTM_RATIO));
    }
    
    else if(movingleft)
    {
        CCPoint p= ccpNormalize(ccpSub(ccp(this->getPosition().x-(size.width*1.5), this->getPosition().y - size.height),this->getPosition()));
        p.x=p.x*300;
        p.y=p.y*300;
        this->getBody()->SetLinearVelocity(b2Vec2(p.x/PTM_RATIO,p.y/PTM_RATIO));
    }
    
    else if(movingright)
    {
        CCPoint p= ccpNormalize(ccpSub(ccp(this->getPosition().x+(size.width*1.5), this->getPosition().y - size.height),this->getPosition()));
        p.x=p.x*300;
        p.y=p.y*300;
        this->getBody()->SetLinearVelocity(b2Vec2(p.x/PTM_RATIO,p.y/PTM_RATIO));
    }
    
    if(this->getPosition().y*PTM_RATIO < (-200) )
    {
        this->setTag(999);
    }
    
    
}

void Bonus::setObjectTexture()
{
    this->texture = CCTextureCache::sharedTextureCache()->addImage("bonus.png");
    initWithTexture(texture);
    
    
}

void Bonus::addBody()
{
    
	b2BodyDef bodyDef;
    bodyDef.type =b2_dynamicBody;
    bodyDef.position.Set(this->getPositionX()/PTM_RATIO, this->getPositionY()/PTM_RATIO);
    bodyDef.userData = this;
    body = world->CreateBody(&bodyDef);
    
    
    b2CircleShape dynamicB;
    dynamicB.m_radius=((this->getContentSize().height/3)*this->getScaleY())/PTM_RATIO;
    
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicB;
    fixtureDef.density = 5.0f;
    fixtureDef.friction = 1.0f;
    fixtureDef.isSensor = true;
    body->CreateFixture(&fixtureDef);
    
    //this->getBody()->GetFixtureList()->SetFriction(1000.0f);
    
    CCPoint p= ccpNormalize(ccpSub(ccp(this->getPosition().x, this->getPosition().y - size.height),this->getPosition()));
    p.x=p.x*300;
    p.y=p.y*300;
    this->getBody()->SetLinearVelocity(b2Vec2(p.x/PTM_RATIO,p.y/PTM_RATIO));
    
    int random_integer = rand() % 6  + 1;
    
    if(random_integer >3)
    {
        random_integer-=3;
    }
    else
    {
        random_integer*= -1;
    }
    
    body->SetFixedRotation(false);
    
    
    body->SetAngularVelocity(random_integer);
    
    std::string s;
    std::stringstream out;
    out << random_integer;
    s = out.str();
    
    CCLog(s.c_str());
    
    // return body;
    
}
