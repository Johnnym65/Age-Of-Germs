//
//  ContactListener.cpp
//  MakeALevel
//
//  Created by darren mckeever on 01/11/2012.
//
//

#include "ContactListener.h"
#include "MainGame.h"
#include "ScorePop.h"
#include "SimpleAudioEngine.h"
#include "ScorePopPlate.h"

void ContactListener::BeginContact(b2Contact* contact) {
    
    size = CCDirector::sharedDirector()->getWinSize();
    
    scaleX = size.width/960;
    scaleY = size.height/640;

    
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    
    
    if(fixtureA->IsSensor() && fixtureB -> IsSensor())
    {
        GameObject* fixtureGameObjectA= (GameObject*)fixtureA->GetBody()->GetUserData();
        GameObject* fixtureGameObjectB= (GameObject*)fixtureB->GetBody()->GetUserData();
        
        if(fixtureGameObjectA->getID() == 1 && fixtureGameObjectB->getID() == 4)
        {
            MainGame* m = (MainGame*)fixtureGameObjectB->getParent();
            m->addScore(100);
            
            Square* ss = (Square*)fixtureGameObjectB;
            ss->explode();
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("splat.wav");
            
            
            ScorePop* s = new ScorePop();
            s->retain();
            s->setObjectTexture();
            s->setScaleX(scaleX);
            s->setScaleY(scaleY);
            s->setPosition(ccp(ss->getPositionX(),ss->getPositionY()));
            s->setOriginalPosition(ss->getPosition());
            //s->addBody();
            ss->getParent()->addChild(s,200);
            fixtureGameObjectB->setTag(999);
            fixtureGameObjectA->setTag(999);
            
        }
        if(fixtureGameObjectB->getID() == 1 && fixtureGameObjectA->getID() == 4)
        {
            MainGame* m = (MainGame*)fixtureGameObjectB->getParent();
            m->addScore(100);
            
            Square* ss = (Square*)fixtureGameObjectB;
            ss->explode();
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("splat.wav");
            
            
            ScorePop* s = new ScorePop();
            s->retain();
            s->setObjectTexture();
            s->setScaleX(scaleX);
            s->setScaleY(scaleY);
            s->setPosition(ccp(ss->getPositionX(),ss->getPositionY()));
            s->setOriginalPosition(ss->getPosition());
            //s->addBody();
            ss->getParent()->addChild(s,200);
            fixtureGameObjectB->setTag(999);
            fixtureGameObjectA->setTag(999);
            
        }
    }
    
    
    
    
    if(fixtureA->IsSensor() && !fixtureB->IsSensor()){
        void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        handleSensorContact(fixtureA, static_cast<GameObject*>(bodyBUserData),contact);
    }
    else if(fixtureB->IsSensor() && !fixtureA->IsSensor()){
        void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        handleSensorContact(fixtureB, static_cast<GameObject*>(bodyAUserData),contact);
    }
    else{
        
        void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        if ( bodyAUserData && bodyBUserData ){
            
            handleContact( static_cast<GameObject*>( bodyAUserData ),
                          static_cast<GameObject*>( bodyBUserData ),contact );
            
        }
    }
    
    //CCLog("contact");
}

void ContactListener::EndContact(b2Contact* contact) {
    
    
    contact->SetEnabled(true);
    
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    
    
    
    if(fixtureA->IsSensor() && !fixtureB->IsSensor()){

        
        
        void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        handleEndSensorContact(fixtureA, static_cast<GameObject*>(bodyBUserData));
    }
    else if(fixtureB->IsSensor() && !fixtureA->IsSensor()){
        void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        handleEndSensorContact(fixtureB, static_cast<GameObject*>(bodyAUserData));
    }
    else{
        
        void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        if ( bodyAUserData && bodyBUserData ){
            
            handleEndContact( static_cast<GameObject*>( bodyAUserData ),
                             static_cast<GameObject*>( bodyBUserData ) );
            
        }
    }
    
}

void ContactListener::handleSensorContact(b2Fixture* fixture, GameObject* bodyUserData,b2Contact* contact){
    
    size = CCDirector::sharedDirector()->getWinSize();
    
    scaleX = size.width/960;
    scaleY = size.height/640;
    
    CCSprite* spriteCast=(CCSprite*)fixture->GetBody()->GetUserData();
    GameObject* fixtureGameObject= (GameObject*)fixture->GetBody()->GetUserData();
    
    
    
    if(bodyUserData->getID() == 5 && fixtureGameObject->getID() == 1)
    {
        MainGame* m = (MainGame*)fixtureGameObject->getParent();
        m->addScore(100);
        
        Square* ss = (Square*)fixtureGameObject;
        ss->explode();
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("splat.wav");
        
        
        ScorePop* s = new ScorePop();
        s->retain();
        s->setObjectTexture();
        s->setScaleX(scaleX);
        s->setScaleY(scaleY);
        s->setPosition(ccp(ss->getPositionX(),ss->getPositionY()));
        s->setOriginalPosition(ss->getPosition());
        //s->addBody();
        ss->getParent()->addChild(s,200);
        fixtureGameObject->setTag(999);
    }
    
    if(bodyUserData->getID() == 3 && fixtureGameObject->getID() == 7)
    {
        MainGame* m = (MainGame*)fixtureGameObject->getParent();
        m->addScore(500);
        
        Platelet* ss = (Platelet*)fixtureGameObject;
        ss->setTag(999);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("bonus.wav");
        
        
        ScorePopPlate* s = new ScorePopPlate();
        s->retain();
        s->setObjectTexture();
        s->setScaleX(scaleX);
        s->setScaleY(scaleY);
        s->setPosition(ccp(ss->getPositionX(),ss->getPositionY()));
        s->setOriginalPosition(ss->getPosition());
        //s->addBody();
        ss->getParent()->addChild(s,200);
        fixtureGameObject->setTag(999);
    }
    
    if(bodyUserData->getID() == 3 && fixtureGameObject->getID() == 1)
    {
        MainGame* m = (MainGame*)fixtureGameObject->getParent();
        m->setTouchEnabled(false);
        m->unschedule(schedule_selector(MainGame::timers));
        m->diemenuPopUp();
        
        Player* p = (Player*)bodyUserData;
        p->explode();
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("explosion.wav");
        bodyUserData->setTag(1000);
        
    }
    
    if(bodyUserData->getID() == 3 && fixtureGameObject->getID() == 2)
    {
     
        Bonus* ss = (Bonus*)fixtureGameObject;
        //CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("bonus.wav");
        
        
        ScorePop* s = new ScorePop();
        s->retain();
        s->setObjectTexture();
        s->setScaleX(scaleX);
        s->setScaleY(scaleY);
        s->setPosition(ccp(ss->getPositionX(),ss->getPositionY()));
        s->setOriginalPosition(ss->getPosition());
        //s->addBody();
        ss->getParent()->addChild(s,200);
        
        
        fixtureGameObject->setTag(999);
        
        //CCLog("Bonus!!!");
        Player* p = (Player*)bodyUserData;
        p->randomBonus();
        
        
        
                     
    }
    
    
    
    
}
void ContactListener::handleEndSensorContact(b2Fixture* fixture, GameObject* bodyUserData){
    
    GameObject* fixtureGameObject= (GameObject*)fixture->GetBody()->GetUserData();
    
}


void ContactListener::handleContact( GameObject* bodyAUserData ,GameObject* bodyBUserData,b2Contact* contact){
    
    //CCLog("ccontact");
    
    
    

    
}
void ContactListener::handleEndContact( GameObject* bodyAUserData ,GameObject* bodyBUserData){
    
}

