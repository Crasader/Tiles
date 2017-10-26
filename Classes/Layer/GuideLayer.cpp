//
//  GuideLayer.cpp
//  dungeonTiles
//
//  Created by Moon on 16/8/14.
//
//

#include "GuideLayer.hpp"
USING_NS_CC;

bool GuideLayer::init()
{
    initUI();
    return true;
}

void GuideLayer::initUI(){
    guidePic=Sprite::create(GUIDE1);
    guidePic->setPosition(Vec2(DesignResolutionWidth/2,DesignResolutionHeight/2));
    addChild(guidePic);
    guideTag=1;
    touchListener=EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan=CC_CALLBACK_2(GuideLayer::onTouchBegan, this);
    touchListener->onTouchMoved=CC_CALLBACK_2(GuideLayer::onTouchMoved, this);
    touchListener->onTouchEnded=CC_CALLBACK_2(GuideLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool GuideLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    if(guideTag==1){
        guidePic->removeFromParent();
        guidePic=nullptr;
        guidePic=Sprite::create(GUIDE2);
        guidePic->setPosition(Vec2(DesignResolutionWidth/2,DesignResolutionHeight/2));
        addChild(guidePic);
        guideTag=2;
    }else if(guideTag==2){
        guidePic->removeFromParent();
        guidePic=nullptr;
        guidePic=Sprite::create(GUIDE3);
        guidePic->setPosition(Vec2(DesignResolutionWidth/2,DesignResolutionHeight/2));
        addChild(guidePic);
        guideTag=3;
    }else if(guideTag==3){
        auto background=LayerColor::create(Color4B(138,0,139,255), 1080, 1920);
        background->setIgnoreAnchorPointForPosition(false);
        background->setAnchorPoint(Point(0.5,0.5));
        background->setPosition(Vec2(DesignResolutionWidth/2,DesignResolutionHeight/2));
        background->setOpacity(150);
        addChild(background);
        
        auto guide_over_label=Label::createWithTTF("教学结束",FONT_ROUND_ZN,GUIDE_LALBEL_SIZE);
        addChild(guide_over_label);
        guide_over_label->setColor(COLOR3B_DRAGON_BG);
        guide_over_label->setPosition(Vec2(DesignResolutionWidth/2,DesignResolutionHeight/2));
        
        btn_continue=Sprite::createWithSpriteFrameName(BTN_CONTINUE);
        btn_continue->setPosition(Vec2(DesignResolutionWidth/2,DesignResolutionHeight*0.4));
        addChild(btn_continue);
        guideTag=4;
    }else if(guideTag==4&&btn_continue!=nullptr&&btn_continue->getBoundingBox().containsPoint(touch->getLocation())){
        this->setVisible(false);
        _eventDispatcher->removeEventListener(touchListener);
        touchListener=nullptr;
        removeFromParent();
        if(SaveManager::getInstance()->getFirstIn()==true){
            Director::getInstance()->pushScene(GameScene::create());
        }
    }
    
    return true;
}

void GuideLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    
}

void GuideLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    
}
