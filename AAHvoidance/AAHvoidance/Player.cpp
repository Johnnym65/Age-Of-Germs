//
//  Player.cpp
//  AAHvoidance
//
//  Created by Johnny Murphy on 20/12/2012.
//
//

#include "Player.h"
#include "SimpleAudioEngine.h"
#include <iostream>

#define PTM_RATIO 32

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

Player::Player(void)
{
    
}
Player::Player(b2World* world,CCPoint pos,int ID,int rotation):PhysicsObject(world,pos,ID,rotation)
{
    //this->addBody();
    
    //not sure why this would cause crash
    //this->autorelease();
    size = CCDirector::sharedDirector()->getWinSize();
    
    scaleX = size.width/960;
    scaleY = size.height/640;
        //this->initwithc
    smallbonus = false;
    invinciblebonus = false;
    shoot = false;
    slowdown = false;
    
    smallbonusOn = false;
    invinciblebonusOn = false;
    shootOn = false;
    slowdownOn = false;
    
    bullets = new CCArray();
   
    lookingLeft = false;
    lookingRight = false;
    
    schedule( schedule_selector(Player::tick) );
    
    
    
}

Player::~Player(void)
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

void Player::tick(float dt)
{
    
    
    if(smallbonus)
    {
        smallbonusOn = true;
        smallbonus = false;
        
        this->setScaleX(this->getScaleX()*.3);
        this->setScaleY(this->getScaleY()*.3);
        this->getBody()->DestroyFixture(this->getBody()->GetFixtureList());
        
        
        b2PolygonShape dynamicBox;
        
        dynamicBox.SetAsBox(((this->getContentSize().width/3)*this->getScaleY())/PTM_RATIO, ((this->getContentSize().height/3)*this->getScaleY())/PTM_RATIO);//These are mid points for our 1m box
        
        
        // Define the dynamic body fixture.
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 5.0f;
        fixtureDef.friction = 1.0f;
        body->CreateFixture(&fixtureDef);
        
        this->runAction(CCSequence::create(CCDelayTime::create(10),CCCallFunc::create(this,callfunc_selector(Player::goNormal)),NULL));
    }
    
    else if(invinciblebonus)
    {
        invinciblebonusOn =true;
        invinciblebonus = false;
    
        //this->getBody()->DestroyFixture(this->getBody()->GetFixtureList());
        
        //this->setOpacity(50);
        
        
        shield = new Shield(world,ccp(this->getPositionX(),this->getPositionY()),5,0);
        shield->retain();
        shield->setObjectTexture();
        shield->setScaleX(scaleX);
        shield->setScaleY(scaleX);
        shield->setPosition(shield->getPosition());
        shield->setOriginalPosition(shield->getPosition());
        shield->addBody();
        //shield->getBody()->SetLinearVelocity(b2Vec2(0,50));
        
        this->getParent()->addChild(shield,3);
        
        this->runAction(CCSequence::create(CCDelayTime::create(10),CCCallFunc::create(this,callfunc_selector(Player::goVincible)),NULL));
    }
    
    else if(shoot)
    {
        shootOn = true;
        shoot = false;
        
        
        schedule( schedule_selector(Player::shootBullets), .2 );
        
        this->runAction(CCSequence::create(CCDelayTime::create(10 ),CCCallFunc::create(this,callfunc_selector(Player::stopShooting)),NULL));
    }
    
    else if(slowdown)
    {
        slowdown = false;
        slowdownOn = true;
        this->runAction(CCSequence::create(CCDelayTime::create(10),CCCallFunc::create(this,callfunc_selector(Player::speedNormal)),NULL));
    }
    
    
    
    
}

