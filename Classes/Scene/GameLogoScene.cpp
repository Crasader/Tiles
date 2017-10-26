//
//  GameLogoScene.cpp
//  dungeonTiles
//
//  Created by Moon on 16/9/10.
//
//

#include "GameLogoScene.hpp"

USING_NS_CC;

bool GameLogoScene::init(){
    Size visibleSize=Director::getInstance()->getVisibleSize();
    
    auto background=Sprite::create(SPLASH_PIC);
    background->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    addChild(background);
    
    background->setOpacity(0);
    
    auto fadein=FadeIn::create(1);
    auto fadeOut=FadeOut::create(1);
    auto seq=Sequence::create(fadein,DelayTime::create(1),fadeOut,DelayTime::create(1),CallFunc::create([this](){
        auto scene=GameStartScene::create();
        Director::getInstance()->replaceScene(scene);
    }),NULL);
    background->runAction(seq);
    return true;
}