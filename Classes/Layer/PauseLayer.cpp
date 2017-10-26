//
//  PauseLayer.cpp
//  dungeonTiles
//
//  Created by Moon on 16/8/10.
//
//

#include "PauseLayer.hpp"

USING_NS_CC;
using namespace CocosDenshion;

bool PauseLayer::init(){
    initUI();
    return true;
}

void PauseLayer::initUI(){
    Size visibleSize=Director::getInstance()->getVisibleSize();
    background=Sprite::create(BACKGROUND_PIC);
    background->setOpacity(150);
    background->setColor(COLOR3B_GAME_BG);
    background->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    this->addChild(background);
    
    btn_continue=Sprite::createWithSpriteFrameName(BTN_CONTINUE);
    btn_continue->setPosition(Vec2(DesignResolutionWidth/2-240,DesignResolutionHeight*0.73));
    addChild(btn_continue);
    
    btn_retry=Sprite::createWithSpriteFrameName(BTN_RETRY);
    btn_retry->setPosition(Vec2(DesignResolutionWidth/2+240,DesignResolutionHeight*0.73));
    addChild(btn_retry);
    
    if(SaveManager::getInstance()->getBGMOn()){
        btn_bgm=Sprite::createWithSpriteFrameName(BTN_BGM_OPEN);
    }else{
         btn_bgm=Sprite::createWithSpriteFrameName(BTN_BGM_OFF);
    }
    
    btn_bgm->setPosition(Vec2(DesignResolutionWidth/2-240,DesignResolutionHeight*0.5));
    addChild(btn_bgm);
    
    if(SaveManager::getInstance()->getSoundOn()){
         btn_sound=Sprite::createWithSpriteFrameName(BTN_SOUND_OPEN);
    }else{
        btn_sound=Sprite::createWithSpriteFrameName(BTN_SOUND_OFF);
    }
    btn_sound->setPosition(Vec2(DesignResolutionWidth/2+240,DesignResolutionHeight*0.5));
    addChild(btn_sound);
    
    btn_menu=Sprite::createWithSpriteFrameName(BTN_MENU);
    btn_menu->setPosition(Vec2(DesignResolutionWidth/2-240,DesignResolutionHeight*0.27));
    addChild(btn_menu);
    
    btn_help=Sprite::createWithSpriteFrameName(BTN_HELP);
    btn_help->setPosition(Vec2(DesignResolutionWidth/2+240,DesignResolutionHeight*0.27));
    addChild(btn_help);
    
    touchListener=EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan=CC_CALLBACK_2(PauseLayer::onTouchBegan, this);
    touchListener->onTouchMoved=CC_CALLBACK_2(PauseLayer::onTouchMoved, this);
    touchListener->onTouchEnded=CC_CALLBACK_2(PauseLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
}

bool PauseLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    if(btn_continue->getBoundingBox().containsPoint(touch->getLocation())){
        this->setVisible(false);
        _eventDispatcher->removeEventListener(touchListener);
        touchListener=nullptr;
        removeFromParent();
    }else if(btn_menu->getBoundingBox().containsPoint(touch->getLocation())){
        if(SaveManager::getInstance()->getBGMOn()){
            SimpleAudioEngine::getInstance()->stopBackgroundMusic(AUDIO_BACKGROUND1);
            SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACKGROUND2,true);
        }
        
        Director::getInstance()->popScene();
        removeFromParent();
    }else if(btn_sound->getBoundingBox().containsPoint(touch->getLocation())){
        if(SaveManager::getInstance()->getSoundOn()){
            btn_sound->initWithSpriteFrameName(BTN_SOUND_OFF);
            SaveManager::getInstance()->setSoundOn(false);
        }else{
            btn_sound->initWithSpriteFrameName(BTN_SOUND_OPEN);
            SaveManager::getInstance()->setSoundOn(true);
        }
    }else if(btn_bgm->getBoundingBox().containsPoint(touch->getLocation())){
        if(SaveManager::getInstance()->getBGMOn()){
            btn_bgm->initWithSpriteFrameName(BTN_BGM_OFF);
            SimpleAudioEngine::getInstance()->stopBackgroundMusic(AUDIO_BACKGROUND1);
            SaveManager::getInstance()->setBGMOn(false);
        }else{
            btn_bgm->initWithSpriteFrameName(BTN_BGM_OPEN);
            SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACKGROUND1 ,true);
            SaveManager::getInstance()->setBGMOn(true);
        }
    }else if(btn_retry->getBoundingBox().containsPoint(touch->getLocation())){
        this->setVisible(false);
        _eventDispatcher->removeEventListener(touchListener);
        touchListener=nullptr;
        GameManager::getInstance()->resetgame=true;
        removeFromParent();
    }else if(btn_help->getBoundingBox().containsPoint(touch->getLocation())){
        auto guideLayer=GuideLayer::create();
        addChild(guideLayer,10);
    }

    
    return true;
}

void PauseLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    
}

void PauseLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    
}