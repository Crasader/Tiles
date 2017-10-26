//
//  GameScene.cpp
//  dungeonTiles
//
//  Created by Moon on 16/7/21.
//
//

#include "GameScene.hpp"
#include "ConstUtil.hpp"

USING_NS_CC;
using namespace CocosDenshion;

bool GameScene::init(){
    initData();
    initUI();
    addBackgroundParticle();
    return true;
}

GameScene::~GameScene(){
    delete recognizer;
    
}

void GameScene::initData(){
    gameManagerInstance=GameManager::getInstance();
    if(SaveManager::getInstance()->getBGMOn()){
        SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACKGROUND1,true);
    }
    
    SaveManager::getInstance()->setFirstIn(false);
    
    background_direction_up=true;
    
    delayTime=0;
    
    isPopLayer=false;
    swordActionOver=false;
    dragonActionOver=false;
    lifeActionOver=false;
    goldActionOver=false;
    
    swordAction2Over=false;
    dragonAction2Over=false;
    lifeAction2Over=false;
    goldAction2Over=false;
    
    swordAction3Over=false;
    dragonAction3Over=false;
    lifeAction3Over=false;
    goldAction3Over=false;
    
    background_r=99;
    background_g=34;
    background_b=153;
    SaveManager::getInstance()->score_number=0;
    srand((unsigned)time(NULL));
}

void GameScene::initUI(){
    Size visibleSize=Director::getInstance()->getVisibleSize();
    
    background=Sprite::create(BACKGROUND_PIC);
    background->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    this->addChild(background);
    
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            auto grid=Sprite::create(GRID_PIC);
            grid->setPosition(getPosition( i, j));
            addChild(grid,3);
        }
    }
    
    pause_btn=Sprite::createWithSpriteFrameName("game_button_pause.png");
    pause_btn->setPosition(Vec2(DesignResolutionWidth-120,DesignResolutionHeight-120));
    addChild(pause_btn,3);
    
    help_btn=Sprite::createWithSpriteFrameName("game_button_help2.png");
    help_btn->setPosition(Vec2(120,DesignResolutionHeight-120));
    addChild(help_btn,3);
    
    auto score_label=Label::createWithTTF("分数",FONT_ROUND_ZN,SCORE_NUMBER_SIZE);
    score_label->setColor(COLOR3B_MENU_BG);
    score_label->setPosition(Point(visibleSize.width/2,visibleSize.height-120));
    addChild(score_label,3);
    
    score=Label::createWithTTF("0",FONT_ROUND_ZN,SCORE_NUMBER_SIZE);
    score->setColor(COLOR3B_MENU_BG);
    score->setPosition(Point(visibleSize.width/2,visibleSize.height-200));
    addChild(score,3);
    
    exchange_btn=Sprite::createWithSpriteFrameName("button_exchange.png");
    exchange_btn->setPosition(Vec2(DesignResolutionWidth-200,200));
    addChild(exchange_btn,3);
    
    auto next_label=Label::createWithTTF("下一个",FONT_ROUND_ZN,NEXT_COLOR_SIZE);
    next_label->setColor(COLOR3B_MENU_BG);
    next_label->setPosition(Point(150,250));
    addChild(next_label,3);
    
    nextColor=Sprite::createWithSpriteFrameName(NEXT_COLOR);
    addChild(nextColor,10);
    nextColor->setPosition(Vec2(150,150));
    generate_next_color();
    
    auto sword=Sprite::createWithSpriteFrameName(SWORD_PIC);
    sword->setColor(COLOR3B_SWORD_BG);
    sword->setPosition(getPosition(0, 4));
    addChild(sword,3);
    
    auto drangon=Sprite::createWithSpriteFrameName(DRAGON_PIC);
    drangon->setColor(COLOR3B_DRAGON_BG);
    drangon->setPosition(getPosition(1, 4));
    addChild(drangon,3);
    
    auto life=Sprite::createWithSpriteFrameName(LIFE_PIC );
    life->setColor(COLOR3B_LIFE_BG);
    life->setPosition(getPosition(2, 4));
    addChild(life,3);
    
    auto gold=Sprite::createWithSpriteFrameName(GOLD_PIC);
    gold->setColor(COLOR3B_GOLD_BG);
    gold->setPosition(getPosition(3, 4));
    addChild(gold,3);
    
    //卡片数目
    setSwordCount(0);
    swordLabel=Label::createWithTTF("0", FONT_ROUND_ZN, CARD_SCORE_SIZE);
    swordLabel->setPosition(getCountPosition(SWORD_TAG));
    swordLabel->setTextColor(Color4B(0,238,238,255));
    setDragonCount(0);
    dragonLabel=Label::createWithTTF("0", FONT_ROUND_ZN, CARD_SCORE_SIZE);
    dragonLabel->setPosition(getCountPosition(DRAGON_TAG));
    dragonLabel->setTextColor(Color4B(211,211,211,255));
    setLifeCount(30);
    lifeLabel=Label::createWithTTF("30",FONT_ROUND_ZN, CARD_SCORE_SIZE);
    lifeLabel->setPosition(getCountPosition(LIFE_TAG));
    lifeLabel->setTextColor(Color4B(238,59,59,255));
    setGoldCount(0);
    goldLabel=Label::createWithTTF(StringUtils::format("%d",SaveManager::getInstance()->geteGolds()),FONT_ROUND_ZN , CARD_SCORE_SIZE);
    goldLabel->setPosition(getCountPosition(GOLD_TAG));
    goldLabel->setTextColor(Color4B(255,215,0,255));
    
    addChild(swordLabel,3);
    addChild(lifeLabel,3);
    addChild(dragonLabel,3);
    addChild(goldLabel,3);
    
    initRandCard();
    
    touchListener=EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan=CC_CALLBACK_2(GameScene::onTouchBegan, this);
    touchListener->onTouchMoved=CC_CALLBACK_2(GameScene::onTouchMoved, this);
    touchListener->onTouchEnded=CC_CALLBACK_2(GameScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    	
    recognizer=new SimpleRecognizer();
    
    scheduleUpdate();
}

void GameScene::update(float delay){
    if(background_r<110&&background_r>70){
        if(background_direction_up==true) {
            background->setColor(Color3B(background_r+BACKGROUND_EXCHANGE_SPEED*delay,background_g+BACKGROUND_EXCHANGE_SPEED*delay/3.75,background_b+BACKGROUND_EXCHANGE_SPEED*delay*1.1));
            background_r+=BACKGROUND_EXCHANGE_SPEED*delay;
            background_g+=BACKGROUND_EXCHANGE_SPEED*delay/3.75;
            background_b+=BACKGROUND_EXCHANGE_SPEED*delay*1.3;
        }else{
            background->setColor(Color3B(background_r-BACKGROUND_EXCHANGE_SPEED*delay,background_g-BACKGROUND_EXCHANGE_SPEED*delay/3.75,background_b-BACKGROUND_EXCHANGE_SPEED*delay*1.1));
            background_r-=BACKGROUND_EXCHANGE_SPEED*delay;
            background_g-=BACKGROUND_EXCHANGE_SPEED*delay/3.75;
            background_b-=BACKGROUND_EXCHANGE_SPEED*delay*1.3;
            
        }
    }else if(background_r>=110){
        background_direction_up=false;
        background->setColor(Color3B(background_r-BACKGROUND_EXCHANGE_SPEED*delay,background_g-BACKGROUND_EXCHANGE_SPEED*delay/3.75,background_b-BACKGROUND_EXCHANGE_SPEED*delay*1.1));
        background_r-=BACKGROUND_EXCHANGE_SPEED*delay;
        background_g-=BACKGROUND_EXCHANGE_SPEED*delay/3.75;
        background_b-=BACKGROUND_EXCHANGE_SPEED*delay*1.3;
        
    }else if(background_r<=70){
        background_direction_up=true;
        background->setColor(Color3B(background_r+BACKGROUND_EXCHANGE_SPEED*delay,background_g+BACKGROUND_EXCHANGE_SPEED*delay/3.75,background_b+BACKGROUND_EXCHANGE_SPEED*delay*1.1));
        background_r+=BACKGROUND_EXCHANGE_SPEED*delay;
        background_g+=BACKGROUND_EXCHANGE_SPEED*delay/3.75;
        background_b+=BACKGROUND_EXCHANGE_SPEED*delay*1.3;
        
    }
    
    swordLabelChange();
    dragonLabelChange();
    lifeLableChange();
    goldsLabelChange();
    socreLabelChange();
    skillChange();
    resetGameChange();
    
    if(getLabelNumber(LIFE_TAG)==0){
        isGameOver=true;
        gameManagerInstance->isLife0=true;
    }
    
    if(isGameOver&&!isPopGameOverLayer){
        _eventDispatcher->removeEventListener(touchListener);
        touchListener=nullptr;
        SimpleAudioEngine::getInstance()->stopBackgroundMusic(AUDIO_BACKGROUND1);
        delayTime+=delay;
        if(delayTime>2){
            if(gameManagerInstance->score_vector.size()==0&&gameManagerInstance->goldLabel_vector.size()==0&&gameManagerInstance->lifeLabel_vector.size()==0&&gameManagerInstance->swordLabel_vector.size()==0&&gameManagerInstance->dragonLabel_vector.size()==0){
                isPopGameOverLayer=true;
                SaveManager::getInstance()->setGolds(getLabelNumber(GOLD_TAG));
                SaveManager::getInstance()->addPoint(SaveManager::getInstance()->score_number);
                gameOverLayer=GameOverLayer::create();
                addChild(gameOverLayer,20);
            }
        }
    }
    
}


bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    Point beginPoint=touch->getLocation();
    
    if(pause_btn->getBoundingBox().containsPoint(beginPoint)){
        isPopLayer=true;
        pauseLayer=PauseLayer::create();
        addChild(pauseLayer,20);
    }else if(exchange_btn->getBoundingBox().containsPoint(beginPoint)){
        isPopLayer=true;
        exchangeLayer=ExchangeLayer::create();
        addChild(exchangeLayer,20);
        auto up_action=MoveTo::create(0.3, Vec2(0,0));
        exchangeLayer->setPosition(Vec2(0,-800));
        exchangeLayer->runAction(up_action);
    }else if(help_btn->getBoundingBox().containsPoint(beginPoint)){
        isPopLayer=true;
        guideLayer=GuideLayer::create();
        addChild(guideLayer,20);
    }
    recognizer->beginPoint(beginPoint);
    return true;
}

void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    Point pos=touch->getLocation();
    recognizer->movePoint(pos);
}

void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    
    Point pos=touch->getLocation();
    SimpleGestures rtn=recognizer->endPoint(pos);
    
    if(!isPopLayer&&gameManagerInstance->swordLabel_vector.size()==0&&gameManagerInstance->dragonLabel_vector.size()==0&&gameManagerInstance->lifeLabel_vector.size()==0&&gameManagerInstance->goldLabel_vector.size()==0){
        
        switch (rtn) {
            case SimpleGesturesLeft:
                moveDirection=1;
                hasMove=doLeft();
                schedule([this](float delay){
                    if(!this->IsMoving()){
                        if(hasMove){
                            if(SaveManager::getInstance()->getSoundOn()){
                                SimpleAudioEngine::getInstance()->playEffect(AUDIO_SWIPE);
                            }
                            if(hasMerge){
                                if(SaveManager::getInstance()->getSoundOn()){
                                    SimpleAudioEngine::getInstance()->playEffect(AUDIO_SHOOT);
                                }
                            }
                            this->createRandCard();
                            this->generate_next_color();
                            this->doCheck();
                        }
                        setCardsMergeCount();
                        setCardsHasMerge();
                        setCardHasMergeCount();
                        this->unschedule("gameRun");
                    }
                },"gameRun");
                
                break;
            case SimpleGesturesRight:
                moveDirection=2;
                hasMove=doRight();
                schedule([this](float delay){
                    if(!this->IsMoving()){
                        if(hasMove){
                            if(SaveManager::getInstance()->getSoundOn()){
                                SimpleAudioEngine::getInstance()->playEffect(AUDIO_SWIPE);
                            }
                            if(hasMerge){
                                if(SaveManager::getInstance()->getSoundOn()){
                                    SimpleAudioEngine::getInstance()->playEffect(AUDIO_SHOOT);
                                }
                            }
                            this->createRandCard();
                            this->generate_next_color();
                            this->doCheck();
                        }
                        setCardsMergeCount();
                        setCardsHasMerge();
                        setCardHasMergeCount();
                        this->unschedule("gameRun");
                    }
                },"gameRun");
                break;
            case SimpleGesturesUp:
                moveDirection=3;
                hasMove=doUp();
                schedule([this](float delay){
                    if(!this->IsMoving()){
                        if(hasMove){
                            if(SaveManager::getInstance()->getSoundOn()){
                                SimpleAudioEngine::getInstance()->playEffect(AUDIO_SWIPE);
                            }
                            if(hasMerge){
                                if(SaveManager::getInstance()->getSoundOn()){
                                    SimpleAudioEngine::getInstance()->playEffect(AUDIO_SHOOT);
                                }
                            }
                            this->createRandCard();
                            this->generate_next_color();
                            this->doCheck();
                        }
                        setCardsMergeCount();
                        setCardsHasMerge();
                        setCardHasMergeCount();
                        this->unschedule("gameRun");
                    }
                },"gameRun");
                break;
            case SimpleGesturesDown:
                moveDirection=4;
                hasMove=doDown();
                schedule([this](float delay){
                    if(!this->IsMoving()){
                        if(hasMove){
                            if(SaveManager::getInstance()->getSoundOn()){
                                SimpleAudioEngine::getInstance()->playEffect(AUDIO_SWIPE);
                            }
                            if(hasMerge){
                                if(SaveManager::getInstance()->getSoundOn()){
                                    SimpleAudioEngine::getInstance()->playEffect(AUDIO_SHOOT);
                                }
                            }
                            this->createRandCard();
                            this->generate_next_color();
                            this->doCheck();
                        }
                        setCardsMergeCount();
                        setCardsHasMerge();
                        setCardHasMergeCount();
                        this->unschedule("gameRun");
                    }
                },"gameRun");
                break;
            case SimpleGesturesNotsupport:
            case SimpleGesturesError:
                log("not support or error touch,use geometricRecoginzer!");
                break;
            default:
                break;
        }

    }
    isPopLayer=false;
}



void GameScene::createRandCard(){
    srand((unsigned)time(NULL));
    while(1){
        int i=CCRANDOM_0_1()*4;
        int number=CCRANDOM_0_1()*3+1;
        if(next_tag==DRAGON_TAG){
            if(getLabelNumber(LIFE_TAG)>200&&getLabelNumber(SWORD_TAG<200)){
                if(CCRANDOM_0_1()>0.9){
                    gameManagerInstance->isDragonCome=true;
                    number=CCRANDOM_0_1()>0.5?0.3*getLabelNumber(LIFE_TAG)+CCRANDOM_0_1()*10:0.2*getLabelNumber(LIFE_TAG)+CCRANDOM_0_1()*10;
                }
            }else if(getLabelNumber(LIFE_TAG)<200&&getLabelNumber(SWORD_TAG)>200){
                if(CCRANDOM_0_1()>0.9){
                    gameManagerInstance->isDragonCome=true;
                   number=CCRANDOM_0_1()>0.5?0.3*getLabelNumber(SWORD_TAG)+CCRANDOM_0_1()*10:0.2*getLabelNumber(SWORD_TAG)+CCRANDOM_0_1()*10;
                }
            }else if(getLabelNumber(LIFE_TAG)>200&&getLabelNumber(SWORD_TAG)>200){
                if(CCRANDOM_0_1()>0.9){
                    gameManagerInstance->isDragonCome=true;
                    number=CCRANDOM_0_1()>0.5?0.3*returnSmallNum(SWORD_TAG, LIFE_TAG)+CCRANDOM_0_1()*10:0.2*returnSmallNum(SWORD_TAG, LIFE_TAG)+CCRANDOM_0_1()*10;
                }
            }
        }
        if(moveDirection==1){
            if(cardArr[3][i]==NULL){
                cardArr[3][i]=CardSprite::create(number, next_tag,  getPosition(3, i));
                addChild(cardArr[3][i],10);
                if(gameManagerInstance->isDragonCome==true){
                    dragonCome(3,i);
                }
                break;
            }
            
        }else if(moveDirection==2){
            if(cardArr[0][i]==NULL){
                cardArr[0][i]=CardSprite::create(number, next_tag,  getPosition(0, i));
                addChild(cardArr[0][i],10);
                if(gameManagerInstance->isDragonCome==true){
                    dragonCome(0,i);
                }
                break;
            }
            
        }else if(moveDirection==3){
            if(cardArr[i][0]==NULL){
                cardArr[i][0]=CardSprite::create(number, next_tag, getPosition(i, 0));
                addChild(cardArr[i][0],10);
                if(gameManagerInstance->isDragonCome==true){
                    dragonCome(i,0);
                }
                break;
            }
        }else if(moveDirection==4){
            if(cardArr[i][3]==NULL){
                cardArr[i][3]=CardSprite::create(number, next_tag,  getPosition(i, 3));
                addChild(cardArr[i][3],10);
                if(gameManagerInstance->isDragonCome==true){
                    dragonCome(i,3);
                }
                break;
            }
        }
    }
}

