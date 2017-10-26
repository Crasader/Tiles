//
//  ExchangeLayer.cpp
//  dungeonTiles
//
//  Created by Moon on 16/8/11.
//
//

#include "ExchangeLayer.hpp"

USING_NS_CC;
bool ExchangeLayer::init(){
    initUI();
    return true;
}

void ExchangeLayer::initUI(){
    
    background=Sprite::createWithSpriteFrameName("skill_plate.png");
    background->setPosition(Vec2(DesignResolutionWidth/2,500));
    addChild(background);
    
    auto background2=LayerColor::create(Color4B(138,0,139,255), 948, 724);
    background2->setIgnoreAnchorPointForPosition(false);
    background2->setAnchorPoint(Point(0.5,0.5));
    background2->setPosition(Vec2(DesignResolutionWidth/2,500));
    background2->setOpacity(150);
    addChild(background2);
    
    btn_close=Sprite::createWithSpriteFrameName("skill_close.png");
    btn_close->setPosition((Vec2(DesignResolutionWidth/2+443,831)));
    addChild(btn_close);
    
    
    btn_sword1=Sprite::createWithSpriteFrameName("sword_card.png");
    btn_sword1->setPosition(Vec2(DesignResolutionWidth/2-320,600));
    addChild(btn_sword1);
    auto btn_sword1_label=Label::createWithTTF("双倍",FONT_ROUND_ZN,CARD_NUMBER_SIZE);
    btn_sword1->addChild(btn_sword1_label);
    btn_sword1_label->setColor(COLOR3B_NUMBER);
    btn_sword1_label->setPosition(Point(btn_sword1->getContentSize().width/2,btn_sword1->getContentSize().height*1/5));
    
    auto sword1_bottom_label=Label::createWithTTF("3000金币",FONT_ROUND_ZN,CARD_NUMBER_SIZE);
    sword1_bottom_label->setColor(COLOR3B_SWORD_BG);
    sword1_bottom_label->setPosition(Point(btn_sword1->getPosition().x,btn_sword1->getPosition().y-120));
    addChild(sword1_bottom_label);
    
    btn_sword2=Sprite::createWithSpriteFrameName("sword_card.png");
    btn_sword2->setPosition(Vec2(DesignResolutionWidth/2-320,300));
    addChild(btn_sword2);
    
    auto btn_sword2_label=Label::createWithTTF("+10",FONT_ROUND_ZN,CARD_NUMBER_SIZE);
    btn_sword2->addChild(btn_sword2_label);
    btn_sword2_label->setColor(COLOR3B_NUMBER);
    btn_sword2_label->setPosition(Point(btn_sword2->getContentSize().width/2,btn_sword2->getContentSize().height*1/5));
    
    auto sword2_bottom_label=Label::createWithTTF("1000金币",FONT_ROUND_ZN,CARD_NUMBER_SIZE);
    sword2_bottom_label->setColor(COLOR3B_SWORD_BG);
    sword2_bottom_label->setPosition(Point(btn_sword2->getPosition().x,btn_sword2->getPosition().y-120));
    addChild(sword2_bottom_label);
    
    
    btn_life1=Sprite::createWithSpriteFrameName("life_card.png");
    btn_life1->setPosition(Vec2(DesignResolutionWidth/2,600));
    addChild(btn_life1);
    
    
    auto btn_life1_label=Label::createWithTTF("双倍",FONT_ROUND_ZN,CARD_NUMBER_SIZE);
    btn_life1->addChild(btn_life1_label);
    btn_life1_label->setColor(COLOR3B_NUMBER);
    btn_life1_label->setPosition(Point(btn_life1->getContentSize().width/2,btn_life1->getContentSize().height*1/5));
    
    auto life1_bottom_label=Label::createWithTTF("3000金币",FONT_ROUND_ZN,CARD_NUMBER_SIZE);
    life1_bottom_label->setColor(COLOR3B_LIFE_BG);
    life1_bottom_label->setPosition(Point(btn_life1->getPosition().x,btn_life1->getPosition().y-120));
    addChild(life1_bottom_label);
    
    btn_life2=Sprite::createWithSpriteFrameName("life_card.png");
    btn_life2->setPosition(Vec2(DesignResolutionWidth/2,300));
    addChild(btn_life2);
    
    auto btn_life2_label=Label::createWithTTF("+10",FONT_ROUND_ZN,CARD_NUMBER_SIZE);
    btn_life2->addChild(btn_life2_label);
    btn_life2_label->setColor(COLOR3B_NUMBER);
    btn_life2_label->setPosition(Point(btn_life2->getContentSize().width/2,btn_life2->getContentSize().height*1/5));
    
    auto life2_bottom_label=Label::createWithTTF("1000金币",FONT_ROUND_ZN,CARD_NUMBER_SIZE);
    life2_bottom_label->setColor(COLOR3B_LIFE_BG);
    life2_bottom_label->setPosition(Point(btn_life2->getPosition().x,btn_life2->getPosition().y-120));
    addChild(life2_bottom_label);
    
    btn_dragon1=Sprite::createWithSpriteFrameName("dragon_card.png");
    btn_dragon1->setPosition(Vec2(DesignResolutionWidth/2+320,600));
    addChild(btn_dragon1);
    
    auto btn_dragon1_label=Label::createWithTTF("移除",FONT_ROUND_ZN,CARD_NUMBER_SIZE);
    btn_dragon1->addChild(btn_dragon1_label);
    btn_dragon1_label->setColor(COLOR3B_NUMBER);
    btn_dragon1_label->setPosition(Point(btn_dragon1->getContentSize().width/2,btn_dragon1->getContentSize().height*1/5));
    
    auto dragon1_bottom_label=Label::createWithTTF("3000金币",FONT_ROUND_ZN,CARD_NUMBER_SIZE);
    dragon1_bottom_label->setColor(COLOR3B_DRAGON_BG);
    dragon1_bottom_label->setPosition(Point(btn_dragon1->getPosition().x,btn_dragon1->getPosition().y-120));
    addChild(dragon1_bottom_label);
    
    btn_dragon2=Sprite::createWithSpriteFrameName("dragon_card.png");
    btn_dragon2->setPosition(Vec2(DesignResolutionWidth/2+320,300));
    addChild(btn_dragon2);
    
    auto btn_dragon2_label=Label::createWithTTF("-10",FONT_ROUND_ZN,CARD_NUMBER_SIZE);
    btn_dragon2->addChild(btn_dragon2_label);
    btn_dragon2_label->setColor(COLOR3B_NUMBER);
    btn_dragon2_label->setPosition(Point(btn_dragon2->getContentSize().width/2,btn_dragon2->getContentSize().height*1/5));
    
    auto dragon2_bottom_label=Label::createWithTTF("1000金币",FONT_ROUND_ZN,CARD_NUMBER_SIZE);
    dragon2_bottom_label->setColor(COLOR3B_DRAGON_BG);
    dragon2_bottom_label->setPosition(Point(btn_dragon2->getPosition().x,btn_dragon2->getPosition().y-120));
    addChild(dragon2_bottom_label);
    
    auto golds=SaveManager::getInstance()->geteGolds();
    if(golds<1000){
        skill_ng1=Sprite::createWithSpriteFrameName("skill_ng.png");
        skill_ng2=Sprite::createWithSpriteFrameName("skill_ng.png");
        skill_ng3=Sprite::createWithSpriteFrameName("skill_ng.png");
        skill_ng4=Sprite::createWithSpriteFrameName("skill_ng.png");
        skill_ng5=Sprite::createWithSpriteFrameName("skill_ng.png");
        skill_ng6=Sprite::createWithSpriteFrameName("skill_ng.png");
        btn_sword1->addChild(skill_ng1);
        skill_ng1->setPosition(btn_sword1->getContentSize().width/2,btn_sword1->getContentSize().height/2);
        btn_sword2->addChild(skill_ng2);
        skill_ng2->setPosition(btn_sword2->getContentSize().width/2,btn_sword2->getContentSize().height/2);
        btn_life1->addChild(skill_ng3);
        skill_ng3->setPosition(btn_life1->getContentSize().width/2,btn_life1->getContentSize().height/2);
        btn_life2->addChild(skill_ng4);
        skill_ng4->setPosition(btn_life2->getContentSize().width/2,btn_life2->getContentSize().height/2);
        btn_dragon1->addChild(skill_ng5);
        skill_ng5->setPosition(btn_dragon1->getContentSize().width/2,btn_dragon1->getContentSize().height/2);
        btn_dragon2->addChild(skill_ng6);
        skill_ng6->setPosition(btn_dragon2->getContentSize().width/2,btn_dragon2->getContentSize().height/2);
    }else if(golds>=1000&&golds<3000){
        skill_ng1=Sprite::createWithSpriteFrameName("skill_ng.png");
        skill_ng3=Sprite::createWithSpriteFrameName("skill_ng.png");
        skill_ng5=Sprite::createWithSpriteFrameName("skill_ng.png");
        btn_sword1->addChild(skill_ng1);
        skill_ng1->setPosition(btn_sword1->getContentSize().width/2,btn_sword1->getContentSize().height/2);
        btn_life1->addChild(skill_ng3);
        skill_ng3->setPosition(btn_life1->getContentSize().width/2,btn_life1->getContentSize().height/2);
        btn_dragon1->addChild(skill_ng5);
        skill_ng5->setPosition(btn_dragon1->getContentSize().width/2,btn_dragon1->getContentSize().height/2);
    }
    
    touchListener=EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan=CC_CALLBACK_2(ExchangeLayer::onTouchBegan, this);
    touchListener->onTouchMoved=CC_CALLBACK_2(ExchangeLayer::onTouchMoved, this);
    touchListener->onTouchEnded=CC_CALLBACK_2(ExchangeLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool ExchangeLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    if(btn_sword1->getBoundingBox().containsPoint(touch->getLocation())&&skill_ng1==nullptr){
        GameManager::getInstance()->exchangeNum=1;
        GameManager::getInstance()->goldLabel_vector.push_back(-3000);
        down_action();
    }else if(btn_sword2->getBoundingBox().containsPoint(touch->getLocation())&&skill_ng2==nullptr){
        GameManager::getInstance()->exchangeNum=2;
        GameManager::getInstance()->goldLabel_vector.push_back(-1000);
        down_action();
    }else if(btn_life1->getBoundingBox().containsPoint(touch->getLocation())&&skill_ng3==nullptr){
        GameManager::getInstance()->exchangeNum=3;
        GameManager::getInstance()->goldLabel_vector.push_back(-3000);
        down_action();
    }else if(btn_life2->getBoundingBox().containsPoint(touch->getLocation())&&skill_ng4==nullptr){
        GameManager::getInstance()->exchangeNum=4;
        GameManager::getInstance()->goldLabel_vector.push_back(-1000);
        down_action();
    }else if(btn_dragon1->getBoundingBox().containsPoint(touch->getLocation())&&skill_ng5==nullptr){
        GameManager::getInstance()->exchangeNum=5;
        GameManager::getInstance()->goldLabel_vector.push_back(-3000);
        down_action();
    }else if(btn_dragon2->getBoundingBox().containsPoint(touch->getLocation())&&skill_ng6==nullptr){
        GameManager::getInstance()->exchangeNum=6;
        GameManager::getInstance()->goldLabel_vector.push_back(-1000);
        down_action();
    }else{
        down_action();
    }
    return true;
}

void ExchangeLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    
}

void ExchangeLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    
}

void ExchangeLayer::down_action(){
    auto down_action=MoveTo::create(0.3, Vec2(0,-800));
    this->runAction(Sequence::create(down_action,CallFunc::create([this](){
        this->setVisible(false);
        _eventDispatcher->removeEventListener(touchListener);
        touchListener=nullptr;
        this->removeFromParent();
    }),NULL));
}