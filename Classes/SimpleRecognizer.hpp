//
//  SimpleRecongnizer.hpp
//  dungeonTiles
//
//  Created by Moon on 16/7/21.
//
//

#ifndef SimpleRecognizer_hpp
#define SimpleRecognizer_hpp

#include <stdio.h>
#include "cocos2d.h"

typedef enum{
    SimpleGesturesRight,
    SimpleGesturesLeft,
    SimpleGesturesUp,
    SimpleGesturesDown,
    SimpleGesturesError,
    SimpleGesturesNotsupport
} SimpleGestures;

class SimpleRecognizer{
    double X;
    double Y;
    SimpleGestures result;
    std::vector<cocos2d::Point> points;
public:
    SimpleRecognizer();
    
    void beginPoint(cocos2d::Point point);
    void movePoint(cocos2d::Point point );
    SimpleGestures endPoint(cocos2d::Point point);
    
    std::vector<cocos2d::Point>& getPoints();
};

#endif /* SimpleRecognizer_hpp */