void GameScene::initRandCard(){
    srand((unsigned)time(NULL));
    
    int i=0;
    while(i<3){
        int x=CCRANDOM_0_1()*4;
        int y=CCRANDOM_0_1()*4;
        int tag=CCRANDOM_0_1()*4+1;
        int number=CCRANDOM_0_1()*3+1;
        if(cardArr[x][y]==NULL){
            cardArr[x][y]=CardSprite::create(number,tag , getPosition(x, y));
            addChild(cardArr[x][y],10);
            ++i;
        }
    }
}

Point GameScene::getPosition(int i, int j){
    float px=i*CELL_SIZE+180;
    float py=(j+2)*CELL_SIZE+120;
    return Point(px,py);
}

Point GameScene::getCountPosition(int tag){
    switch (tag) {
        case SWORD_TAG:
            return Point(180,6*CELL_SIZE+120-72);
            break;
        case DRAGON_TAG:
            return Point(180+CELL_SIZE,6*CELL_SIZE+120-72);
            break;
        case LIFE_TAG:
            return Point(180+2*CELL_SIZE,6*CELL_SIZE+120-72);
            break;
        case GOLD_TAG:
            return Point(180+3*CELL_SIZE,6*CELL_SIZE+120-72);
            break;
        default:
            return Point(0,0);
            break;
    }
}

bool GameScene::doLeft(){
    bool isMove=false;
    hasMerge=false;
    for(int y=0;y<4;y++){
        for(int x=0;x<4;x++){
            for(int x1=x+1;x1<4;x1++){
                if(cardArr[x1][y]!=NULL){
                    if(cardArr[x][y]==NULL){
                        cardArr[x][y]=CardSprite::create(cardArr[x1][y]->getNumber(),cardArr[x1][y]->getPicTag() , getPosition(x1,y));
                        cardArr[x][y]->setCardState(CardState::Move);
                        cardArr[x1][y]->removeFromParent();
                        cardArr[x1][y]=NULL;
                        addChild(cardArr[x][y],10);
                        MoveBy* left=MoveBy::create(0.2, Vec2(-(x1-x)*CELL_SIZE,0));
                        cardArr[x][y]->runAction(Sequence::create(left,CallFunc::create([this,x,y](){
                            cardArr[x][y]->setCardState(CardState::Nochange);
                        }), NULL));
                        isMove=true;
                        continue;
                    }else if(cardArr[x][y]->getPicTag()==cardArr[x1][y]->getPicTag()){
                        hasMerge=true;
                        auto card=CardSprite::create(cardArr[x1][y]->getNumber(),cardArr[x1][y]->getPicTag() , getPosition(x1, y));
                        cardArr[x][y]->setCardState(CardState::Move);
                        
                        cardArr[x1][y]->removeFromParent();
                        cardArr[x1][y]=NULL;
                        addChild(card,10);
                        
                        switch (cardArr[x][y]->getMergeCount()) {
                            case 0:
                                cardArr[x][y]->setMergeCount(1);
                                break;
                            case 1:
                                cardArr[x][y]->setMergeCount(2);
                                break;
                            case 2:
                                cardArr[x][y]->setMergeCount(3);
                                break;
                            default:
                                break;
                        }
                        cardArr[x][y]->setNumber(card->getNumber()+cardArr[x][y]->getNumber());
                        MoveBy* left=MoveBy::create(0.2, Vec2(-CELL_SIZE*(x1-x),0));
                        card->runAction(Sequence::create(left,CallFunc::create([this,card,x,y,x1]() mutable{
                            cardArr[x][y]->changeNamber(cardArr[x][y]->getNumber());
                            
                            auto tag=cardArr[x][y]->getPicTag();
                            switch (tag) {
                                case DRAGON_TAG:
                                    this->playCardParticle(PARTICLE_DRAGON_CARD_BG, getPosition(x, y),x,y,false);
                                    playCardAnimation(x, y);
                                    gameManagerInstance->dragonLabel_vector.push_back(cardArr[x][y]->getMergeCount()==1?cardArr[x][y]->getNumber():card->getNumber());
                                    this->playCurveParticle2(PARTICLE_DRAGON_CURVE, getPosition(x, y), getPosition(1, 4), x, y,false);
                                    break;
                                case LIFE_TAG:
                                    this->playCardParticle(PARTICLE_LIFE_CARD_BG, getPosition(x, y),x,y,false);
                                    playCardAnimation(x, y);
                                    gameManagerInstance->lifeLabel_vector.push_back(cardArr[x][y]->getMergeCount()==1?cardArr[x][y]->getNumber():card->getNumber());
                                    this->playCurveParticle2(PARTICLE_LIFE_CURVE, getPosition(x, y), getPosition(2, 4), x, y,false);
                                    break;
                                case GOLD_TAG:
                                    this->playCardParticle(PARTICLE_GOLD_CARD_BG, getPosition(x, y),x,y,false);
                                    playCardAnimation(x, y);
                                    gameManagerInstance->goldLabel_vector.push_back(cardArr[x][y]->getMergeCount()==1?cardArr[x][y]->getNumber():card->getNumber());
                                    this->playCurveParticle2(PARTICLE_GOLD_CURVE, getPosition(x, y), getPosition(3, 4), x, y,false);
                                    break;
                                case SWORD_TAG:
                                    this->playCardParticle(PARTICLE_SWORD_CARD_BG, getPosition(x, y),x,y,false);
                                    playCardAnimation(x, y);
                                    gameManagerInstance->swordLabel_vector.push_back(cardArr[x][y]->getMergeCount()==1?cardArr[x][y]->getNumber():card->getNumber());
                                    this->playCurveParticle2(PARTICLE_SWORD_CURVE, getPosition(x, y), getPosition(0, 4), x, y,false);
                                    break;
                                default:
                                    break;
                                    
                            }
                            cardArr[x][y]->setCardState(CardState::Nochange);
                            card->removeFromParent();
                            card=nullptr;
                        }) ,NULL));
                        isMove=true;
                        continue;
                    }
                    break;
                }
            }
        }
    }
    return isMove;
}

bool GameScene::doRight(){
    bool isMove=false;
    hasMerge=false;
    for(int y=0;y<4;y++){
        for(int x=3;x>=0;x--){
            for(int x1=x-1;x1>=0;x1--){
                if(cardArr[x1][y]!=NULL){
                    if(cardArr[x][y]==NULL){
                        cardArr[x][y]=CardSprite::create(cardArr[x1][y]->getNumber(),cardArr[x1][y]->getPicTag() , getPosition(x1,y));
                        cardArr[x][y]->setCardState(CardState::Move);
                        cardArr[x1][y]->removeFromParent();
                        cardArr[x1][y]=NULL;
                        addChild(cardArr[x][y],10);
                        MoveBy* left=MoveBy::create(0.2, Vec2(-(x1-x)*CELL_SIZE,0));
                        cardArr[x][y]->runAction(Sequence::create(left,CallFunc::create([this,x,y](){
                            cardArr[x][y]->setCardState(CardState::Nochange);
                        }), NULL));
                        isMove=true;
                        continue;
                    }else if(cardArr[x][y]->getPicTag()==cardArr[x1][y]->getPicTag()){
                        hasMerge=true;
                        auto card=CardSprite::create(cardArr[x1][y]->getNumber(),cardArr[x1][y]->getPicTag() , getPosition(x1, y));
                        cardArr[x][y]->setCardState(CardState::Move);
                        
                        cardArr[x1][y]->removeFromParent();
                        cardArr[x1][y]=NULL;
                        addChild(card,10);
                        
                        switch (cardArr[x][y]->getMergeCount()) {
                            case 0:
                                cardArr[x][y]->setMergeCount(1);
                                break;
                            case 1:
                                cardArr[x][y]->setMergeCount(2);
                                break;
                            case 2:
                                cardArr[x][y]->setMergeCount(3);
                                break;
                            default:
                                break;
                        }
                        cardArr[x][y]->setNumber(card->getNumber()+cardArr[x][y]->getNumber());
                        MoveBy* left=MoveBy::create(0.2, Vec2(-CELL_SIZE*(x1-x),0));
                        card->runAction(Sequence::create(left,CallFunc::create([this,card,x,y,x1]() mutable{
                            cardArr[x][y]->changeNamber(cardArr[x][y]->getNumber());
                            
                            auto tag=cardArr[x][y]->getPicTag();
                            switch (tag) {
                                case DRAGON_TAG:
                                    this->playCardParticle(PARTICLE_DRAGON_CARD_BG, getPosition(x, y),x,y,false);
                                    playCardAnimation(x, y);
                                    gameManagerInstance->dragonLabel_vector.push_back(cardArr[x][y]->getMergeCount()==1?cardArr[x][y]->getNumber():card->getNumber());
                                    this->playCurveParticle2(PARTICLE_DRAGON_CURVE, getPosition(x, y), getPosition(1, 4), x, y,false);
                                    break;
                                case LIFE_TAG:
                                    this->playCardParticle(PARTICLE_LIFE_CARD_BG, getPosition(x, y),x,y,false);
                                    playCardAnimation(x, y);
                                    gameManagerInstance->lifeLabel_vector.push_back(cardArr[x][y]->getMergeCount()==1?cardArr[x][y]->getNumber():card->getNumber());
                                    this->playCurveParticle2(PARTICLE_LIFE_CURVE, getPosition(x, y), getPosition(2, 4), x, y,false);
                                    break;
                                case GOLD_TAG:
                                    this->playCardParticle(PARTICLE_GOLD_CARD_BG, getPosition(x, y),x,y,false);
                                    playCardAnimation(x, y);
                                    gameManagerInstance->goldLabel_vector.push_back(cardArr[x][y]->getMergeCount()==1?cardArr[x][y]->getNumber():card->getNumber());
                                    this->playCurveParticle2(PARTICLE_GOLD_CURVE, getPosition(x, y), getPosition(3, 4), x, y,false);
                                    break;
                                case SWORD_TAG:
                                    this->playCardParticle(PARTICLE_SWORD_CARD_BG, getPosition(x, y),x,y,false);
                                    playCardAnimation(x, y);
                                    gameManagerInstance->swordLabel_vector.push_back(cardArr[x][y]->getMergeCount()==1?cardArr[x][y]->getNumber():card->getNumber());
                                    this->playCurveParticle2(PARTICLE_SWORD_CURVE, getPosition(x, y), getPosition(0, 4), x, y,false);
                                    break;
                                default:
                                    break;
                                    
                            }
                            cardArr[x][y]->setCardState(CardState::Nochange);
                            card->removeFromParent();
                            card=nullptr;
                        }) ,NULL));
                        isMove=true;
                        continue;
                    }
                    break;
                }
            }
        }
    }
    return isMove;
    
}

