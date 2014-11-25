//
//  GameObject.cpp
//  MakeALevel
//
//  Created by darren mckeever on 05/10/2012.
//
//

#include "GameObject.h"



GameObject::GameObject(CCPoint pos,int ID,int rotationSetting)
{
    //this->originalPosition=pos;
    gameWorldCellPosition=pos;
    this->setPosition(pos);
    //this->setScaleX(scaleX);
    //this->setScaleY(scaleY);
    this->ID=ID;
    //this->setObjectTexture();
    this->rotationSetting=rotationSetting;
    this->autorelease();
    isenabled = false;
    isDead=false;
    limbCount=0;
    target=NULL;
    partner=NULL;
    passenger=NULL;
}
GameObject::GameObject(void)
{
}

GameObject::~GameObject(void)
{
}

void GameObject::setObjectTexture()
{
    //this->texture = CCTextureCache::sharedTextureCache()->addImage(ID.find(ID)->second);
    
    //initWithTexture(texture);
}

bool GameObject::initWithTexture(CCTexture2D* aTexture)
{
    if( CCSprite::initWithTexture(aTexture) )
    {
        m_state = kStateUngrabbed;
    }
    
    return true;
}
bool GameObject::initWithSpriteFrame( CCSpriteFrame* pSpriteFrame )
{
    if(CCSprite::initWithSpriteFrame(pSpriteFrame) )
    {
        m_state = kStateUngrabbed;
    }
    
    return true;
}

CCRect GameObject::rect()
{
    CCSize s = getTexture()->getContentSize();
    return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}

void GameObject::onEnter()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
    CCSprite::onEnter();
}

void GameObject::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}

bool GameObject::containsTouchLocation(CCTouch* touch)
{
    return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool GameObject::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    if (getState() != kStateUngrabbed) return false;
    if ( !containsTouchLocation(touch) ) return false;
    
    setState(kStateGrabbed) ;
    return true;
}

void GameObject::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    // If it weren't for the TouchDispatcher, you would need to keep a reference
    // to the touch from touchBegan and check that the current touch is the same
    // as that one.
    // Actually, it would be even more complicated since in the Cocos dispatcher
    // you get CCSets instead of 1 UITouch, so you'd need to loop through the set
    // in each touchXXX method.
    
    //CCAssert(getState() == kStateGrabbed, L"GameObject - Unexpected state!");
    /*
    
    CCPoint touchPoint = touch->getLocation();
    touchPoint = this->getParent()->convertToNodeSpace(touchPoint);
    setPosition( CCPointMake(touchPoint.x, touchPoint.y) );*/
    
}

void GameObject::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    //CCAssert(getState() == kStateGrabbed, L"GameObject - Unexpected state!");
    
    setState(kStateUngrabbed) ;
}

State GameObject::getState(){
    return m_state;
}
void GameObject::setState(State state){
    this->m_state=state;
}


CCObject* GameObject::copyWithZone(CCZone *pZone)
{
    this->retain();
    return this;
}

int GameObject::getID(){
    return ID;
}
void GameObject::touchDelegateRetain()
{
    this->retain();
}

void GameObject::touchDelegateRelease()
{
    this->release();
}
void GameObject::setOriginalPosition(CCPoint pos){
    this->originalPosition=pos;
}
CCPoint GameObject::getOriginalPosition(){
    return originalPosition;
}

CCPoint GameObject::getGameWorldCellPosition(){
    
    return gameWorldCellPosition;
}

void GameObject::setTarget(GameObject* target){
    this->target=target;
}


GameObject* GameObject::getTarget(){
    return target;
}


void GameObject::setPartner(GameObject* partner){
    this->partner=partner;
}


GameObject* GameObject::getPartner(){
    return partner;
}

bool GameObject::getIsDead(){
    return isDead;
}

void GameObject::die(){
    isDead=true;
    this->setTag(1000);
}
void GameObject::cleanRemove(){
    //this->setTag(1000);
}

void GameObject::enable()
{
    isenabled = true;
}
void GameObject::disable()
{
    isenabled = false;
}

int GameObject::getObjectType(){
    return 1;
}

int GameObject::getRotationSetting(){
    return rotationSetting;
}


void GameObject::addRoomCell(int rowNumber,int colNumber){
    //roomCells->addObject(ccp(rowNumber,colNumber));
    roomCells.push_back(ccp(rowNumber,colNumber));
}
/*
vector<CCPoint> GameObject::getRoomCells(){
    return roomCells;
}
*/
void GameObject::setPassenger(GameObject* pas){
    this->passenger=pas;
}
GameObject* GameObject::getPassenger(){
    return passenger;
}