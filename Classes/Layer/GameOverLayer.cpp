//
//  GameOverLayer.cpp
//  dungeonTiles
//
//  Created by Moon on 16/8/12.
//
//

#include "GameOverLayer.hpp"

USING_NS_CC;

bool GameOverLayer::init(){
    initUI();
    return true;
}

void GameOverLayer::initUI(){
    hasGetGolds=false;
    _3000golds=3000;
    
    Size visibleSize=Director::getInstance()->getVisibleSize();
    background=Sprite::create(BACKGROUND_PIC);
    background->setOpacity(150);
    background->setColor(COLOR3B_GAME_BG);
    background->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    this->addChild(background);
    
    auto gameOver_ribbon=Sprite::create("Button/gameover_ribbon.png");
    gameOver_ribbon->setColor(COLOR3B_MENU_BG);
    gameOver_ribbon->setPosition(Vec2(visibleSize.width/2,visibleSize.height*0.8));
    addChild(gameOver_ribbon);
    
    auto gameOver_label=Label::createWithTTF("Game Over",FONT_ROUND_ZN,110);
    gameOver_ribbon->addChild(gameOver_label);
    gameOver_label->setColor(COLOR3B_NUMBER);
    gameOver_label->setPosition(Point(gameOver_ribbon->getContentSize().width/2,gameOver_ribbon->getContentSize().height*0.6));
    
    if(GameManager::getInstance()->isLife0==true){
        gameOverReason_label=Label::createWithTTF("生命为0",FONT_ROUND_ZN,70);
    }else{
        gameOverReason_label=Label::createWithTTF("不能再移动",FONT_ROUND_ZN,70);
    }
    gameOverReason_label->setColor(COLOR3B_LIFE_BG);
    gameOverReason_label->setPosition(Point(visibleSize.width/2,visibleSize.height*0.73));
    addChild(gameOverReason_label);
    
    auto gameOver_result_card1=Sprite::createWithSpriteFrameName("gameover_result_card.png");
    gameOver_result_card1->setPosition(Vec2(visibleSize.width/2,visibleSize.height*0.6));
    addChild(gameOver_result_card1);
    
    auto gameOver_result_label1=Label::createWithTTF("得分",FONT_ROUND_ZN,CARD_NUMBER_SIZE);
    gameOver_result_card1->addChild(gameOver_result_label1);
    gameOver_result_label1->setColor(COLOR3B_NUMBER);
    gameOver_result_label1->setPosition(Point(gameOver_result_card1->getContentSize().width/2,gameOver_result_card1->getContentSize().height*0.7));
    
    auto score_label=Label::createWithTTF(StringUtils::format("%d",SaveManager::getInstance()->score_number), FONT_ROUND_ZN, SCORE_NUMBER_SIZE);
    gameOver_result_card1->addChild(score_label);
    score_label->setColor(COLOR3B_NUMBER);
    score_label->setPosition(Point(gameOver_result_card1->getContentSize().width/2,gameOver_result_card1->getContentSize().height*0.4));
    
    auto gameOver_result_card2=Sprite::createWithSpriteFrameName("gameover_result_card.png");
    gameOver_result_card2->setPosition(Vec2(visibleSize.width/2,visibleSize.height*0.45));
    addChild(gameOver_result_card2);
    
    auto gameOver_result_label2=Label::createWithTTF("最高得分",FONT_ROUND_ZN,CARD_NUMBER_SIZE);
    gameOver_result_card2->addChild(gameOver_result_label2);
    gameOver_result_label2->setColor(COLOR3B_NUMBER);
    gameOver_result_label2->setPosition(Point(gameOver_result_card2->getContentSize().width/2,gameOver_result_card2->getContentSize().height*0.7));
    
    auto max_score_label=Label::createWithTTF(StringUtils::format("%d",SaveManager::getInstance()->getMaxPoint()), FONT_ROUND_ZN, SCORE_NUMBER_SIZE);
    gameOver_result_card2->addChild(max_score_label);
    max_score_label->setColor(COLOR3B_NUMBER);
    max_score_label->setPosition(Point(gameOver_result_card2->getContentSize().width/2,gameOver_result_card2->getContentSize().height*0.4));
    
    auto gameOver_result_card3=Sprite::createWithSpriteFrameName("gameover_result_card.png");
    gameOver_result_card3->setColor(COLOR3B_GOLD_BG);
    gameOver_result_card3->setPosition(Vec2(visibleSize.width/2,visibleSize.height*0.3));
    addChild(gameOver_result_card3);
    
    gameOver_result_label3=Label::createWithTTF("金币",FONT_ROUND_ZN,CARD_NUMBER_SIZE);
    gameOver_result_card3->addChild(gameOver_result_label3);
    gameOver_result_label3->setColor(COLOR3B_GOLD_BG);
    gameOver_result_label3->setPosition(Point(gameOver_result_card3->getContentSize().width/2,gameOver_result_card3->getContentSize().height*0.7));
    
    golds=SaveManager::getInstance()->geteGolds();
    gold_label=Label::createWithTTF(StringUtils::format("%d",SaveManager::getInstance()->geteGolds()), FONT_ROUND_ZN, SCORE_NUMBER_SIZE);
    gameOver_result_card3->addChild(gold_label);
    gold_label->setColor(COLOR3B_GOLD_BG);
    gold_label->setPosition(Point(gameOver_result_card3->getContentSize().width/2,gameOver_result_card3->getContentSize().height*0.4));
    
    btn_menu=Sprite::createWithSpriteFrameName("game_button_menu.png");
    addChild(btn_menu);
    btn_menu->setPosition(Vec2(visibleSize.width/2-300,visibleSize.height*0.15));
    
    btn_retry=Sprite::createWithSpriteFrameName("game_button_retry.png");
    addChild(btn_retry);
    btn_retry->setPosition(Vec2(visibleSize.width/2,visibleSize.height*0.15));
    
    btn_getGold=Sprite::createWithSpriteFrameName("game_button_getgolds.png");
    addChild(btn_getGold);
    btn_getGold->setPosition(Vec2(visibleSize.width/2+300,visibleSize.height*0.15));
    
    touchListener=EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan=CC_CALLBACK_2(GameOverLayer::onTouchBegan, this);
    touchListener->onTouchMoved=CC_CALLBACK_2(GameOverLayer::onTouchMoved, this);
    touchListener->onTouchEnded=CC_CALLBACK_2(GameOverLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    scheduleUpdate();
}

void GameOverLayer::update(float delay){
    if(hasGetGolds){
        gold_label->setString(__String::createWithFormat("%i",golds+250)->getCString());
        golds+=100;
        _3000golds-=100;
        if(_3000golds==0){
            hasGetGolds=false;
            gameOver_result_label3->setString("您得到3000金币");
        }
    }
}

bool GameOverLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    if(btn_menu->getBoundingBox().containsPoint(touch->getLocation())){
        Director::getInstance()->popScene();
        removeFromParent();
    }else if(btn_retry->getBoundingBox().containsPoint(touch->getLocation())){
        this->setVisible(false);
        _eventDispatcher->removeEventListener(touchListener);
        touchListener=nullptr;  
        GameManager::getInstance()->resetgame=true;
        removeFromParent();
    }else if(btn_getGold!=nullptr && btn_getGold->getBoundingBox().containsPoint(touch->getLocation())){
        SaveManager::getInstance()->setGolds(SaveManager::getInstance()->geteGolds()+3000);
        btn_getGold->removeFromParent();
        btn_getGold=nullptr;
        hasGetGolds=true;
    }

    return true;
}

void GameOverLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    
}

void GameOverLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    
}