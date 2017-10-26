//
//  SimpleRecongnizer.cpp
//  dungeonTiles
//
//  Created by Moon on 16/7/21.
//
//

#include "SimpleRecognizer.hpp"

USING_NS_CC;

#define MAX_DOUBLE std::numeric_limits<double>::max();

SimpleRecognizer::SimpleRecognizer(){
    this->result=SimpleGesturesError;
}

void SimpleRecognizer::beginPoint(cocos2d::Point point){
    this->result=SimpleGesturesError;
    points.clear();
    points.push_back(point);
}

void SimpleRecognizer::movePoint(cocos2d::Point point){
    points.push_back(point);
}

SimpleGestures SimpleRecognizer::endPoint(cocos2d::Point point){
    points.push_back(point);
    
    if(this->points.size()<3){
        return SimpleGesturesError;
    }
    
    SimpleGestures newRtn=SimpleGesturesError;
    int len=this->points.size();
    double dx=this->points[len-1].x-this->points[0].x;
    double dy=this->points[len-1].y-this->points[0].y;
    
    if(std::abs(dx)>std::abs(dy)){
        if(dx>0){
            newRtn=SimpleGesturesRight;
        }else{
            newRtn=SimpleGesturesLeft;
        }
    }else{
        if(dy>0){
            newRtn=SimpleGesturesUp;
        }else{
            newRtn=SimpleGesturesDown;
        }
    }
    
    if(result==SimpleGesturesError){
        result=newRtn;
    }
    return result;
}

std::vector<Point>& SimpleRecognizer::getPoints(){
    return points;
}