bool GameScene::doUp(){
    bool isMove=false;
    hasMerge=false;
    for(int x=0;x<4;x++){
        for(int y=3;y>=0;y--){
            for(int y1=y-1;y1>=0;y1--){
                if(cardArr[x][y1]!=NULL){
                    if(cardArr[x][y]==NULL){
                        cardArr[x][y]=CardSprite::create(cardArr[x][y1]->getNumber(),cardArr[x][y1]->getPicTag() , getPosition(x,y1));
                        cardArr[x][y]->setCardState(CardState::Move);
                        cardArr[x][y1]->removeFromParent();
                        cardArr[x][y1]=NULL;
                        addChild(cardArr[x][y],10);
                        MoveBy* left=MoveBy::create(0.2, Vec2(0,-(y1-y)*CELL_SIZE));
                        cardArr[x][y]->runAction(Sequence::create(left,CallFunc::create([this,x,y](){
                            cardArr[x][y]->setCardState(CardState::Nochange);
                        }), NULL));
                        isMove=true;
                        continue;
                    }else if(cardArr[x][y]->getPicTag()==cardArr[x][y1]->getPicTag()){
                        hasMerge=true;
                        auto card=CardSprite::create(cardArr[x][y1]->getNumber(),cardArr[x][y1]->getPicTag() , getPosition(x, y1));
                        cardArr[x][y]->setCardState(CardState::Move);
                        
                        cardArr[x][y1]->removeFromParent();
                        cardArr[x][y1]=NULL;
                        addChild(card,10);
                        
                        switch (cardArr[x][y]->getMergeCount()) {
                            case 0:
                                cardArr[x][y]->setMergeCount(1);
                                break;
                            case 1:
                                cardArr[x][y]->setMergeCount(2);
                                break;
                            case 2:
                                cardArr[x][y]->setMergeCount(3);
                                break;
                            default:
                                break;
                        }
                        cardArr[x][y]->setNumber(card->getNumber()+cardArr[x][y]->getNumber());
                        MoveBy* left=MoveBy::create(0.2, Vec2(0,-(y1-y)*CELL_SIZE));
                        card->runAction(Sequence::create(left,CallFunc::create([this,card,x,y]() mutable{
                            cardArr[x][y]->changeNamber(cardArr[x][y]->getNumber());
                            
                            auto tag=cardArr[x][y]->getPicTag();
                            switch (tag) {
                                case DRAGON_TAG:
                                    this->playCardParticle(PARTICLE_DRAGON_CARD_BG, getPosition(x, y),x,y,false);
                                    playCardAnimation(x, y);
                                    gameManagerInstance->dragonLabel_vector.push_back(cardArr[x][y]->getMergeCount()==1?cardArr[x][y]->getNumber():card->getNumber());
                                    this->playCurveParticle2(PARTICLE_DRAGON_CURVE, getPosition(x, y), getPosition(1, 4), x, y,false);
                                    break;
                                case LIFE_TAG:
                                    this->playCardParticle(PARTICLE_LIFE_CARD_BG, getPosition(x, y),x,y,false);
                                    playCardAnimation(x, y);
                                    gameManagerInstance->lifeLabel_vector.push_back(cardArr[x][y]->getMergeCount()==1?cardArr[x][y]->getNumber():card->getNumber());
                                    this->playCurveParticle2(PARTICLE_LIFE_CURVE, getPosition(x, y), getPosition(2, 4), x, y,false);
                                    break;
                                case GOLD_TAG:
                                    this->playCardParticle(PARTICLE_GOLD_CARD_BG, getPosition(x, y),x,y,false);
                                    playCardAnimation(x, y);
                                    gameManagerInstance->goldLabel_vector.push_back(cardArr[x][y]->getMergeCount()==1?cardArr[x][y]->getNumber():card->getNumber());
                                    this->playCurveParticle2(PARTICLE_GOLD_CURVE, getPosition(x, y), getPosition(3, 4), x, y,false);
                                    break;
                                case SWORD_TAG:
                                    this->playCardParticle(PARTICLE_SWORD_CARD_BG, getPosition(x, y),x,y,false);
                                    playCardAnimation(x, y);
                                    gameManagerInstance->swordLabel_vector.push_back(cardArr[x][y]->getMergeCount()==1?cardArr[x][y]->getNumber():card->getNumber());
                                    this->playCurveParticle2(PARTICLE_SWORD_CURVE, getPosition(x, y), getPosition(0, 4), x, y,false);
                                    break;
                                default:
                                    break;
                                    
                            }
                            cardArr[x][y]->setCardState(CardState::Nochange);
                            card->removeFromParent();
                            card=nullptr;
                        }) ,NULL));
                        isMove=true;
                        continue;
                    }
                    break;
                }
            }
        }
    }
    return isMove;
}

