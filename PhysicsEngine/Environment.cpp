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
    std::uniform_int_distribution<float> massRand(10, 20);
    float mass = massRand(rd);
    Position position = {xRand(rd), yRand(rd)};
    Velocity velocity = {xVelocityRand(rd), yVelocityRand(rd)};
    Acceleration acceleration = {0, 0};
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

//Collsion with boundarys
void Environment::bounce(Circle *c) {
    float x = c->getPosition().x;
    float y = c->getPosition().y;
    float xSpeed = c->getVelocity().xSpeed;
    float ySpeed = c->getVelocity().ySpeed;
    float size = c->getSize();
    
    
    if ((x > (width-size)) || (x < size)) {
        c->setVelocityX(-xSpeed * 0.75);
    }
    if ((y > (height-size)) || (y < size)) {
        c->setVelocityY(-ySpeed * 0.75);
    }
    if (x > width-size) {
        c->setX(width-size);
    }
    if (x < size){
        c->setX(size);
    }
    if (y > height-size) {
        c->setY(height-size);
    }
    if (y < size){
        c->setY(size);
    }
}


void Environment::update() {
    for (int i = 0; i < circles.size(); i++) {
        Circle *c = circles[i];
        c->applyForce();
        c->accelerate();
        c->move();
        c->applyDrag();
        bounce(c);
        for (int j = i + 1; j < circles.size(); j++) {
            Circle *otherCircle = circles[j];
            c->collisionDetection(otherCircle);
        }
    }
}


