//
//  Square.cpp
//  AAHvoidance
//
//  Created by Johnny Murphy on 20/12/2012.
//
//

#include "Square.h"
#include <iostream>

#define PTM_RATIO 32
#define DEGTORAD 0.0174532925199432957f
Square::Square(void)
{
    
}
Square::Square(b2World* world,CCPoint pos,int ID,int rotation):PhysicsObject(world,pos,ID,rotation)
{
    //this->addBody();
    
    //not sure why this would cause crash
    //this->autorelease();
    size = CCDirector::sharedDirector()->getWinSize();
    
    scaleX = size.width/960;
    scaleY = size.height/640;
    movingleft = false;
    movingright = false;
    straight = true;
    //this->initwithc
    type = 0;
    
    slowdown = 1;
    
    
    schedule( schedule_selector(Square::tick) );
}

Square::~Square(void)
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

void Square::tick(float dt)
{
    if(straight)
    {
        CCPoint p= ccpNormalize(ccpSub(ccp(this->getPosition().x, this->getPosition().y - size.height * scaleY),this->getPosition()));
        p.x=p.x*(300 * scaleY);
        p.y=p.y*(300 * scaleY) ;
        body->SetAngularVelocity(body->GetAngularVelocity()*slowdown);
        this->getBody()->SetLinearVelocity(b2Vec2(p.x/PTM_RATIO,p.y/PTM_RATIO));
    }
    
    else if(movingleft)
    {
        CCPoint p= ccpNormalize(ccpSub(ccp(this->getPosition().x-(size.width*1.5), this->getPosition().y - size.height * scaleY),this->getPosition()));
        p.x=p.x*(300 * scaleY);
        p.y=p.y*(300 * scaleY);
        body->SetAngularVelocity(body->GetAngularVelocity()*slowdown);
        this->getBody()->SetLinearVelocity(b2Vec2(p.x/PTM_RATIO,p.y/PTM_RATIO));
    }
    
    else if(movingright)
    {
        CCPoint p= ccpNormalize(ccpSub(ccp(this->getPosition().x+(size.width*1.5), this->getPosition().y - size.height * scaleY),this->getPosition()));
        p.x=p.x*(300 * scaleY);
        p.y=p.y*(300 * scaleY);
        body->SetAngularVelocity(body->GetAngularVelocity()*slowdown);
        this->getBody()->SetLinearVelocity(b2Vec2(p.x/PTM_RATIO,p.y/PTM_RATIO));
    }
    
    if(this->getBody()->GetPosition().y*PTM_RATIO < (-400) )
    {
        this->setTag(999);
    }
    
    
}

void Square::setObjectTexture()
{
    type = rand() % 6  + 1;
    
    if(type == 1)
        this->texture = CCTextureCache::sharedTextureCache()->addImage("square.png");
    if(type == 2)
        this->texture = CCTextureCache::sharedTextureCache()->addImage("circle.png");
    if(type == 3)
        this->texture = CCTextureCache::sharedTextureCache()->addImage("rect.png");
    if(type == 4)
        this->texture = CCTextureCache::sharedTextureCache()->addImage("star.png");
    if(type == 5)
        this->texture = CCTextureCache::sharedTextureCache()->addImage("triangle.png");
    if(type == 6)
        this->texture = CCTextureCache::sharedTextureCache()->addImage("cross.png");
    
    
    initWithTexture(texture);
    
    int r1 = rand() % 255  + 1;
    int r2 = rand() % 255  + 1;
    int r3 = rand() % 255  + 1;
    
    ccColor3B myColor={r1,r2,r3};
    
    //myColor = myColor1;
    ccColor4F baha = {r1,r2,r3,r2};
    
    C = baha;
    this->setColor(myColor);
    
   
}