void Player::setObjectTexture()
{
    /*
    if(leftA!=NULL)
        this->stopAction(leftA);
    if(rightA!=NULL)
        this->stopAction(rightA);
    */
    
    //this->texture = CCTextureCache::sharedTextureCache()->addImage(IDs.find(ID)->second);
    
    this->stopActionByTag(50);
    
    //load plist and it will load in the png with the same name
    //the frames will be stored in the CCSpriteFrameCache so you can get the frames at you leisure
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ships.plist");
    
    
    
    CCArray* walkAnimFrames = new CCArray();
    
    
    for(int i = 1; i <4; i++) {
        std::string s;
        std::stringstream out;
        out << i;
        s = out.str();
        
        string test2="ship"+s+".png";
        
        walkAnimFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( test2.c_str() ));
        
    }
    
    CCAnimation* walkAnim = CCAnimation::createWithSpriteFrames(walkAnimFrames);
    walkAnim->setDelayPerUnit(0.03f);
    
    straightA =CCRepeatForever::create(CCAnimate::create(walkAnim));
    straightA->setTag(50);
    this->runAction(straightA);
    
    CCSpriteFrame* pFrame;
    
    //tries to get the frame
    pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ship1.png");
    
    initWithSpriteFrame(pFrame);
    //CCLOG("ROTATION SAW:%d",rotation);
    //this->setRotation(rotation);
    //this->setRotation(this->getRotation()+ 90)
    
    
    
    
    
/*
    
    this->texture = CCTextureCache::sharedTextureCache()->addImage("player.png");
    initWithTexture(texture);
 */   
    

}

void Player::addBody()
{
    
	b2BodyDef bodyDef;
	bodyDef.type =b2_staticBody;
	bodyDef.position.Set(this->getPositionX()/PTM_RATIO, this->getPositionY()/PTM_RATIO);
	bodyDef.userData = this;
	body = world->CreateBody(&bodyDef);
	
	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
    
    dynamicBox.SetAsBox(((this->getContentSize().width/3)*this->getScaleY())/PTM_RATIO, ((this->getContentSize().height/3)*this->getScaleY())/PTM_RATIO);//These are mid points for our 1m box
    
	
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 5.0f;
	fixtureDef.friction = 1.0f;
	body->CreateFixture(&fixtureDef);
    
   
}



void Player::goNormal()
{
    smallbonusOn = false;
    this->setScaleX(scaleX);
    this->setScaleY(scaleY);
    this->getBody()->DestroyFixture(this->getBody()->GetFixtureList());

	
	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
    
    dynamicBox.SetAsBox(((this->getContentSize().width/3)*this->getScaleY())/PTM_RATIO, ((this->getContentSize().height/3)*this->getScaleY())/PTM_RATIO);//These are mid points for our 1m box
    
	
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 5.0f;
	fixtureDef.friction = 1.0f;
	body->CreateFixture(&fixtureDef);
    
    smallbonus = false;
}



void Player::goVincible()
{
    invinciblebonusOn =false;
    b2PolygonShape dynamicBox;
    
    /*
    dynamicBox.SetAsBox(((this->getContentSize().width/2)*this->getScale())/PTM_RATIO, ((this->getContentSize().height/2)*this->getScale())/PTM_RATIO);//These are mid points for our 1m box
    
    
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 5.0f;
    fixtureDef.friction = 1.0f;
    body->CreateFixture(&fixtureDef);
    
    this->setOpacity(255);
    */
    
    //this->getParent()->removeChild(shield);
    invinciblebonus = false;
    
}



