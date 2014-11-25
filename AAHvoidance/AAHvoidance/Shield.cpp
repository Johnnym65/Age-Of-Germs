//
//  Shield.cpp
//  AAHvoidance
//
//  Created by Johnny Murphy on 24/12/2012.
//
//

#include "Shield.h"
#include "SimpleAudioEngine.h"

#include <iostream>

#define PTM_RATIO 32

Shield::Shield(void)
{
    
}
Shield::Shield(b2World* world,CCPoint pos,int ID,int rotation):PhysicsObject(world,pos,ID,rotation)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("poweron.wav");
    
    schedule( schedule_selector(Shield::tick) );
    time = 0;
    
    shutdown = false;
    startflicker = false;
    invisible = false;
}

Shield::~Shield(void)
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

void Shield::tick(float dt)
{
    time += dt;
    
    if(time > 9 && time <10 && !shutdown)
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("poweroff.wav");
        shutdown = true;
    }
    
    if(time>10)
    {
        this->setTag(999);
    }
    
    if(time >8 && !startflicker)
    {
        startflicker = true;
        schedule( schedule_selector(Shield::goinvisible), .1 );
    }
    
}

void Shield::setObjectTexture()
{
    this->texture = CCTextureCache::sharedTextureCache()->addImage("blueshield.png");
    initWithTexture(texture);
    
    
}

void Shield::addBody()
{
    
	b2BodyDef bodyDef;
    bodyDef.type =b2_kinematicBody;
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
    //fixtureDef.isSensor = true;
    body->CreateFixture(&fixtureDef);
    
    
    body->SetFixedRotation(false);
    
    
    body->SetAngularVelocity(7);
    //this->getBody()->GetFixtureList()->SetFriction(1000.0f);
    
    
}

void Shield::goinvisible()
{
    if(invisible)
    {
        invisible = false;
        this->setOpacity(0);
    }
    
    else
    {
        invisible = true;
        this->setOpacity(255);
    }
    
    
    
}
