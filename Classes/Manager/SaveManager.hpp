//
//  SaveManager.hpp
//  dungeonTiles
//
//  Created by Moon on 16/8/14.
//
//

#ifndef SaveManager_hpp
#define SaveManager_hpp

#include <stdio.h>
#include "cocos2d.h"

#define SAVE_FILE_PATH (FileUtils::getInstance()->getWritablePath()+"rank.nightmoon")

class SaveManager{
public:
    static SaveManager* getInstance();
    bool init();
    void addPoint(int point);
    int getMaxPoint();
    
    CC_SYNTHESIZE(bool, firstIn, FirstIn);
    void setBGMOn(bool b);
    bool getBGMOn();
    void setSoundOn(bool b);
    bool getSoundOn();
    void setGolds(int num);
    int geteGolds();
    bool writeSaveToFile();
    
    int score_number;
    int golds;
private:
    static SaveManager* instance;
    std::vector<cocos2d::Value> rank;
    bool isBGMOn;
    bool isSoundOn;
};

#endif /* SaveManager_hpp */
