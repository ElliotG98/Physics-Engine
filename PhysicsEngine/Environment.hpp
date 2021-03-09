//
//  Environment.hpp
//  PE
//
//  Created by Elliot Glaze on 06/03/2021.
//  Copyright © 2021 Elliot Glaze. All rights reserved.
//

#ifndef Environment_hpp
#define Environment_hpp
#define _USE_MATH_DEFINES

#include "Circle.hpp"
#include <math.h>
#include <random>


class Environment {
public:
    Environment(int width, int height);
    ~Environment();
    int getHeight() {return height;}
    int getWidth() {return width;}
    std::vector<Circle *> getCircles() {return circles;}
    Circle * addCircle();
    Circle * getCircle(float x, float y);
    
    void update();
    void bounce(Circle *circle);
    
protected:
    const int height;
    const int width;
    std::vector<Circle *> circles;
};

#endif /* Environment_hpp */
