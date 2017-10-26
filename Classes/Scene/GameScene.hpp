//
//  GameScene.hpp
//  dungeonTiles
//
//  Created by Moon on 16/7/21.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Card/Card.hpp"
#include "SimpleRecognizer.hpp"
#include "Layer/PauseLayer.hpp"
#include "Layer/ExchangeLayer.hpp"
#include "Layer/GameOverLayer.hpp"
#include "Manager/SaveManager.hpp"
#include "SimpleAudioEngine.h"
#include "Manager/GameManager.hpp"
#include "Layer/GuideLayer.hpp"

class CardSprite;
class SimpleRecognizer;
class ExchangeLayer;
class PauseLayer;
class GameOverLayer;
class GuideLayer;

class GameScene:public cocos2d::Scene{
public:
    CREATE_FUNC(GameScene);
    ~GameScene();
private:
    virtual bool init();
    virtual void update(float delay);
    
    void initUI();
    void initData();
    
    void createCardSprite();
    void addBackgroundParticle();
    void createRandCard();
    void initRandCard();
    void newNumber(int i,int j,int num);
    bool shouldCreateCardNumber();
    void playCardParticle(std::string plistName,cocos2d::Point playPoint,int i, int j,bool isSkill);
    void playParticle(std::string plistName,cocos2d::Point startPoint,cocos2d::Point endPoint,int i,int j);
    void playCardAnimation(int i,int j);
    void playCurveParticle(std::string plistName,cocos2d::Point startPoint,cocos2d::Point endPoint);
    void playCurveParticle2(std::string plistName,cocos2d::Point startPoint,cocos2d::Point endPoint,int i,int j,bool isSkill);
    
    void setCardsMergeCount();
    void setCardsHasMerge();
    void setCardHasMergeCount();
    
    int  getLabelNumber(int tag);
    void setLabelNumber(int tag,int num);
    
    void swordLabelChange();
    void dragonLabelChange();
    void lifeLableChange();
    void goldsLabelChange();
    void socreLabelChange();
    void skillChange();
    void resetGameChange();
    
    void dragonCome(int i,int j);
    
    int returnSmallNum(int tag1,int tag2);
    
    cocos2d::Point getCountPosition(int tag);
    cocos2d::Point getPosition(int i,int j);
    
    bool doLeft();
    bool doRight();
    bool doUp();
    bool doDown();
    
    void doCheck();
    void generate_next_color();
    
    bool IsMoving();
    void setScore(int score);
    void resetGame();
    
    CC_SYNTHESIZE(int, swordNumber, SwordNumber);
    CC_SYNTHESIZE(int, dragonNumber, DragonNumber);
    
public:
    virtual bool onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch,cocos2d::Event* event);
private:
    GameManager* gameManagerInstance;
    cocos2d::Sprite* background;
    
    cocos2d::EventListenerTouchOneByOne* touchListener;
    
    ExchangeLayer* exchangeLayer;
    PauseLayer* pauseLayer;
    GameOverLayer* gameOverLayer;
    GuideLayer* guideLayer;
    
    cocos2d::Sprite* pause_btn;
    cocos2d::Sprite* exchange_btn;
    cocos2d::Sprite* help_btn;
    cocos2d::Sprite* nextColor;	
    
    cocos2d::Label* score;
    int next_tag;
    
    float background_r;
    float background_g;
    float background_b;
    
    float delayTime;
    bool background_direction_up;
    CardSprite* cardArr[4][4];
    int moveDirection=0;
    bool hasMove;
    bool hasMerge;
    
    bool isPopLayer;
    bool isGameOver;
    bool isPopGameOverLayer;
    
    bool swordActionOver;
    bool dragonActionOver;
    bool lifeActionOver;
    bool goldActionOver;
    
    bool swordAction2Over;
    bool dragonAction2Over;
    bool lifeAction2Over;
    bool goldAction2Over;
    
    bool swordAction3Over;
    bool dragonAction3Over;
    bool lifeAction3Over;
    bool goldAction3Over;
    
    CC_SYNTHESIZE(int, m_swordCount, SwordCount);
    CC_SYNTHESIZE(int, m_lifeCount, LifeCount);
    CC_SYNTHESIZE(int, m_dragonCount, DragonCount);
    CC_SYNTHESIZE(int, m_goldCount, GoldCount);
    cocos2d::Label *swordLabel,*lifeLabel,*dragonLabel,*goldLabel;
    
    
    SimpleRecognizer* recognizer;
};
#endif /* GameScene_hpp */