bool GameScene::doDown(){
    bool isMove=false;
    hasMerge=false;
    for(int x=0;x<4;x++){
        for(int y=0;y<4;y++){
            for(int y1=y+1;y1<4;y1++){
                if(cardArr[x][y1]!=NULL){
                    if(cardArr[x][y]==NULL){
                        cardArr[x][y]=CardSprite::create(cardArr[x][y1]->getNumber(),cardArr[x][y1]->getPicTag() , getPosition(x,y1));
                        cardArr[x][y]->setCardState(CardState::Move);
                        cardArr[x][y1]->removeFromParent();
                        cardArr[x][y1]=NULL;
                        addChild(cardArr[x][y],10);
                        MoveBy* left=MoveBy::create(0.2, Vec2(0,-(y1-y)*CELL_SIZE));
                        cardArr[x][y]->runAction(Sequence::create(left,CallFunc::create([this,x,y](){
                            cardArr[x][y]->setCardState(CardState::Nochange);
                        }), NULL));
                        isMove=true;
                        continue;
                    }else if(cardArr[x][y]->getPicTag()==cardArr[x][y1]->getPicTag()){
                        hasMerge=true;
                        auto card=CardSprite::create(cardArr[x][y1]->getNumber(),cardArr[x][y1]->getPicTag() , getPosition(x, y1));
                        cardArr[x][y]->setCardState(CardState::Move);
                        
                        cardArr[x][y1]->removeFromParent();
                        cardArr[x][y1]=NULL;
                        addChild(card,10);
                        
                        switch (cardArr[x][y]->getMergeCount()) {
                            case 0:
                                cardArr[x][y]->setMergeCount(1);
                                break;
                            case 1:
                                cardArr[x][y]->setMergeCount(2);
                                break;
                            case 2:
                                cardArr[x][y]->setMergeCount(3);
                                break;
                            default:
                                break;
                        }
                        cardArr[x][y]->setNumber(card->getNumber()+cardArr[x][y]->getNumber());
                        MoveBy* left=MoveBy::create(0.2, Vec2(0,-(y1-y)*CELL_SIZE));
                        card->runAction(Sequence::create(left,CallFunc::create([this,card,x,y]() mutable{
                            cardArr[x][y]->changeNamber(cardArr[x][y]->getNumber());
                            
                            auto tag=cardArr[x][y]->getPicTag();
                            switch (tag) {
                                case DRAGON_TAG:
                                    this->playCardParticle(PARTICLE_DRAGON_CARD_BG, getPosition(x, y),x,y,false);
                                    playCardAnimation(x, y);
                                    gameManagerInstance->dragonLabel_vector.push_back(cardArr[x][y]->getMergeCount()==1?cardArr[x][y]->getNumber():card->getNumber());
                                    this->playCurveParticle2(PARTICLE_DRAGON_CURVE, getPosition(x, y), getPosition(1, 4), x, y,false);
                                    break;
                                case LIFE_TAG:
                                    this->playCardParticle(PARTICLE_LIFE_CARD_BG, getPosition(x, y),x,y,false);
                                    playCardAnimation(x, y);
                                    gameManagerInstance->lifeLabel_vector.push_back(cardArr[x][y]->getMergeCount()==1?cardArr[x][y]->getNumber():card->getNumber());
                                    this->playCurveParticle2(PARTICLE_LIFE_CURVE, getPosition(x, y), getPosition(2, 4), x, y,false);
                                    break;
                                case GOLD_TAG:
                                    this->playCardParticle(PARTICLE_GOLD_CARD_BG, getPosition(x, y),x,y,false);
                                    playCardAnimation(x, y);
                                    gameManagerInstance->goldLabel_vector.push_back(cardArr[x][y]->getMergeCount()==1?cardArr[x][y]->getNumber():card->getNumber());
                                    this->playCurveParticle2(PARTICLE_GOLD_CURVE, getPosition(x, y), getPosition(3, 4), x, y,false);
                                    break;
                                case SWORD_TAG:
                                    this->playCardParticle(PARTICLE_SWORD_CARD_BG, getPosition(x, y),x,y,false);
                                    playCardAnimation(x, y);
                                    gameManagerInstance->swordLabel_vector.push_back(cardArr[x][y]->getMergeCount()==1?cardArr[x][y]->getNumber():card->getNumber());
                                    this->playCurveParticle2(PARTICLE_SWORD_CURVE, getPosition(x, y), getPosition(0, 4), x, y,false);
                                    break;
                                default:
                                    break;
                                    
                            }
                            cardArr[x][y]->setCardState(CardState::Nochange);
                            card->removeFromParent();
                            card=nullptr;
                        }) ,NULL));
                        isMove=true;
                        continue;
                    }
                    break;
                }
            }
        }
    }
    return isMove;
}

bool GameScene::IsMoving(){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(cardArr[i][j]!=NULL){
                if(cardArr[i][j]->getCardState()!=Nochange){
                    return true;
                }
            }
        }
    }
    return false;
}



void GameScene::addBackgroundParticle(){
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

void GameScene::playCardParticle(std::string plistName, cocos2d::Point playPoint,int i,int j,bool isSkill){
    if(!isSkill){
        auto mergeCount=cardArr[i][j]->getMergeCount();
        if(mergeCount==1){
            ParticleSystem* particleSystem_card=ParticleSystemQuad::create(plistName);
            particleSystem_card->retain();
            
            ParticleBatchNode *batch=ParticleBatchNode::createWithTexture(particleSystem_card->getTexture());
            batch->addChild(particleSystem_card);
            addChild(batch,11);
            
            particleSystem_card->setPosition(playPoint);
            particleSystem_card->release();
            particleSystem_card->setAutoRemoveOnFinish(true);
        }else{
            auto tag=cardArr[i][j]->getPicTag();
            auto fadeOut=FadeOut::create(0.3);
            cardArr[i][j]->runAction(Sequence::create(fadeOut,CallFunc::create([this,i,j](){
                cardArr[i][j]->removeFromParent();
                cardArr[i][j]=NULL;
            }),NULL));
            ParticleSystem* particleSystem_broken;
            if(tag==DRAGON_TAG){
                particleSystem_broken=ParticleSystemQuad::create(PARTICLE_DRAGON_BROKEN);
            }else if(tag==LIFE_TAG){
                particleSystem_broken=ParticleSystemQuad::create(PARTICLE_LIFE_BROKEN);
            }else if(tag==SWORD_TAG){
                particleSystem_broken=ParticleSystemQuad::create(PARTICLE_SWORD_BROKEN);
            }else if(tag==GOLD_TAG){
                particleSystem_broken=ParticleSystemQuad::create(PARTICLE_GOLD_BROKEN);
            }
            particleSystem_broken->retain();
            
            addChild(particleSystem_broken,11);
            
            particleSystem_broken->setPosition(playPoint);
            particleSystem_broken->release();
            particleSystem_broken->setAutoRemoveOnFinish(true);
            
        }
    }else{
        auto fadeOut=FadeOut::create(0.3);
        cardArr[i][j]->runAction(Sequence::create(fadeOut,CallFunc::create([this,i,j,playPoint](){
            cardArr[i][j]->removeFromParent();
            cardArr[i][j]=NULL;
            ParticleSystem* particleSystem_broken=ParticleSystemQuad::create(PARTICLE_DRAGON_BROKEN);
            particleSystem_broken->retain();
            
            addChild(particleSystem_broken,11);
            
            particleSystem_broken->setPosition(playPoint);
            particleSystem_broken->release();
            particleSystem_broken->setAutoRemoveOnFinish(true);
        }),NULL));
        
        
    }
}

void GameScene::playCardAnimation(int i,int j){
    if(!cardArr[i][j]->getHasMerge()){
        cardArr[i][j]->setHasMerge(true);
        auto card_tag=cardArr[i][j]->getPicTag();
        auto number=cardArr[i][j]->getNumber();
        std::stringstream stream;
        if(cardArr[i][j]->getMergeCount()==1){
            
        }else if(cardArr[i][j]->getMergeCount()==2){
            number*=2;
        }else if(cardArr[i][j]->getMergeCount()==3){
            number*=3;
        }
        gameManagerInstance->score_vector.push_back(number*100);
        stream<<number;
        auto label=Label::createWithSystemFont("+"+stream.str()+"00", "Consolas", 100);
        label->setPosition(getPosition(i, j));
        
        Sprite* card_temp;
        switch (card_tag) {
            case DRAGON_TAG:
                card_temp=Sprite::createWithSpriteFrameName(DRAGON_PIC);
                label->setTextColor(Color4B(211,211,211,255));
                break;
            case GOLD_TAG:
                card_temp=Sprite::createWithSpriteFrameName(GOLD_PIC);
                label->setTextColor(Color4B(255,215,0,255));
                break;
            case SWORD_TAG:
                card_temp=Sprite::createWithSpriteFrameName(SWORD_PIC);
                label->setTextColor(Color4B(0,238,238,255));
                break;
            case LIFE_TAG:
                card_temp=Sprite::createWithSpriteFrameName(LIFE_PIC);
                label->setTextColor(Color4B(238,59,59,255));
            default:
                break;
        }
        addChild(card_temp,11);
        addChild(label,11);
        
        auto move=MoveBy::create(0.8, Vec2(0,200));
        auto fadeTo=FadeTo::create(0.8, GLubyte(50));
        label->runAction(Sequence::create(Spawn::create(move,fadeTo, NULL),
                                          CallFunc::create([label](){
            label->removeFromParent();
        }),NULL));
        card_temp->setColor(Color3B(58,17,68));
        card_temp->setPosition(getPosition(i, j));
        ScaleTo* large=ScaleTo::create(0.3, 1.5);
        FadeOut* fadeOut=FadeOut::create(0.5);
        card_temp->runAction(Spawn::create(large,fadeOut, NULL));
    }
}

void GameScene::setCardsMergeCount(){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(cardArr[i][j]!=NULL){
                cardArr[i][j]->setMergeCount(0);
            }
        }
    }
}

void GameScene::setCardsHasMerge(){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(cardArr[i][j]!=NULL){
                cardArr[i][j]->setHasMerge(false);
            }
        }
    }
}

void GameScene::setCardHasMergeCount(){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(cardArr[i][j]!=NULL){
                cardArr[i][j]->setHaveMergeCount(0);
            }
        }
    }
}


