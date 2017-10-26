//
//  GameManager.cpp
//  dungeonTiles
//
//  Created by Moon on 16/8/21.
//
//

#include "GameManager.hpp"
USING_NS_CC;

GameManager* GameManager::instance=NULL;
GameManager* GameManager::getInstance(){
    if(instance==NULL){
        instance=new GameManager();
    }
    return instance;
}

void GameManager::init(){
    resetgame=false;
    isDragonCome=false;
    isLife0=false;
}