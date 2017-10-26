//
//  GameStartScene.cpp
//  dungeonTiles
//
//  Created by Moon on 16/8/10.
//
//

#include "GameStartScene.hpp"

USING_NS_CC;
using namespace CocosDenshion;

bool GameStartScene::init(){
    addBackgroundParticle();
    initUI();
    return true;
}

void GameStartScene::initUI(){
	if (SaveManager::getInstance()->getBGMOn()) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACKGROUND2, true);
	}
    Size visibleSize=Director::getInstance()->getVisibleSize();
    auto background=Sprite::create(BACKGROUND_PIC);
    background->setColor(Color3B(138, 0, 139));
    background->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    this->addChild(background);
    
    auto logo=Sprite::createWithSpriteFrameName("logo.png");
    logo->setColor(Color3B(218,112,214));
    logo->setOpacity(0);
    logo->setPosition(Vec2(DesignResolutionWidth/2,DesignResolutionHeight*73/100));
    addChild(logo,10);
    
    auto fadeIn=FadeIn::create(1.5);
    logo->runAction(Sequence::create(fadeIn,CallFunc::create([this,visibleSize](){
        ParticleSystem* particleSystem_fire1=ParticleSystemQuad::create(PARTICLE_FIRE1);
        ParticleSystem* particleSystem_fire2=ParticleSystemQuad::create(PARTICLE_FIRE2);
        particleSystem_fire1->retain();
        particleSystem_fire2->retain();
        ParticleBatchNode* batch4=ParticleBatchNode::createWithTexture(particleSystem_fire1->getTexture());
        ParticleBatchNode* batch5=ParticleBatchNode::createWithTexture(particleSystem_fire2->getTexture());
        batch4->addChild(particleSystem_fire1);
        addChild(batch4,2);
        batch5->addChild(particleSystem_fire2);
        addChild(batch5,2);
        particleSystem_fire1->setPosition(Vec2(visibleSize.width/2,visibleSize.height*0.76));
        particleSystem_fire2->setPosition(Vec2(visibleSize.width/2,visibleSize.height*0.65));
    }),NULL));
    
    btn_tutorial=Sprite::createWithSpriteFrameName(BTN_TUTORIAL);
    btn_tutorial->setPosition(Vec2(DesignResolutionWidth/2-240,DesignResolutionHeight/2));
    addChild(btn_tutorial,10);
    
    btn_play=Sprite::createWithSpriteFrameName(BTN_PLAY);
    btn_play->setPosition(Vec2(DesignResolutionWidth/2+240,DesignResolutionHeight/2));
    addChild(btn_play,10);
    
    btn_setting=Sprite::createWithSpriteFrameName(BTN_SETTING);
    btn_setting->setPosition(Vec2(240,240));
    addChild(btn_setting,10);
    
    touchListener=EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan=CC_CALLBACK_2(GameStartScene::onTouchBegan, this);
    touchListener->onTouchMoved=CC_CALLBACK_2(GameStartScene::onTouchMoved, this);
    touchListener->onTouchEnded=CC_CALLBACK_2(GameStartScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
}