void GameScene::playCurveParticle(std::string plistName, cocos2d::Point startPoint, cocos2d::Point endPoint){
    float angle=60;
    float height=100;
    float radian=angle*3.14159/180.0;
    
    float q1x = startPoint.x+(endPoint.x - startPoint.x)/4.0;
    Point q1 = Point(q1x, height + startPoint.y+cos(radian)*q1x);
    float q2x = startPoint.x + (endPoint.x - startPoint.x)/2.0;
    Point q2 = Point(q2x, height + startPoint.y+cos(radian)*q2x);
    
    ccBezierConfig cfg;
    cfg.controlPoint_1 = q1;
    cfg.controlPoint_2 = q2;
    cfg.endPosition = endPoint;
    
    auto bezierTo=BezierTo::create(0.8, cfg);
    
    ParticleSystem* particleSystem_curve=ParticleSystemQuad::create(plistName);
    particleSystem_curve->retain();
    
    addChild(particleSystem_curve,12);
    
    
    particleSystem_curve->setPosition(startPoint);
    particleSystem_curve->runAction(Sequence::create(bezierTo,CallFunc::create([this,plistName,endPoint](){
        if(plistName==PARTICLE_SWORD_CURVE){
            swordAction3Over=true;
            if (SaveManager::getInstance()->getSoundOn()) {
                SimpleAudioEngine::getInstance()->playEffect(AUDIO_SWORD_ATTACK);
            }
            ParticleSystem* particleSystem_smoke=ParticleSystemQuad::create(PARTICLE_DRAGON_SMOKE);
            particleSystem_smoke->retain();
            particleSystem_smoke->setPosition(endPoint);
            addChild(particleSystem_smoke,12);
            particleSystem_smoke->release();
            particleSystem_smoke->setAutoRemoveOnFinish(true);
        }else if(plistName==PARTICLE_DRAGON_CURVE){
            dragonAction3Over=true;
            if (SaveManager::getInstance()->getSoundOn()) {
                SimpleAudioEngine::getInstance()->playEffect(AUDIO_DRAGON_ATTACK);
            }
            ParticleSystem* particleSystem_smoke=ParticleSystemQuad::create(PARTICLE_LIFE_SMOKE);
            particleSystem_smoke->retain();
            particleSystem_smoke->setPosition(endPoint);
            addChild(particleSystem_smoke,12);
            particleSystem_smoke->release();
            particleSystem_smoke->setAutoRemoveOnFinish(true);
        }else if(plistName==PARTICLE_LIFE_CURVE){
            ParticleSystem* particleSystem_smoke=ParticleSystemQuad::create(PARTICLE_LIFE_SMOKE);
            particleSystem_smoke->retain();
            particleSystem_smoke->setPosition(endPoint);
            addChild(particleSystem_smoke,12);
            particleSystem_smoke->release();
            particleSystem_smoke->setAutoRemoveOnFinish(true);
        }else if(plistName==PARTICLE_GOLD_CURVE){
            ParticleSystem* particleSystem_smoke=ParticleSystemQuad::create(PARTICLE_GOLD_SMOKE);
            particleSystem_smoke->retain();
            particleSystem_smoke->setPosition(endPoint);
            addChild(particleSystem_smoke,12);
            particleSystem_smoke->release();
            particleSystem_smoke->setAutoRemoveOnFinish(true);
        }
    }),NULL));
    particleSystem_curve->release();
    particleSystem_curve->setAutoRemoveOnFinish(true);
}

void GameScene::playCurveParticle2(std::string plistName, cocos2d::Point startPoint, cocos2d::Point endPoint,int i,int j,bool isSkill){
    if(!isSkill){
        if(cardArr[i][j]->getHaveMergeCount()==1){
            return;
        }
    }
    if(!isSkill){
        cardArr[i][j]->setHaveMergeCount(1);
    }
    Point q1,q2;
    if(startPoint.x<endPoint.x){
        q1=Point(startPoint.x-240,startPoint.x+(endPoint.y-startPoint.x)/2);
        q2=Point(startPoint.x+(endPoint.x-startPoint.x)*0.75,(endPoint.y-startPoint.y)/4+endPoint.y);
    }else if(startPoint.x>endPoint.x){
        q1=Point(startPoint.x+240,startPoint.x+(endPoint.y-startPoint.x)/2);
        q2=Point(startPoint.x+(endPoint.x-startPoint.x)*0.75,(endPoint.y-startPoint.y)/4+endPoint.y);
    }else if(startPoint.x==endPoint.x&&startPoint.x<540){
        q1=Point(startPoint.x-100,startPoint.y+(endPoint.y-startPoint.y)/4);
        q2=Point(startPoint.x-100,startPoint.y+(endPoint.y-startPoint.y)*0.75);
    }else if(startPoint.x==endPoint.x&&startPoint.x>540){
        q1=Point(startPoint.x+100,startPoint.y+(endPoint.y-startPoint.y)/4);
        q2=Point(startPoint.x+100,startPoint.y+(endPoint.y-startPoint.y)*0.75);
    }
    ccBezierConfig cfg;
    cfg.controlPoint_1 = q1;
    cfg.controlPoint_2 = q2;
    cfg.endPosition = endPoint;
    
    BezierTo* bezierTo;
    
    ParticleSystem* particleSystem_curve=ParticleSystemQuad::create(plistName);
    particleSystem_curve->retain();
    
    addChild(particleSystem_curve,12);
    
    auto distance=sqrtf(std::pow(endPoint.y-startPoint.y,2)+std::pow(endPoint.x-startPoint.x,2));
    if(distance<400){
        particleSystem_curve->setDuration(0.4);
        bezierTo=BezierTo::create(0.6, cfg);
    }else if(distance>=400&&distance<600){
        particleSystem_curve->setDuration(0.8);
        bezierTo=BezierTo::create(0.8, cfg);
    }else if(distance>=600&&distance<800){
        particleSystem_curve->setDuration(1.0);
        bezierTo=BezierTo::create(1.0, cfg);
    }else{
        particleSystem_curve->setDuration(1.2);
        bezierTo=BezierTo::create(1.2, cfg);
    }
    
    particleSystem_curve->setPosition(startPoint);
    particleSystem_curve->runAction(Sequence::create(bezierTo,CallFunc::create([this,plistName,isSkill](){
        if(plistName==PARTICLE_SWORD_CURVE){
            if(gameManagerInstance->swordLabel_vector.size()!=0){
                swordAction2Over=true;
            }
            if (SaveManager::getInstance()->getSoundOn()) {
                SimpleAudioEngine::getInstance()->playEffect(AUDIO_SWORD);
            }
        }else if(plistName==PARTICLE_DRAGON_CURVE){
            if(!isSkill){
                if(gameManagerInstance->dragonLabel_vector.size()!=0){
                    dragonAction2Over=true;
                }
            }else{
                if(gameManagerInstance->dragonLabel_vector.size()!=0){
                    swordAction3Over=true;
                }
            }
            if (SaveManager::getInstance()->getSoundOn()) {
                SimpleAudioEngine::getInstance()->playEffect(AUDIO_DRAGON);
            }
        }else if(plistName==PARTICLE_LIFE_CURVE){
            if(gameManagerInstance->lifeLabel_vector.size()!=0){
                lifeAction2Over=true;
            }
            if (SaveManager::getInstance()->getSoundOn()) {
                SimpleAudioEngine::getInstance()->playEffect(AUDIO_LIFE);
            }
        }else if(plistName==PARTICLE_GOLD_CURVE){
            if(!isSkill){
                if(gameManagerInstance->goldLabel_vector.size()!=0){
                    goldAction2Over=true;
                }
            }
            if (SaveManager::getInstance()->getSoundOn()) {
                SimpleAudioEngine::getInstance()->playEffect(AUDIO_GOLD);
            }
        }
    }),NULL));
    particleSystem_curve->release();
    particleSystem_curve->setAutoRemoveOnFinish(true);
}

int GameScene::getLabelNumber(int tag){
    std::stringstream stream;
    int number;
    switch (tag) {
        case DRAGON_TAG:
            stream<<dragonLabel->getString();
            stream>>number;
            break;
        case SWORD_TAG:
            stream<<swordLabel->getString();
            stream>>number;
            break;
        case LIFE_TAG:
            stream<<lifeLabel->getString();
            stream>>number;
            break;
        case GOLD_TAG:
            stream<<goldLabel->getString();
            stream>>number;
            break;
        default:
            break;
    }
    return number;
}

void GameScene::setLabelNumber(int tag, int num){
    std::stringstream stream;
    stream<<num;
    switch (tag) {
        case DRAGON_TAG:
            dragonLabel->setString(stream.str());
            break;
        case SWORD_TAG:
            swordLabel->setString(stream.str());
            break;
        case LIFE_TAG:
            lifeLabel->setString(stream.str());
            break;
        case GOLD_TAG:
            goldLabel->setString(stream.str());
            break;
        default:
            break;
    }
    
}