void Square::addBody()
{
    
	
	
	// Define another box shape for our dynamic body.
	
    
    
    if(type == 1)
    {
        
        b2BodyDef bodyDef;
        bodyDef.type =b2_dynamicBody;
        bodyDef.position.Set(this->getPositionX()/PTM_RATIO, this->getPositionY()/PTM_RATIO);
        bodyDef.userData = this;
        body = world->CreateBody(&bodyDef);
        
        
    b2PolygonShape dynamicB;    
    dynamicB.SetAsBox(((this->getContentSize().width/4)*this->getScaleY())/PTM_RATIO, ((this->getContentSize().height/4)*this->getScaleY())/PTM_RATIO);//These are mid points for our 1m box
        
        
        
        
        // Define the dynamic body fixture.
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicB;
        fixtureDef.density = 5.0f;
        fixtureDef.friction = 1.0f;
        fixtureDef.isSensor = true;
        body->CreateFixture(&fixtureDef);
    }
    
    if(type == 3)
    {
        b2BodyDef bodyDef;
        bodyDef.type =b2_dynamicBody;
        bodyDef.position.Set(this->getPositionX()/PTM_RATIO, this->getPositionY()/PTM_RATIO);
        bodyDef.userData = this;
        body = world->CreateBody(&bodyDef);
        
        
        b2PolygonShape dynamicB;
        dynamicB.SetAsBox(((this->getContentSize().width/2.5)*this->getScaleY())/PTM_RATIO, ((this->getContentSize().height/3)*this->getScaleY())/PTM_RATIO);//These are mid points for our 1m box
        
        
        
        
        // Define the dynamic body fixture.
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicB;
        fixtureDef.density = 5.0f;
        fixtureDef.friction = 1.0f;
        fixtureDef.isSensor = true;
        body->CreateFixture(&fixtureDef);
    }
    
    if(type == 2 || type == 4)
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
    }
    
    if(type == 5)
    {
        b2BodyDef bodyDef;
        bodyDef.type =b2_dynamicBody;
        bodyDef.position.Set(this->getPositionX()/PTM_RATIO, this->getPositionY()/PTM_RATIO);
        bodyDef.userData = this;
        body = world->CreateBody(&bodyDef);
        
        
        
        b2Vec2 vertices[3];
        
            
        vertices[0].Set((-1.5f)*this->getScaleY(), -1.5f*this->getScaleY());
        vertices[1].Set(1.5f*this->getScaleY(), -1.5f*this->getScaleY());
        vertices[2].Set(0.1f*this->getScaleY(), 1.5f*this->getScaleY());
        
        b2PolygonShape shape;
        shape.Set(vertices, 3);
        
        // dynamicBox.SetAsBox(((this->getContentSize().width/2)*this->getScaleX())/PTM_RATIO, ((this->getContentSize().height/2)*this->getScaleY())/PTM_RATIO);//These are mid points for our 1m box
        
        
        // Define the dynamic body fixture.
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.1f;
        fixtureDef.isSensor = 0.1f;
        body->CreateFixture(&fixtureDef);
        
        body->SetTransform(body->GetPosition(), -(this->getRotationSetting())*DEGTORAD);
    }
    
    if(type ==6)
    {
        b2BodyDef bodyDef;
        bodyDef.type =b2_dynamicBody;
        bodyDef.position.Set(this->getPositionX()/PTM_RATIO, this->getPositionY()/PTM_RATIO);
        bodyDef.userData = this;
        body = world->CreateBody(&bodyDef);
        
        
        b2PolygonShape dynamicB;
        dynamicB.SetAsBox(((this->getContentSize().width/3)*this->getScaleY())/PTM_RATIO, ((this->getContentSize().height/22)*this->getScaleY())/PTM_RATIO, b2Vec2(.1,0), 0);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicB;
        fixtureDef.density = 5.0f;
        fixtureDef.friction = 1.0f;
        fixtureDef.isSensor = true;
        body->CreateFixture(&fixtureDef);
        
        
        b2PolygonShape dynamicB2;
        dynamicB2.SetAsBox(((this->getContentSize().width/3)*this->getScaleY())/PTM_RATIO, ((this->getContentSize().height/22)*this->getScaleY())/PTM_RATIO, b2Vec2(.1,0), 90*DEGTORAD);
        
        b2FixtureDef fixtureDef2;
        fixtureDef2.shape = &dynamicB2;
        fixtureDef2.density = 5.0f;
        fixtureDef2.friction = 1.0f;
        fixtureDef2.isSensor = true;
        body->CreateFixture(&fixtureDef2);
    }
    
    
	
	
    
    //this->getBody()->GetFixtureList()->SetFriction(1000.0f);
    
    //int r2 = rand() % 400  + 200;
    
    CCPoint p= ccpNormalize(ccpSub(ccp(this->getPosition().x, this->getPosition().y - size.height * scaleY),this->getPosition()));
    p.x=p.x*(300);
    p.y=p.y*(300);
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

void Square::explode()
{
    //CCLog("Explode");
    /*
    CCParticleSystemQuad *glass=CCParticleSystemQuad::create("glass.plist");
    glass->setTexture(this->texture);
    glass->retain();
    glass->setStartColor(C);
    glass->setEndColor(C);
    glass->setStartSize((glass->getStartSize()*scaleX)/2);
    glass->setEndSize((glass->getEndSize()*scaleY)/2);
    glass->setPositionX(this->getBody()->GetPosition().x*PTM_RATIO);
    glass->setPositionY(this->getBody()->GetPosition().y*PTM_RATIO);
    glass->autorelease();
    this->getParent()->addChild(glass,200);
    */
   // glass->run
}