void Player::shootBullets()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("laser.wav");
    
    if(lookingLeft)
    {
    
        Bullet* bullet = new Bullet(world,ccp(this->getPositionX()+(40*scaleX),this->getPositionY()-(3*scaleY)),4,0);
        bullet->retain();
        bullet->setObjectTexture();
        bullet->setPosition(bullet->getPosition());
        bullet->setOriginalPosition(bullet->getPosition());
        bullet->addBody();
        bullet->getBody()->SetLinearVelocity(b2Vec2(-50*scaleX,50*scaleY));
        bullet->getBody()->SetTransform(bullet->getBody()->GetPosition(), 45*DEGTORAD);
        bullet->setScaleX(scaleX);
        bullet->setScaleY(scaleY);
        this->getParent()->addChild(bullet,2);
        
        
        
        Bullet* bullet2 = new Bullet(world,ccp(this->getPositionX()+(2*scaleX),this->getPositionY()-(35*scaleY)),4,0);
        bullet2->retain();
        bullet2->setObjectTexture();
        bullet2->setPosition(bullet2->getPosition());
        bullet2->setOriginalPosition(bullet2->getPosition());
        bullet2->addBody();
        bullet2->getBody()->SetLinearVelocity(b2Vec2(-50*scaleX,50*scaleY));
        bullet2->getBody()->SetTransform(bullet2->getBody()->GetPosition(), 45*DEGTORAD);
        bullet2->setScaleX(scaleX);
        bullet2->setScaleY(scaleY);
        this->getParent()->addChild(bullet2,2);
        
    }
    
    else if(lookingRight)
    {
        
        Bullet* bullet = new Bullet(world,ccp(this->getPositionX()-(40*scaleX),this->getPositionY()-(3*scaleY)),4,0);
        bullet->retain();
        bullet->setObjectTexture();
        bullet->setPosition(bullet->getPosition());
        bullet->setOriginalPosition(bullet->getPosition());
        bullet->addBody();
        bullet->getBody()->SetLinearVelocity(b2Vec2(50*scaleX,50*scaleY));
        bullet->getBody()->SetTransform(bullet->getBody()->GetPosition(), -45*DEGTORAD);
        bullet->setScaleX(scaleX);
        bullet->setScaleY(scaleY);
        this->getParent()->addChild(bullet,2);
        
        
        
        Bullet* bullet2 = new Bullet(world,ccp(this->getPositionX()-(2*scaleX),this->getPositionY()-(35*scaleY)),4,0);
        bullet2->retain();
        bullet2->setObjectTexture();
        bullet2->setPosition(bullet2->getPosition());
        bullet2->setOriginalPosition(bullet2->getPosition());
        bullet2->addBody();
        bullet2->getBody()->SetLinearVelocity(b2Vec2(50*scaleX,50*scaleY));
        bullet2->getBody()->SetTransform(bullet2->getBody()->GetPosition(), -45*DEGTORAD);
        bullet2->setScaleX(scaleX);
        bullet2->setScaleY(scaleY);
        
        this->getParent()->addChild(bullet2,2);
        
    }

    else
    {
        
        Bullet* bullet = new Bullet(world,ccp(this->getPositionX()-(27*scaleX),this->getPositionY()-(3*scaleY)),4,0);
        bullet->retain();
        bullet->setObjectTexture();
        bullet->setPosition(bullet->getPosition());
        bullet->setOriginalPosition(bullet->getPosition());
        bullet->addBody();
        bullet->getBody()->SetLinearVelocity(b2Vec2(0,50*scaleY));
        bullet->setScaleX(scaleX);
        bullet->setScaleY(scaleY);
        this->getParent()->addChild(bullet,2);
        
        
        
        Bullet* bullet2 = new Bullet(world,ccp(this->getPositionX()+(27*scaleX),this->getPositionY()-(3*scaleY)),4,0);
        bullet2->retain();
        bullet2->setObjectTexture();
        bullet2->setPosition(bullet2->getPosition());
        bullet2->setOriginalPosition(bullet2->getPosition());
        bullet2->addBody();
        bullet2->getBody()->SetLinearVelocity(b2Vec2(0,50*scaleY));
        bullet2->setScaleX(scaleX);
        bullet2->setScaleY(scaleY);
        this->getParent()->addChild(bullet2,2);
        
    }
    
    
    /*
    Bullet* bullet3 = new Bullet(world,ccp(this->getPositionX()-25,this->getPositionY()-5),4,0);
    bullet3->retain();
    bullet3->setObjectTexture();
    bullet3->setPosition(bullet3->getPosition());
    bullet3->setOriginalPosition(bullet3->getPosition());
    bullet3->addBody();
    bullet3->getBody()->SetTransform(bullet3->getBody()->GetPosition(), 315 * DEGTORAD);
    bullet3->getBody()->SetLinearVelocity(b2Vec2(33,50));
    
    this->getParent()->addChild(bullet3);
    
    Bullet* bullet4 = new Bullet(world,ccp(this->getPositionX()+25,this->getPositionY()-5),4,0);
    bullet4->retain();
    bullet4->setObjectTexture();
    bullet4->setPosition(bullet4->getPosition());
    bullet4->setOriginalPosition(bullet4->getPosition());
    bullet4->addBody();
    
    bullet4->getBody()->SetTransform(bullet4->getBody()->GetPosition(), 45 * DEGTORAD);
    bullet4->getBody()->SetLinearVelocity(b2Vec2(-33,50
                                                 ));
    
     
     
    this->getParent()->addChild(bullet4);
    */
    /*
    MainGame* m = (MainGame*)this->getParent();
    
    m->shapes->addObject(bullet);
    */
}

