//
//  Card.cpp
//  dungeonTiles
//
//  Created by Moon on 16/7/21.
//
//

#include "Card.hpp"
#include "ConstUtil.hpp"
#include "Scene/GameScene.hpp"

USING_NS_CC;

CardSprite* CardSprite::create(int number, int tag, Point point){
    CardSprite* card=new CardSprite();
    if(card && card->init(number,tag,point)){
        card->autorelease();
        return card;
    }
    CC_SAFE_DELETE(card);
    return nullptr;
}

bool CardSprite::init(int number, int tag, Point point){
    this->number=number;
    this->tag=tag;
    setCardState(Nochange);
    setHasMerge(false);
    setMergeCount(0);
    setHaveMergeCount(0);
    switch (tag) {
        case DRAGON_TAG:
            card=Sprite::createWithSpriteFrameName("dragon_card.png");
            setPicTag(DRAGON_TAG);
            break;
        case LIFE_TAG:
            card=Sprite::createWithSpriteFrameName("life_card.png");
            setPicTag(LIFE_TAG);
            break;
        case SWORD_TAG:
            card=Sprite::createWithSpriteFrameName("sword_card.png");
            setPicTag(SWORD_TAG);
            break;
        case GOLD_TAG:
            card=Sprite::createWithSpriteFrameName("gold_card.png");
            setPicTag(GOLD_TAG);
            break;
        default:
            log("get wrong tag");
            break;
    }
   
    
    if(tag>0){
        labelCardNumber=Label::createWithTTF(StringUtils::format("%d",number),FONT_ROUND_ZN,CARD_NUMBER_SIZE);
        labelCardNumber->setColor(COLOR3B_NUMBER);
        labelCardNumber->setPosition(Point(card->getContentSize().width/2,card->getContentSize().height*1/5));
        card->addChild(labelCardNumber);
    }else{
        card->setVisible(false);
    }
    this->addChild(card);
    this->setPosition(point);
    return true;
}

int CardSprite::getNumber(){
    return number;
}

void CardSprite::setNumber(int num){
    number=num;
    
}

void CardSprite::changeNamber(int num){
    if(num>0){
        labelCardNumber->setString(__String::createWithFormat("%i",number)->getCString());
    }else{
        labelCardNumber->setString("");
    }
}