void GameScene::swordLabelChange(){
    int num_now=getLabelNumber(SWORD_TAG);
    int num_change=0;
    if(gameManagerInstance->swordLabel_vector.size()!=0){
        auto num_iterator=gameManagerInstance->swordLabel_vector.cbegin();
        num_change=*num_iterator;
    }
    
    int num_set;
    if(num_change!=0){
        int changeSpeed;
        if(abs(num_change)>200){
            changeSpeed=200;
        }else if(abs(num_change)>100&&abs(num_change)<=200){
            changeSpeed=40;
        }else if(abs(num_change)<=100&&abs(num_change)>20){
            changeSpeed=10;
        }else if(abs(num_change)<=20&&abs(num_change)>10){
            changeSpeed=5;
        }else{
            changeSpeed=2;
        }
        if(num_change>0){
            if(swordAction2Over){
                num_set=num_now+changeSpeed;
                num_change-=changeSpeed;
                if(num_change<=0){
                    num_set+=num_change;
                    gameManagerInstance->swordLabel_vector.erase(gameManagerInstance->swordLabel_vector.begin());
                    swordActionOver=true;
                    if(gameManagerInstance->swordLabel_vector.size()==0){
                        swordAction2Over=false;
                    }
                }else{
                    *gameManagerInstance->swordLabel_vector.begin()=num_change;
                }
                setLabelNumber(SWORD_TAG, num_set);
            }
        }else{
            
            num_set=num_now-changeSpeed;
            num_change+=changeSpeed;
            if(num_change>=0){
                num_set+=num_change;
                gameManagerInstance->swordLabel_vector.erase(gameManagerInstance->swordLabel_vector.begin());
            }else{
                *gameManagerInstance->swordLabel_vector.begin()=num_change;
            }
            setLabelNumber(SWORD_TAG, num_set);
            
        }
    }else{
        if(swordActionOver){
            if(num_now!=0){
                if(gameManagerInstance->dragonLabel_vector.size()==0){
                    swordActionOver=false;
                    auto dragon_num_set=getLabelNumber(DRAGON_TAG);
                    if(dragon_num_set!=0){
                        playCurveParticle(PARTICLE_SWORD_CURVE, getPosition(0, 4), getPosition(1, 4));
                        auto smallNum=returnSmallNum(SWORD_TAG, DRAGON_TAG);
                        gameManagerInstance->swordLabel_vector.push_back(-smallNum);
                        gameManagerInstance->dragonLabel_vector.push_back(-smallNum);
                    }
                }
            }
        }
    }
}

void GameScene::dragonLabelChange(){
    int num_now=getLabelNumber(DRAGON_TAG);
    int num_change=0;
    if(gameManagerInstance->dragonLabel_vector.size()!=0){
        auto num_iterator=gameManagerInstance->dragonLabel_vector.cbegin();
        num_change=*num_iterator;
    }
    int num_set;
    if(num_change!=0){
        int changeSpeed;
        if(abs(num_change)>200){
            changeSpeed=200;
        }else if(abs(num_change)>100&&abs(num_change)<=200){
            changeSpeed=40;
        }else if(abs(num_change)<=100&&abs(num_change)>20){
            changeSpeed=10;
        }else if(abs(num_change)<=20&&abs(num_change)>10){
            changeSpeed=5;
        }else{
            changeSpeed=2;
        }
        if(num_change>0){
            if(dragonAction2Over==true){
                num_set=num_now+changeSpeed;
                num_change-=changeSpeed;
                if(num_change<=0){
                    num_set+=num_change;
                    gameManagerInstance->dragonLabel_vector.erase(gameManagerInstance->dragonLabel_vector.begin());
                    dragonActionOver=true;
                    if(gameManagerInstance->dragonLabel_vector.size()==0){
                        dragonAction2Over=false;
                    }
                }else{
                    *gameManagerInstance->dragonLabel_vector.begin()=num_change;
                }
                setLabelNumber(DRAGON_TAG, num_set);
            }
            
        }else{
            if(swordAction3Over){
                num_set=num_now-changeSpeed;
                num_change+=changeSpeed;
                if(num_change>=0){
                    num_set+=num_change;
                    gameManagerInstance->dragonLabel_vector.erase(gameManagerInstance->dragonLabel_vector.begin());
                    if(gameManagerInstance->dragonLabel_vector.size()==0){
                        swordAction3Over=false;
                    }
                }else{
                    *gameManagerInstance->dragonLabel_vector.begin()=num_change;
                }
                setLabelNumber(DRAGON_TAG, num_set);
            }
        }
    }else{
        if(dragonActionOver==true){
            if(num_now!=0){
                if(gameManagerInstance->lifeLabel_vector.size()==0){
                    dragonActionOver=false;
                    auto life_num_set=getLabelNumber(LIFE_TAG);
                    if(life_num_set!=0){
                        playCurveParticle(PARTICLE_DRAGON_CURVE, getPosition(1, 4), getPosition(2, 4));
                        auto smallNum=returnSmallNum(DRAGON_TAG, LIFE_TAG);
                        gameManagerInstance->lifeLabel_vector.push_back(-smallNum);
                    }
                }
            }
        }
    }
}

void GameScene::lifeLableChange(){
    int num_set;
    int num_now=getLabelNumber(LIFE_TAG);
    int num_change=0;
    if(gameManagerInstance->lifeLabel_vector.size()!=0){
        auto num_iterator=gameManagerInstance->lifeLabel_vector.cbegin();
        num_change=*num_iterator;
    }
    if(num_change!=0){
        int changeSpeed;
        if(abs(num_change)>200){
            changeSpeed=200;
        }else if(abs(num_change)>100&&abs(num_change)<=200){
            changeSpeed=40;
        }else if(abs(num_change)<=100&&abs(num_change)>20){
            changeSpeed=10;
        }else if(abs(num_change)<=20&&abs(num_change)>10){
            changeSpeed=3;
        }else{
            changeSpeed=2;
        }
        if(num_change>0){
            if(lifeAction2Over){
                num_set=num_now+changeSpeed;
                num_change-=changeSpeed;
                if(num_change<=0){
                    num_set+=num_change;
                    gameManagerInstance->lifeLabel_vector.erase(gameManagerInstance->lifeLabel_vector.begin());
                    if(gameManagerInstance->lifeLabel_vector.size()==0){
                        lifeAction2Over=false;
                    }
                }else{
                    *gameManagerInstance->lifeLabel_vector.begin()=num_change;
                }
                setLabelNumber(LIFE_TAG, num_set);
            }
        }else{
            if(dragonAction3Over){
                num_set=num_now-changeSpeed;
                num_change+=changeSpeed;
                if(num_change>=0){
                    num_set+=num_change;
                    gameManagerInstance->lifeLabel_vector.erase(gameManagerInstance->lifeLabel_vector.begin());
                    if(gameManagerInstance->lifeLabel_vector.size()==0){
                        dragonAction3Over=false;
                    }
                }else{
                    *gameManagerInstance->lifeLabel_vector.begin()=num_change;
                }
                setLabelNumber(LIFE_TAG, num_set);
            }
        }
    }
}

void GameScene::goldsLabelChange(){
    int num_set;
    int num_now=getLabelNumber(GOLD_TAG);
    int num_change=0;
    if(gameManagerInstance->goldLabel_vector.size()!=0){
        auto num_iterator=gameManagerInstance->goldLabel_vector.cbegin();
        num_change=*num_iterator;
    }
    if(num_change!=0){
        int changeSpeed;
        if(abs(num_change)>500){
            changeSpeed=500;
        }else if(abs(num_change)>200&&abs(num_change)<=500){
            changeSpeed=200;
        }else if(abs(num_change)>100&&abs(num_change)<=200){
            changeSpeed=40;
        }else if(abs(num_change)<=100&&abs(num_change)>20){
            changeSpeed=20;
        }else if(abs(num_change)<=20&&abs(num_change)>10){
            changeSpeed=5;
        }else{
            changeSpeed=2;
        }
        if(num_change>0){
            if(goldAction2Over){
                num_set=num_now+changeSpeed;
                num_change-=changeSpeed;
                if(num_change<=0){
                    num_set+=num_change;
                    gameManagerInstance->goldLabel_vector.erase(gameManagerInstance->goldLabel_vector.begin());
                    if(gameManagerInstance->goldLabel_vector.size()==0){
                        goldAction2Over=false;
                    }
                }else{
                    *gameManagerInstance->goldLabel_vector.begin()=num_change;
                }
                setLabelNumber(GOLD_TAG, num_set);
                SaveManager::getInstance()->setGolds(num_set);
            }
        }else{
            num_set=num_now-changeSpeed;
            num_change+=changeSpeed;
            if(num_change>=0){
                num_set+=num_change;
                gameManagerInstance->goldLabel_vector.erase(gameManagerInstance->goldLabel_vector.begin());
               
            }else{
                *gameManagerInstance->goldLabel_vector.begin()=num_change;
            }
            setLabelNumber(GOLD_TAG, num_set);
            SaveManager::getInstance()->setGolds(num_set);
        }
    }
}

