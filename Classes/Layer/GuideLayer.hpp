//
//  GuideLayer.hpp
//  dungeonTiles
//
//  Created by Moon on 16/8/14.
//
//

#ifndef GuideLayer_hpp
#define GuideLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ConstUtil.hpp"
#include "Manager/GameManager.hpp"
#include "Manager/SaveManager.hpp"
#include "Scene/GameScene.hpp"

class GuideLayer:public cocos2d::Layer{
public:
    CREATE_FUNC(GuideLayer);
    virtual bool init();
    
    
    virtual bool onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch,cocos2d::Event* event);
private:
    cocos2d::Sprite* guidePic;
    cocos2d::Sprite* btn_continue;
    int guideTag;
    cocos2d::EventListenerTouchOneByOne* touchListener;
    
    void initUI();
    void initFirst();
    void initSecond();
    void initThrid();
    void keyUpCallBack(cocos2d::Touch* t,cocos2d::Event* e);
    void keyDownCallBack(cocos2d::Touch* t,cocos2d::Event* e);
    void guideOver();
    void resetGuide();
    
    cocos2d::Sprite* exchange_btn;
    cocos2d::Label* score;
};
#endif /* GuideLayer_hpp */