bool GameStartScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    if(btn_setting->getBoundingBox().containsPoint(touch->getLocation())&&btn_setting->getBoundingBox().containsPoint(Point(240,240))){
        if(SaveManager::getInstance()->getSoundOn()){
            btn_sound=Sprite::createWithSpriteFrameName(BTN_SOUND_OPEN);
        }else{
            btn_sound=Sprite::createWithSpriteFrameName(BTN_SOUND_OFF);
        }
        if(SaveManager::getInstance()->getBGMOn()){
            btn_bgm=Sprite::createWithSpriteFrameName(BTN_BGM_OPEN);
        }else{
            btn_bgm=Sprite::createWithSpriteFrameName(BTN_BGM_OFF);
        }
        btn_sound->setPosition(Vec2(-200,240));
        this->addChild(btn_sound,10);
        btn_bgm->setPosition(Vec2(-200,240));
        this->addChild(btn_bgm,10);
        
        auto right0=MoveTo::create(0.2, Vec2(240,240));
        btn_bgm->runAction(right0);
        auto right1=MoveTo::create(0.2, Vec2(480,240));
        btn_sound->runAction(right1);
        auto right2=MoveTo::create(0.2, Vec2(720,240));
        btn_setting->runAction(right2);
    }else if(btn_setting->getBoundingBox().containsPoint(touch->getLocation())&&btn_setting->getBoundingBox().containsPoint(Point(720,240))){
        auto left0=MoveTo::create(0.2, Vec2(-200,240));
        btn_bgm->runAction(left0);
        auto left1=MoveTo::create(0.2, Vec2(-200,240));
        btn_sound->runAction(left1);
        auto left2=MoveTo::create(0.2, Vec2(240,240));
        btn_setting->runAction(left2);
    }else if(btn_play->getBoundingBox().containsPoint(touch->getLocation())){
        if(SaveManager::getInstance()->getFirstIn()==true){
            auto guideLayer=GuideLayer::create();
            addChild(guideLayer,11);
        }else{
            Director::getInstance()->pushScene(GameScene::create());
        }
        
    }else if(btn_tutorial->getBoundingBox().containsPoint(touch->getLocation())){
        auto guideLayer=GuideLayer::create();
        addChild(guideLayer,11);
    }else if(btn_sound!=nullptr&&btn_sound->getBoundingBox().containsPoint(touch->getLocation())){
        if(SaveManager::getInstance()->getSoundOn()){
            btn_sound->initWithSpriteFrameName(BTN_SOUND_OFF);
            SaveManager::getInstance()->setSoundOn(false);
        }else{
            btn_sound->initWithSpriteFrameName(BTN_SOUND_OPEN);
            SaveManager::getInstance()->setSoundOn(true);
        }
    }else if(btn_bgm!=nullptr&&btn_bgm->getBoundingBox().containsPoint(touch->getLocation())){
        if(SaveManager::getInstance()->getBGMOn()){
            btn_bgm->initWithSpriteFrameName(BTN_BGM_OFF);
            SimpleAudioEngine::getInstance()->stopBackgroundMusic(AUDIO_BACKGROUND2);
            SaveManager::getInstance()->setBGMOn(false);
        }else{
            btn_bgm->initWithSpriteFrameName(BTN_BGM_OPEN);
            SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACKGROUND2,true);
            SaveManager::getInstance()->setBGMOn(true);
        }
    }
    
    return true;
}

void GameStartScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    
}

void GameStartScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    
}

void GameStartScene::addBackgroundParticle(){
    Size visibleSize=Director::getInstance()->getVisibleSize();
    ParticleSystem* particleSystem_bgd1=ParticleSystemQuad::create(PARTICLE_BACKGROUND1);
    ParticleSystem* particleSystem_bgd2=ParticleSystemQuad::create(PARTICLE_BACKGROUND2);
    ParticleSystem* particleSystem_bgd3=ParticleSystemQuad::create(PARTICLE_BACKGROUND3);
    
    particleSystem_bgd1->retain();
    particleSystem_bgd2->retain();
    particleSystem_bgd3->retain();
    
    
    ParticleBatchNode* batch1=ParticleBatchNode::createWithTexture(particleSystem_bgd1->getTexture());
    ParticleBatchNode* batch2=ParticleBatchNode::createWithTexture(particleSystem_bgd2->getTexture());
    ParticleBatchNode* batch3=ParticleBatchNode::createWithTexture(particleSystem_bgd3->getTexture());
    
    batch1->addChild(particleSystem_bgd1);
    addChild(batch1,2);
    batch2->addChild(particleSystem_bgd2);
    addChild(batch2,2);
    batch3->addChild(particleSystem_bgd3);
    addChild(batch3,2);
    
    
    particleSystem_bgd1->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    particleSystem_bgd2->setPosition(Vec2(visibleSize.width/4,visibleSize.height/2));
    particleSystem_bgd3->setPosition(Vec2(visibleSize.width*0.75,visibleSize.height/2));
    
}





