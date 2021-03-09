//
//  Circle.hpp
//  PE
//
//  Created by Elliot Glaze on 06/03/2021.
//  Copyright © 2021 Elliot Glaze. All rights reserved.
//

#ifndef Circle_hpp
#define Circle_hpp
#define _USE_MATH_DEFINES

#include <math.h>

struct Position {
    float x;
    float y;
};

struct Velocity {
    float xSpeed;
    float ySpeed;
};

struct Acceleration {
    float x;
    float y;
};

struct Force {
    float fx;
    float fy;
};

struct Drag {
    float dx;
    float dy;
};

class Circle {
public:
    Circle(Position position, Velocity velocity, Acceleration acceleration, Force force, float size, float mass);
    Position getPosition() {return position;}
    float getSize() {return size;}
    
    void setPosition(float x, float y) {position.x = x, position.y = y;}
    void setAcceleration(float x, float y) {acceleration.x = x, acceleration.y = y;}
    void setSize(float s) {size = s;}
    
    void move();
    void moveTo(float x, float y);
    void accelerate();
    void applyForce();
    void applyDrag();
    void bounce();
    void collisionDetection(Circle *otherCircle);
    
protected:
    Position position;
    Velocity velocity;
    Acceleration acceleration;
    Force force;
    Drag drag;
    float size;
    float mass;
};

#endif /* Circle_hpp */