void Player::stopShooting()
{
    shootOn = false;
    unschedule( schedule_selector(Player::shootBullets));
    
    shoot = false;
}



void Player::speedNormal()
{
    slowdownOn = false;
    slowdown = false;
}


void Player::randomBonus()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("bonus.wav");
    
    /*
    if(smallbonusOn == false && invinciblebonusOn == false && shootOn == false)
    {*/
    
    
        int r = rand() % 4  + 1;
        
        if(r == 1)
        {

            //goInvincible();
          
            invinciblebonus = true;
           

        }
        else if(r==2)
        {
            smallbonus = true;
            //goSmaller();
            
        }
        else if(r==3)
        {
            shoot = true;
            //startShooting();
          
        }
        else if(r==4)
        {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("slowdown.wav");
            slowdown = true;
            //slowDown();
        }
 
   // }
    
}


void Player::turnRight()
{
    
    this->stopActionByTag(50);
    lookingRight = true;
    
        //this->stopAllActions();
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shipsright.plist");
        
        
        
        CCArray* walkAnimFrames = new CCArray();
        
        
        for(int i = 1; i <4; i++) {
            std::string s;
            std::stringstream out;
            out << i;
            s = out.str();
            
            string test2="shipright"+s+".png";
            
            walkAnimFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( test2.c_str() ));
            
        }
        
        CCAnimation* walkAnim = CCAnimation::createWithSpriteFrames(walkAnimFrames);
        walkAnim->setDelayPerUnit(0.03f);
        
        rightA =CCRepeatForever::create(CCAnimate::create(walkAnim));
        rightA->setTag(50);
        this->runAction(rightA);
        
        CCSpriteFrame* pFrame;
        
        //tries to get the frame
        pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("shipright1.png");
        
        initWithSpriteFrame(pFrame);
    
    
    

    
}


void Player::turnLeft()
{
    this->stopActionByTag(50);
    
    lookingLeft = true;
    //this->stopAllActions();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shipsleft.plist");
    
    
    
    CCArray* walkAnimFrames = new CCArray();
    
    
    for(int i = 1; i <4; i++) {
        std::string s;
        std::stringstream out;
        out << i;
        s = out.str();
        
        string test2="shipleft"+s+".png";
        
        walkAnimFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( test2.c_str() ));
        
    }
    
    CCAnimation* walkAnim = CCAnimation::createWithSpriteFrames(walkAnimFrames);
    walkAnim->setDelayPerUnit(0.03f);
    
    leftA =CCRepeatForever::create(CCAnimate::create(walkAnim));
    leftA->setTag(50);
    this->runAction(leftA);
    
    CCSpriteFrame* pFrame;
    
    //tries to get the frame
    pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("shipleft1.png");
    
    initWithSpriteFrame(pFrame);
    
    
}

void Player::explode()
{
    
    //this->stopActionByTag(50);
    
    this->stopAllActions();
    //this->pauseSchedulerAndActions();
    this->stopShooting();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("explosionspritesheet.plist");
    
    
    
    CCArray* walkAnimFrames = new CCArray();
    
    
    for(int i = 1; i <26; i++) {
        std::string s;
        std::stringstream out;
        out << i;
        s = out.str();
        
        string test2="explosion"+s+".png";
        
        walkAnimFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( test2.c_str() ));
        
    }
    
    CCAnimation* walkAnim = CCAnimation::createWithSpriteFrames(walkAnimFrames);
    walkAnim->setDelayPerUnit(0.05f);
    
    CCAction* walkAction =CCAnimate::create(walkAnim);
    
    this->runAction(walkAction);
    
    CCSpriteFrame* pFrame;
    
}
