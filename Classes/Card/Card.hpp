//
//  Card.hpp
//  dungeonTiles
//
//  Created by Moon on 16/7/21.
//
//

#ifndef Card_hpp
#define Card_hpp

#include <stdio.h>
#include "ConstUtil.hpp"

class CardSprite:public cocos2d::Sprite{
public:
    static CardSprite* create(int number,int tag,cocos2d::Point position);
    
    int getNumber();
    void setNumber(int num);
    void changeNamber(int num);
    CC_SYNTHESIZE(int, cardState, CardState);
    CC_SYNTHESIZE(int, mergeCount, MergeCount);
    CC_SYNTHESIZE(int, haveMergeCount, HaveMergeCount);
    CC_SYNTHESIZE(int , tag, PicTag);
    CC_SYNTHESIZE(cocos2d::Sprite*, pic,Pic );
    CC_SYNTHESIZE(bool, hasMerge, HasMerge);
    
private:
    virtual bool init(int number,int tag,cocos2d::Point position);
    
private:
    int number;
    cocos2d::Label *labelCardNumber;
    
    
    cocos2d::Sprite *card;
};
#endif /* Card_hpp */
