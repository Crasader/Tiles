//
//  ResourceManager.cpp
//  dungeonTiles
//
//  Created by Moon on 16/7/29.
//
//

#include "ResourceManager.hpp"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

ResourceManager* ResourceManager::instance=NULL;
ResourceManager* ResourceManager::getInstance(){
    if(instance==NULL){
        instance=new ResourceManager();
    }
    return instance;
}

void ResourceManager::init(){
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Button/button.plist", "Button/button.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Card/card.plist", "Card/card.png");
    
    auto audio=SimpleAudioEngine::getInstance();
    audio->preloadBackgroundMusic(AUDIO_BACKGROUND1);
    audio->preloadBackgroundMusic(AUDIO_BACKGROUND2);
    audio->preloadEffect(AUDIO_BUTTON);
    audio->preloadEffect(AUDIO_BUTTON_SYSTEM);
    audio->preloadEffect(AUDIO_DRAGON);
    audio->preloadEffect(AUDIO_DRAGON_ATTACK);
    audio->preloadEffect(AUDIO_GOLD);
    audio->preloadEffect(AUDIO_LIFE);
    audio->preloadEffect(AUDIO_SWORD);
    audio->preloadEffect(AUDIO_SWORD_ATTACK);
    audio->preloadEffect(AUDIO_SHOOT);
    audio->preloadEffect(AUDIO_SWIPE);
    audio->preloadEffect(AUDIO_POST_BONUS);
    audio->preloadEffect(AUDIO_GAMEOVER_SWORD);
    audio->preloadEffect(AUDIO_DRAGON_COME);
    
}