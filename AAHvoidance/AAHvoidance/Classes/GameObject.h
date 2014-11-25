//
//  GameObject.h
//  MakeALevel
//
//  Created by darren mckeever on 11/10/2012.
//
//

#ifndef __MakeALevel__GameObject__
#define __MakeALevel__GameObject__


#include <iostream>
#include "cocos2d.h"

//#include "../Utilities/ImageScaler/ImageScaler.h"


using namespace cocos2d;

//USING_NS_CC;

typedef enum tagState
{
    kStateGrabbed,
    kStateUngrabbed
} State;


class GameObject : public CCSprite, public CCTargetedTouchDelegate
{
    
public:
    GameObject();
    GameObject(CCPoint pos, int ID, int rotation);
    virtual ~GameObject(void);
    
    virtual void setObjectTexture();
    bool initWithTexture(CCTexture2D* aTexture);
    bool initWithSpriteFrame( CCSpriteFrame* pSpriteFrame );
    virtual CCRect rect();
    
    virtual void onEnter();
    virtual void onExit();
    
    bool containsTouchLocation(CCTouch* touch);
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
    virtual CCObject* copyWithZone(CCZone *pZone);
    
    virtual void touchDelegateRetain();
    virtual void touchDelegateRelease();
    
    int getID();
    void setOriginalPosition(CCPoint pos);
    CCPoint getOriginalPosition();
    
    CCPoint getGameWorldCellPosition();
    
    virtual void setTarget(GameObject* target);
    virtual GameObject* getTarget();
    
    virtual void setPartner(GameObject* partner);
    virtual GameObject* getPartner();
    
    virtual bool getIsDead();
    virtual void die();
    virtual void cleanRemove();
    
    void enable();
    void disable();

    virtual int getObjectType();
    int getRotationSetting();
    
    void addRoomCell(int rowNumber,int colNumber);
    //std::vector<CCPoint> getRoomCells();
    
    void setPassenger(GameObject* passenger);
    GameObject* getPassenger();
    
    State getState();
    void setState(State m_state);
    
private:
    CCPoint originalPosition;
    GameObject* target;
    GameObject* partner;
    
protected:
    State        m_state;
    
    CCTexture2D* texture;
    int ID;
    CCPoint gameWorldCellPosition;
    bool isenabled;
    bool isDead;
    int limbCount;
    int rotationSetting;
    //use ccpoints
    std::vector<CCPoint> roomCells;
    GameObject* passenger;
    
};



#endif /* defined(__MakeALevel__GameObject__) */
