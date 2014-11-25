//
//  PhysicsObject.cpp
//  MakeALevel
//
//  Created by darren mckeever on 11/10/2012.
//
//


#include "PhysicsObject.h"

#define PTM_RATIO 32

PhysicsObject::PhysicsObject(void)
{
    
}
PhysicsObject::PhysicsObject(b2World* world,CCPoint pos,int ID,int rotation):GameObject(pos,ID,rotation)
{
   this->setPhysicsWorld(world);
    //this->addBody();
    this->autorelease();
    this->body=NULL;
}

PhysicsObject::~PhysicsObject(void)
{
}


void PhysicsObject::setPhysicsWorld(b2World* world){
    this->world=world;
    
}
b2World* PhysicsObject::getPhysicsWorld(){
    return this->world;
}

void PhysicsObject::addBody()
{
    
	b2BodyDef bodyDef;
	bodyDef.type =b2_dynamicBody; //b2_staticBody;
	bodyDef.position.Set(this->getPositionX()/PTM_RATIO, this->getPositionY()/PTM_RATIO);
	bodyDef.userData = this;
    bodyDef.fixedRotation=true;
	body = world->CreateBody(&bodyDef);
	
	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
    
    dynamicBox.SetAsBox(((this->getContentSize().width/2))/PTM_RATIO, ((this->getContentSize().height/2))/PTM_RATIO);//These are mid points for our 1m box
    
	
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
    
    // return body;
    
}

b2Body* PhysicsObject::getBody(){
    
    return body;
}

void PhysicsObject::inWater(bool b){
    if(b==true){
        this->body->SetGravityScale(-1.0);
        this->body->SetLinearDamping(0.2);
    }
    else{
        this->body->SetGravityScale(1);
        this->body->SetLinearDamping(1);
    }
    
}

void PhysicsObject::boosting(bool b)
{
    
    
    if(b==true){
        //this->body->ApplyLinearImpulse(b2Vec2(0,10), b2Vec2(0,0));
        //this->body->SetLinearDamping(0.2);
        
        this->body->SetGravityScale(-3.0);
        this->body->SetLinearDamping(0.2);
    }
    else{
        this->body->SetGravityScale(1);
        this->body->SetLinearDamping(1);
    }
}


int PhysicsObject::getObjectType(){
    return 2;
}

