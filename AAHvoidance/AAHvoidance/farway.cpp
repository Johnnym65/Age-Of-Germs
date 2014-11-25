//
//  farway.cpp
//  AAHvoidance
//
//  Created by Johnny Murphy on 03/01/2013.
//
//

#include "farway.h"

#include <iostream>

#define PTM_RATIO 32
#define DEGTORAD 0.0174532925199432957f
farway::farway(void)
{
    
}
farway::farway(b2World* world,CCPoint pos,int ID,int rotation):PhysicsObject(world,pos,ID,rotation)
{
    //this->addBody();
    
    //not sure why this would cause crash
    //this->autorelease();
    size = CCDirector::sharedDirector()->getWinSize();
    movingleft = false;
    movingright = false;
    straight = true;
    //this->initwithc
    //type = 0;
    
    //slowdown = 1;
    
    
    schedule( schedule_selector(farway::tick) );
}

farway::~farway(void)
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

void farway::tick(float dt)
{
    if(straight)
    {
        CCPoint p= ccpNormalize(ccpSub(ccp(this->getPosition().x, this->getPosition().y - size.height/4),this->getPosition()));
        p.x=p.x*(50);
        p.y=p.y*(50);
        body->SetAngularVelocity(body->GetAngularVelocity());
        this->getBody()->SetLinearVelocity(b2Vec2(p.x/PTM_RATIO,p.y/PTM_RATIO));
    }
    
    else if(movingleft)
    {
        CCPoint p= ccpNormalize(ccpSub(ccp(this->getPosition().x-(size.width*1.5), this->getPosition().y - size.height/4),this->getPosition()));
        p.x=p.x*(50);
        p.y=p.y*(50);
        body->SetAngularVelocity(body->GetAngularVelocity());
        this->getBody()->SetLinearVelocity(b2Vec2(p.x/PTM_RATIO,p.y/PTM_RATIO));
    }
    
    else if(movingright)
    {
        CCPoint p= ccpNormalize(ccpSub(ccp(this->getPosition().x+(size.width*1.5), this->getPosition().y - size.height/4),this->getPosition()));
        p.x=p.x*(50);
        p.y=p.y*(50);
        body->SetAngularVelocity(body->GetAngularVelocity());
        this->getBody()->SetLinearVelocity(b2Vec2(p.x/PTM_RATIO,p.y/PTM_RATIO));
    }
    
    if(this->getBody()->GetPosition().y*PTM_RATIO < (-600) )
    {
        this->setTag(999);
    }
    
    
}

void farway::setObjectTexture()
{
    
    int random_integer = rand() % 3  + 1;
    
    if(random_integer == 1)
        this->texture = CCTextureCache::sharedTextureCache()->addImage("farway1.png");
    if(random_integer == 2)
        this->texture = CCTextureCache::sharedTextureCache()->addImage("farway2.png");
    if(random_integer == 3)
        this->texture = CCTextureCache::sharedTextureCache()->addImage("farway3.png");

    
    initWithTexture(texture);
    
    
}

void farway::addBody()
{
    
	
	
	// Define another box shape for our dynamic body.
	
    
    
    
    b2BodyDef bodyDef;
    bodyDef.type =b2_dynamicBody;
    bodyDef.position.Set(this->getPositionX()/PTM_RATIO, this->getPositionY()/PTM_RATIO);
    bodyDef.userData = this;
    body = world->CreateBody(&bodyDef);
    
    
    b2CircleShape dynamicB;
    dynamicB.m_radius=((this->getContentSize().height/2)*this->getScaleY())/PTM_RATIO;
    
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicB;
    fixtureDef.density = 5.0f;
    fixtureDef.friction = 1.0f;
    fixtureDef.isSensor = true;
    body->CreateFixture(&fixtureDef);
    
    
	
	
    
    //this->getBody()->GetFixtureList()->SetFriction(1000.0f);
    
    CCPoint p= ccpNormalize(ccpSub(ccp(this->getPosition().x, this->getPosition().y - size.height/4),this->getPosition()));
    p.x=p.x*50;
    p.y=p.y*50;
    this->getBody()->SetLinearVelocity(b2Vec2(p.x/PTM_RATIO,p.y/PTM_RATIO));
    
    
    
    // return body;
    
}