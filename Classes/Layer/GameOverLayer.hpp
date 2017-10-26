//
//  GameOverLayer.hpp
//  dungeonTiles
//
//  Created by Moon on 16/8/12.
//
//

#ifndef GameOverLayer_hpp
#define GameOverLayer_hpp

#include <stdio.h>
#include "ConstUtil.hpp"
#include "Manager/SaveManager.hpp"
#include "Manager/GameManager.hpp"

class GameOverLayer:public cocos2d::Layer{
public:
    CREATE_FUNC(GameOverLayer);
    virtual bool init();
    void initUI();
    
    virtual void update(float delay);
    
    cocos2d::Sprite* background;
    cocos2d::EventListenerTouchOneByOne* touchListener;
    
    virtual bool onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch,cocos2d::Event* event);
    
private:
    cocos2d::Sprite* btn_getGold;
    cocos2d::Sprite* btn_retry;
    cocos2d::Sprite* btn_menu;
    bool hasGetGolds;
    int changeGolds;
    cocos2d::Label* gold_label;
    int golds;
    int _3000golds;
    cocos2d::Label* gameOver_result_label3;
    cocos2d::Label* gameOverReason_label;
};

#endif /* GameOverLayer_hpp */
