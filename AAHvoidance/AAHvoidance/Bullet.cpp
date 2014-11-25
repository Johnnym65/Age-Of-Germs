//
//  Bullet.cpp
//  AAHvoidance
//
//  Created by Johnny Murphy on 21/12/2012.
//
//

#include "Bullet.h"

#include <iostream>

#define PTM_RATIO 32

Bullet::Bullet(void)
{
    
}
Bullet::Bullet(b2World* world,CCPoint pos,int ID,int rotation):PhysicsObject(world,pos,ID,rotation)
{
    //this->addBody();
    
    //not sure why this would cause crash
    //this->autorelease();
    size = CCDirector::sharedDirector()->getWinSize();
    time = 0;
    
    schedule( schedule_selector(Bullet::tick) );
}

Bullet::~Bullet(void)
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

void Bullet::tick(float dt)
{
    
    time += dt;
    
    if(time > 1 || this->getBody()->GetPosition().y > size.height)
    {
        this->setTag(999);
    }
    
}

void Bullet::setObjectTexture()
{
    this->texture = CCTextureCache::sharedTextureCache()->addImage("bullet.png");
    initWithTexture(texture);
    
    
}

void Bullet::addBody()
{
    
	b2BodyDef bodyDef;
	bodyDef.type =b2_dynamicBody;
	bodyDef.position.Set(this->getPositionX()/PTM_RATIO, this->getPositionY()/PTM_RATIO);
	bodyDef.userData = this;
	body = world->CreateBody(&bodyDef);
	
	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
    
    dynamicBox.SetAsBox(((this->getContentSize().width/2))/PTM_RATIO, ((this->getContentSize().height/2))/PTM_RATIO);//These are mid points for our 1m box
    
	
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 5.0f;
	fixtureDef.friction = 1.0f;
    fixtureDef.isSensor = true;
	body->CreateFixture(&fixtureDef);
    
    //this->getBody()->GetFixtureList()->SetFriction(1000.0f);
    
        
}
