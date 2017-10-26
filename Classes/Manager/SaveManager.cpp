//
//  SaveManager.cpp
//  dungeonTiles
//
//  Created by Moon on 16/8/14.
//
//

#include "SaveManager.hpp"

USING_NS_CC;

SaveManager* SaveManager::instance=NULL;
SaveManager* SaveManager::getInstance(){
    if(instance==NULL){
        instance=new SaveManager();
    }
    return instance;
}

bool SaveManager::init(){
    auto map=FileUtils::getInstance()->getValueMapFromFile(SAVE_FILE_PATH);
    if(map.size()>0) {
        if(!map["rank"].isNull()){
            firstIn=false;
            rank=map["rank"].asValueVector();
            std::sort(rank.begin(), rank.end(), [](Value a,Value b){
                return a.asInt()>b.asInt();
            });
            if(!map["BGM"].isNull()){
                isBGMOn=map["BGM"].asBool();
            }else{
                isBGMOn=true;
            }
            
            if(!map["sound"].isNull()){
                isSoundOn=map["sound"].asBool();
            }else{
                isSoundOn=true;
            }
            
            if(!map["golds"].isNull()){
                golds=map["golds"].asInt();
            }else{
                golds=0;
            }
        }
    }else{
        firstIn=true;
        isBGMOn=true;
        isSoundOn=true;
        golds=0;
    }
    return true;
}

int SaveManager::getMaxPoint(){
    if(rank.size()>0){
        return rank[0].asInt();
    }else{
        return 0;
    }
}

void SaveManager::addPoint(int point){
    firstIn=false;
    if(rank.size()!=0){
        if(rank[0].asInt()<point){
            rank.clear();
            rank.push_back(Value(point));
            writeSaveToFile();
        }else{
            if(rank.size()==2){
                rank.erase(rank.begin()+1);
            }
            rank.push_back(Value(point));
            writeSaveToFile();
        }
    }else{
        rank.push_back(Value(point));
        writeSaveToFile();
    }
}

bool SaveManager::writeSaveToFile(){
    ValueMap map;
    if(rank.size()!=0){
        std::sort(rank.begin(),rank.end(),[](Value a,Value b){
            return a.asInt()>b.asInt();
        });
        map["rank"]=rank;
    }
    map["BGM"]=Value(isBGMOn);
    map["sound"]=Value(isSoundOn);
    map["golds"]=Value(golds);
    return FileUtils::getInstance()->writeToFile(map, SAVE_FILE_PATH);
}

void SaveManager::setBGMOn(bool b){
    isBGMOn=b;
    writeSaveToFile();
}

bool SaveManager::getBGMOn(){
    return isBGMOn;
}

void SaveManager::setSoundOn(bool b){
    isSoundOn=b;
    writeSaveToFile();
}

bool SaveManager::getSoundOn(){
    return isSoundOn;
}

void SaveManager::setGolds(int num){
    golds=num;
    writeSaveToFile();
}

int SaveManager::geteGolds(){
    return golds;
}

