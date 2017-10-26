//
//  PauseLayer.hpp
//  dungeonTiles
//
//  Created by Moon on 16/8/10.
//
//

#ifndef PauseLayer_hpp
#define PauseLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Manager/ResourceManager.hpp"
#include "ConstUtil.hpp"
#include "Manager/SaveManager.hpp"
#include "SimpleAudioEngine.h"
#include "Scene/GameScene.hpp"
#include "Manager/GameManager.hpp"

class PauseLayer:public cocos2d::Layer{
public:
    CREATE_FUNC(PauseLayer);
    virtual bool init();
    void initUI();
    
    cocos2d::Sprite* background;
    cocos2d::EventListenerTouchOneByOne* touchListener;
    
    virtual bool onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch,cocos2d::Event* event);
private:
    cocos2d::Sprite* btn_continue;
    cocos2d::Sprite* btn_retry;
    cocos2d::Sprite* btn_menu;
    cocos2d::Sprite* btn_bgm;
    cocos2d::Sprite* btn_sound;
    cocos2d::Sprite* btn_help;
};
#endif /* PauseLayer_hpp */