void GameScene::socreLabelChange(){
    if(gameManagerInstance->score_vector.size()!=0){
        int number=*gameManagerInstance->score_vector.cbegin();
        if(number!=0){
            int changeSpeed;
            if(number>100000){
                changeSpeed=100000;
            }else if(number>10000&&number<=100000){
                changeSpeed=10000;
            }else if(number>=2000&&number<10000){
                changeSpeed=2000;
            }else if(number<2000&&number>=1000){
                changeSpeed=500;
            }else if(number<1000&&number>=500){
                changeSpeed=250;
            }else if(number<500){
                changeSpeed=100;
            }
            SaveManager::getInstance()->score_number+=changeSpeed;
            number-=changeSpeed;
            if(number<=0){
                SaveManager::getInstance()->score_number+=number;
                gameManagerInstance->score_vector.erase(gameManagerInstance->score_vector.begin());
            }else{
                *gameManagerInstance->score_vector.begin()=number;
            }
            score->setString(__String::createWithFormat("%i",SaveManager::getInstance()->score_number)->getCString());
        }
    }
}

void GameScene::skillChange(){
    if(exchangeLayer!=nullptr){
        if(gameManagerInstance->exchangeNum==1){
            playCurveParticle2(PARTICLE_SWORD_CURVE, exchange_btn->getPosition(), getPosition(0, 4), 0,0,true);
            auto number=getLabelNumber(SWORD_TAG);
            if(number!=0){
                gameManagerInstance->swordLabel_vector.push_back(number);
            }
            gameManagerInstance->exchangeNum=0;
        }else if(gameManagerInstance->exchangeNum==2){
            playCurveParticle2(PARTICLE_SWORD_CURVE, exchange_btn->getPosition(), getPosition(0, 4), 0,0,true);
            gameManagerInstance->swordLabel_vector.push_back(10);
            gameManagerInstance->exchangeNum=0;
        }else if(gameManagerInstance->exchangeNum==3){
            playCurveParticle2(PARTICLE_LIFE_CURVE, exchange_btn->getPosition(), getPosition(2, 4), 0,0,true);
            auto number=getLabelNumber(LIFE_TAG);
            if(number!=0){
                gameManagerInstance->lifeLabel_vector.push_back(number);
            }
            gameManagerInstance->exchangeNum=0;
        }else if(gameManagerInstance->exchangeNum==4){
            playCurveParticle2(PARTICLE_LIFE_CURVE, exchange_btn->getPosition(), getPosition(2, 4), 0,0,true);
            gameManagerInstance->lifeLabel_vector.push_back(10);
            gameManagerInstance->exchangeNum=0;
        }else if(gameManagerInstance->exchangeNum==5){
            auto number=getLabelNumber(DRAGON_TAG);
            if(number!=0){
                playCurveParticle2(PARTICLE_DRAGON_CURVE, exchange_btn->getPosition(), getPosition(1, 4), 0,0,true);
                gameManagerInstance->dragonLabel_vector.push_back(-number);
            }
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    if(cardArr[i][j]!=NULL){
                        if(cardArr[i][j]->getPicTag()==DRAGON_TAG){
                            playCardParticle(PARTICLE_DRAGON_BROKEN, getPosition(i, j), i, j, true);
                        }
                    }
                }
            }
            gameManagerInstance->exchangeNum=0;
        }else if(gameManagerInstance->exchangeNum==6){
            playCurveParticle2(PARTICLE_DRAGON_CURVE, exchange_btn->getPosition(), getPosition(1, 4), 0,0,true);
            auto number=getLabelNumber(DRAGON_TAG);
            if (number!=0) {
                gameManagerInstance->dragonLabel_vector.push_back(-(10>number?number:10));
            }
            gameManagerInstance->exchangeNum=0;
        }
        
    }
}

void GameScene::resetGameChange(){
    if(gameManagerInstance->resetgame==true){
        gameManagerInstance->resetgame=false;
        resetGame();
    }
}

int GameScene::returnSmallNum(int tag1, int tag2){
    auto num1=getLabelNumber(tag1);
    auto num2=getLabelNumber(tag2);
    return num1>num2?num2:num1;
}

void GameScene::doCheck(){
    bool isGameOver=true;
    int count=0;
    for(int y=0;y<4;y++){
        for(int x=0;x<4;x++){
            if(cardArr[x][y]!=NULL){
                count++;
            }
        }
    }
    if(count==16){
        for(int y=0;y<4;y++){
            for(int x=0;x<4;x++){
                if((x<3&&cardArr[x][y]->getPicTag()==cardArr[x+1][y]->getPicTag())||
                   (x>0&&cardArr[x][y]->getPicTag()==cardArr[x-1][y]->getPicTag())||
                   (y<3&&cardArr[x][y]->getPicTag()==cardArr[x][y+1]->getPicTag())||
                   ((y>0&&cardArr[x][y]->getPicTag()==cardArr[x][y-1]->getPicTag()))){
                    isGameOver=false;
                }
            }
        }
    }else{
        isGameOver=false;
    }
    if(isGameOver){
        this->isGameOver=true;
        gameManagerInstance->isLife0=false;
    }
}

void GameScene::generate_next_color(){
    next_tag=CCRANDOM_0_1()*4+1;
    switch (next_tag) {
        case DRAGON_TAG:
            nextColor->setColor(COLOR3B_DRAGON_BG);
            break;
        case LIFE_TAG:
            nextColor->setColor(COLOR3B_LIFE_BG);
            break;
        case GOLD_TAG:
            nextColor->setColor(COLOR3B_GOLD_BG);
            break;
        case SWORD_TAG:
            nextColor->setColor(COLOR3B_SWORD_BG);
            break;
        default:
            break;
    }
}

void GameScene::resetGame(){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(cardArr[i][j]!=NULL){
                cardArr[i][j]->removeFromParent();
                cardArr[i][j]=NULL;
            }
        }
    }
    exchangeLayer=nullptr;
    gameOverLayer=nullptr;
    pauseLayer=nullptr;
    guideLayer=nullptr;
    
    delayTime=0;
    
    isPopLayer=false;
    isPopGameOverLayer=false;
    gameManagerInstance->isDragonCome=false;
    if(SaveManager::getInstance()->getBGMOn()){
        SimpleAudioEngine::getInstance()->playBackgroundMusic(AUDIO_BACKGROUND1,true);
    }
    setLabelNumber(DRAGON_TAG, 0);
    setLabelNumber(SWORD_TAG, 0);
    setLabelNumber(LIFE_TAG, 30);
    setLabelNumber(GOLD_TAG, SaveManager::getInstance()->geteGolds());
    initRandCard();
    SaveManager::getInstance()->score_number=0;
    score->setString(__String::createWithFormat("%i",0)->getCString());
    generate_next_color();
    if(isGameOver){
        touchListener=EventListenerTouchOneByOne::create();
        touchListener->onTouchBegan=CC_CALLBACK_2(GameScene::onTouchBegan, this);
        touchListener->onTouchMoved=CC_CALLBACK_2(GameScene::onTouchMoved, this);
        touchListener->onTouchEnded=CC_CALLBACK_2(GameScene::onTouchEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    }
    isGameOver=false;
    
    swordActionOver=false;
    dragonActionOver=false;
    lifeActionOver=false;
    goldActionOver=false;
    
    swordAction2Over=false;
    dragonAction2Over=false;
    lifeAction2Over=false;
    goldAction2Over=false;
    
    swordAction3Over=false;
    dragonAction3Over=false;
    lifeAction3Over=false;
    goldAction3Over=false;
    srand((unsigned)time(NULL));
}

void GameScene::dragonCome(int i,int j){
    if(gameManagerInstance->isDragonCome==true){
        if(SaveManager::getInstance()->getSoundOn()){
            SimpleAudioEngine::getInstance()->playEffect(AUDIO_DRAGON_COME);
        }
        auto dragon=Sprite::create(DRAGON_COME_PIC);
        dragon->setColor(Color3B(58,17,68));
        dragon->setPosition(Vec2(DesignResolutionWidth/2,DesignResolutionHeight/2));
        addChild(dragon,3);
        ScaleTo* large=ScaleTo::create(0.4, 3);
        FadeOut* fadeOut=FadeOut::create(0.5);
        dragon->runAction(Spawn::create(large,fadeOut, NULL));
        
        ParticleSystem* particleSystem_curve=ParticleSystemQuad::create(PARTICLE_DRAGON_COME);
        particleSystem_curve->retain();
        addChild(particleSystem_curve,12);
        particleSystem_curve->setPosition(getPosition(i, j));
        particleSystem_curve->release();
        particleSystem_curve->setAutoRemoveOnFinish(true);
        gameManagerInstance->isDragonCome=false;
    }
}



