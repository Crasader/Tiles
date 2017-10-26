//
//  GameLogoScene.hpp
//  dungeonTiles
//
//  Created by Moon on 16/9/10.
//
//

#ifndef GameLogoScene_hpp
#define GameLogoScene_hpp

#include <stdio.h>
#include "Scene/GameStartScene.hpp"
#include "ConstUtil.hpp"

class GameLogoScene:public cocos2d::Scene{
public:
    CREATE_FUNC(GameLogoScene);
    virtual bool init();
};
#endif /* GameLogoScene_hpp */
