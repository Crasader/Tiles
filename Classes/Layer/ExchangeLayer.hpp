//
//  ExchangeLayer.hpp
//  dungeonTiles
//
//  Created by Moon on 16/8/11.
//
//

#ifndef ExchangeLayer_hpp
#define ExchangeLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ConstUtil.hpp"
#include "Scene/GameScene.hpp"
#include "Manager/SaveManager.hpp"
#include "Manager/GameManager.hpp"

class ExchangeLayer:public cocos2d::Layer{
public:
    CREATE_FUNC(ExchangeLayer);
    virtual bool init();
    void initUI();
    
    cocos2d::Sprite* background;
    cocos2d::EventListenerTouchOneByOne* touchListener;
    
    virtual bool onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch,cocos2d::Event* event);
private:
    cocos2d::Sprite* btn_sword1;
    cocos2d::Sprite* btn_sword2;
    cocos2d::Sprite* btn_life1;
    cocos2d::Sprite* btn_life2;
    cocos2d::Sprite* btn_dragon1;
    cocos2d::Sprite* btn_dragon2;
    cocos2d::Sprite* btn_close;
    cocos2d::Sprite* btn_anandon;
    
    cocos2d::Sprite* skill_ng1;
    cocos2d::Sprite* skill_ng2;
    cocos2d::Sprite* skill_ng3;
    cocos2d::Sprite* skill_ng4;
    cocos2d::Sprite* skill_ng5;
    cocos2d::Sprite* skill_ng6;
    
    void down_action();
};


#endif /* ExchangeLayer_hpp */
