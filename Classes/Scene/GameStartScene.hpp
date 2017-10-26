//
//  GameStartScene.hpp
//  dungeonTiles
//
//  Created by Moon on 16/8/10.
//
//

#ifndef GameStartScene_hpp
#define GameStartScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ConstUtil.hpp"
#include "Scene/GameScene.hpp"
#include "SimpleAudioEngine.h"
#include "Manager/SaveManager.hpp"
#include "Layer/GuideLayer.hpp"

class GameStartScene:public cocos2d::Scene{
public:
    CREATE_FUNC(GameStartScene);
    virtual bool init();
    void initUI();
    
    cocos2d::EventListenerTouchOneByOne* touchListener;
    
    virtual bool onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch,cocos2d::Event* event);
private:
    cocos2d::Sprite* btn_setting;
    cocos2d::Sprite* btn_play;
    cocos2d::Sprite* btn_tutorial;
    cocos2d::Sprite* btn_bgm;
    cocos2d::Sprite* btn_sound;
    
    void addBackgroundParticle();
};
#endif /* GameStartScene_hpp */
