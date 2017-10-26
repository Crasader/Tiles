//
//  GameManager.hpp
//  dungeonTiles
//
//  Created by Moon on 16/8/21.
//
//

#ifndef GameManager_hpp
#define GameManager_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ConstUtil.hpp"

class GameManager{
public:
    static GameManager* getInstance();
    void init();

    std::vector<int> swordLabel_vector;
    std::vector<int> dragonLabel_vector;
    std::vector<int> goldLabel_vector;
    std::vector<int> lifeLabel_vector;
    std::vector<int> score_vector;
   
    int exchangeNum;
    bool resetgame;
    bool isDragonCome;
    bool isLife0;
    
    
private:
    static GameManager* instance;
};
#endif /* GameManager_hpp */
