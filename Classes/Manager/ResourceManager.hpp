//
//  ResourceManager.hpp
//  dungeonTiles
//
//  Created by Moon on 16/7/29.
//
//

#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ConstUtil.hpp"

class ResourceManager{
public:
    static ResourceManager* getInstance();
    void init();
private:
    static ResourceManager* instance;
};
#endif /* ResourceManager_hpp */
