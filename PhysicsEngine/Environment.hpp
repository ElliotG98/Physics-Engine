//
//  Environment.hpp
//  PhysicsEngine
//
//  Created by Elliot Glaze on 12/02/2021.
//  Copyright © 2021 Elliot Glaze. All rights reserved.
//

#ifndef Environment_hpp
#define Environment_hpp
#define _USE_MATH_DEFINES

#include <math.h>
#include <random>
#include "Circle.hpp"

class Environment {
public:
    Environment(int width, int height);
    ~Environment();
    int getHeight() {return height;}
    int getWidth() {return width;}
    Circle * addCircle();
        Circle * addCircle(float x, float y, float size, float mass, float speed, float angle);
        Circle * getCircle(float x, float y);
        std::vector<Circle* > getCircle() { return circles; }
        void collisionResponse(Circle *circle);
        void removeCircle(Circle *circle);
        void setAllowcollisionResponse(bool setting) { allowcollisionResponse = setting; }
        void setAllowCollide(bool setting) { allowCollide = setting; }
        void setAllowMove(bool setting) { allowMove = setting; }
        void update();
        
    protected:
        const int height;
        const int width;
        bool allowcollisionResponse = true;
        bool allowCollide = true;
        bool allowMove = true;
        std::vector<Circle *> circles;
        Velocity acceleration = {M_PI, 0.2};
};

#endif /* Environment_hpp */