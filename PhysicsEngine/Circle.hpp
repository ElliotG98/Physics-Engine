//
//  Circle.hpp
//  PhysicsEngine
//
//  Created by Elliot Glaze on 14/02/2021.
//  Copyright © 2021 Elliot Glaze. All rights reserved.
//

#ifndef Circle_hpp
#define Circle_hpp
#define _USE_MATH_DEFINES

#include <math.h>

struct Velocity {
    float angle;
    float speed;
};
Velocity operator+(Velocity const& v1, Velocity const& v2);

class Circle {
public:
    Circle(float x, float y, float size, float mass, float speed, float angle, float airResistance);
    Circle *getCollideWith() { return collideWith; }
    float getAirResistance() {return airResistance;}
    float getAngle() { return angle; }
    float getMass() { return mass; }
    float getSize() { return size; }
    float getSpeed() { return speed; }
    float getX() { return x; }
    float getY() { return y; }
    void setAirResistance(float aR) {airResistance = aR;}
    void collide(Circle *otherC);
    void move();
    void accelerate(Velocity velocity);
    void drag();
    void moveTo(float moveX, float moveY);
    void setAngle(float a) { angle = a; }
    void setMass(float m) { mass = m; }
    void setSize(float s) { size = s; }
    void setSpeed(float s) { speed = s; }
    void setX(float xCoord) { x = xCoord; }
    void setY(float yCoord) { y = yCoord; }
    
protected:
    float airResistance;
    float angle;
    float mass;
    float size;
    float speed;
    float x;
    float y;
    Circle *collideWith = NULL;
};

#endif /* Circle_hpp */
