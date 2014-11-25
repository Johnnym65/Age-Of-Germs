//
//  Platelet.cpp
//  AAHvoidance
//
//  Created by Johnny Murphy on 03/01/2013.
//
//

#include "Platelet.h"

#include <iostream>

#define PTM_RATIO 32
#define DEGTORAD 0.0174532925199432957f
Platelet::Platelet(void)
{
    
}
Platelet::Platelet(b2World* world,CCPoint pos,int ID,int rotation):PhysicsObject(world,pos,ID,rotation)
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
    
    
    schedule( schedule_selector(Platelet::tick) );
    schedule( schedule_selector(Platelet::colors),.3 );
}

Platelet::~Platelet(void)
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

void Platelet::tick(float dt)
{
    if(straight)
    {
        CCPoint p= ccpNormalize(ccpSub(ccp(this->getPosition().x, this->getPosition().y - size.height),this->getPosition()));
        p.x=p.x*(300);
        p.y=p.y*(300);
        body->SetAngularVelocity(body->GetAngularVelocity());
        this->getBody()->SetLinearVelocity(b2Vec2(p.x/PTM_RATIO,p.y/PTM_RATIO));
    }
    
    else if(movingleft)
    {
        CCPoint p= ccpNormalize(ccpSub(ccp(this->getPosition().x-(size.width*1.5), this->getPosition().y - size.height),this->getPosition()));
        p.x=p.x*(300);
        p.y=p.y*(300);
        body->SetAngularVelocity(body->GetAngularVelocity());
        this->getBody()->SetLinearVelocity(b2Vec2(p.x/PTM_RATIO,p.y/PTM_RATIO));
    }
    
    else if(movingright)
    {
        CCPoint p= ccpNormalize(ccpSub(ccp(this->getPosition().x+(size.width*1.5), this->getPosition().y - size.height),this->getPosition()));
        p.x=p.x*(300);
        p.y=p.y*(300);
        body->SetAngularVelocity(body->GetAngularVelocity());
        this->getBody()->SetLinearVelocity(b2Vec2(p.x/PTM_RATIO,p.y/PTM_RATIO));
    }
    
    if(this->getBody()->GetPosition().y*PTM_RATIO < (-200) )
    {
        this->setTag(999);
    }
    
    
}

void Platelet::setObjectTexture()
{
    this->texture = CCTextureCache::sharedTextureCache()->addImage("platelet.png");
    
    initWithTexture(texture);
    
    
}

void Platelet::addBody()
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
    
    CCPoint p= ccpNormalize(ccpSub(ccp(this->getPosition().x, this->getPosition().y - size.height),this->getPosition()));
    p.x=p.x*300;
    p.y=p.y*300;
    this->getBody()->SetLinearVelocity(b2Vec2(p.x/PTM_RATIO,p.y/PTM_RATIO));
    
    int random_integer = rand() % 10  + 1;
    
    if(random_integer >5)
    {
        random_integer-=5;
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


void Platelet::colors()
{
    
    int r1 = rand() % 255  + 1;
    int r2 = rand() % 255  + 1;
    int r3 = rand() % 255  + 1;
    
    ccColor3B myColor={r1,r2,r3};
    this->setColor(myColor);

    
    
}


