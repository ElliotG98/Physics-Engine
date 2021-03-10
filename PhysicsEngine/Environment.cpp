//
//  Environment.cpp
//  PE
//
//  Created by Elliot Glaze on 06/03/2021.
//  Copyright © 2021 Elliot Glaze. All rights reserved.
//

#include "Environment.hpp"


Environment::Environment(int width, int height):
width(width), height(height){
}

Circle * Environment::addCircle() {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<float> sizeRand(10,35);
    float size = sizeRand(rd);
    std::uniform_int_distribution<float> xRand(size, width - size);
    std::uniform_int_distribution<float> yRand(size, height - size);
    std::uniform_int_distribution<float> xVelocityRand(1, 5);
    std::uniform_int_distribution<float> yVelocityRand(1, 5);
    std::uniform_int_distribution<float> massRand(100, 200);
    float mass = massRand(rd);
    Position position = {xRand(rd), yRand(rd)};
    Velocity velocity = {xVelocityRand(rd), yVelocityRand(rd)};
    Acceleration acceleration = {0, 0};
    //Force = mass * acceleration
    //Earths Gravity = 9.807msSquared
    float gravityConstant = pow(9.807, 2);
    Force force = {0, gravityConstant};
    
    Circle *circle = new Circle(position, velocity, acceleration, force, size, mass);
    circles.push_back(circle);
    return circle;
}

Circle * Environment::getCircle(float x, float y){
    for (int i = 0; i < circles.size(); i++){
        if (hypot(circles[i]->getPosition().x - x, circles[i]->getPosition().y - y) <= circles[i]->getSize()){
            return circles[i];
        }
    }
    return nullptr;
}


void Environment::update() {
    for (int i = 0; i < circles.size(); i++) {
        Circle *c = circles[i];
        c->move();
        c->bounce();
        c->applyForce();
        c->applyDrag();
        c->accelerate();
        c->setAcceleration(0, 0);
        for (int j = i + 1; j < circles.size(); j++) {
            Circle *otherCircle = circles[j];
            c->collisionDetection(otherCircle);
        }
    }
}
