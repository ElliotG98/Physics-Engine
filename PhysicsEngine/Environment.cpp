//
//  Environment.cpp
//  PhysicsEngine
//
//  Created by Elliot Glaze on 12/02/2021.
//  Copyright © 2021 Elliot Glaze. All rights reserved.
//

#include "Environment.hpp"


//Constructor -- create the Environment
Environment::Environment(int width, int height):
width(width), height(height){
}

//Destructor -- Destroy everything in the environment
Environment::~Environment(){
    for (int i = 0; i < circles.size(); i++) {
        delete circles[i];
    }
}

//Create circles with a random distribution of settings i.e. starting speeds and angles
Circle * Environment::addCircle() {
    std::random_device random;
    std::default_random_engine el(random());
    std::uniform_int_distribution<int> sizeDist(10,30);
    std::uniform_int_distribution<int> massDist(100, 10000);
    float size = sizeDist(el);
    float speed = 0;
    float angle = 0;
    float mass = massDist(el);
    std::uniform_int_distribution<int> xDist(size, width - size);
    std::uniform_int_distribution<int> yDist(size, height - size);
    float x = xDist(el);
    float y = yDist(el);
    return addCircle(x, y, size, mass, speed, angle);
}

Circle * Environment::addCircle(float x, float y, float size, float mass, float speed, float angle) {
    //https://jfuchs.hotell.kau.se/kurs/amek/prst/06_simu.pdf drag forces
    //-1/2 x mass * speed squared * size * drag coeficient * angle
    float dragCoef = 0.1;
    float airResistance = -1/2*(mass*(speed*speed)*size*dragCoef*angle);
    Circle *circle = new Circle(x, y, size, mass, speed, angle, airResistance);
    circles.push_back(circle);
    return circle;
}

Circle * Environment::getCircle(float x, float y){
    for (int i = 0; i < circles.size(); i++) {
        if (hypot(circles[i]->getX() - x, circles[i]->getY() - y) <= circles[i]->getSize()) {
            return circles[i];
        }
    }
    return nullptr;
}

void Environment::collisionResponse(Circle *circle) {
    // Circle hits the right boundary:
    if (circle->getX() > (width - circle->getSize())) {
        circle->setX(2 * (width - circle->getSize()) - circle->getX());
        circle->setAngle(-circle->getAngle());
        circle->setSpeed(circle->getSpeed());
    // Circle hits the left boundary:
    } else if (circle->getX() < circle->getSize()) {
        circle->setX(2 * circle->getSize() - circle->getX());
        circle->setAngle(-circle->getAngle());
        circle->setSpeed(circle->getSpeed());
    }
    // Circle hits the bottom boundary:
    if (circle->getY() > (height - circle->getSize())) {
        circle->setY(2 * (height - circle->getSize()) - circle->getY());
        circle->setAngle(M_PI - circle->getAngle());
        circle->setSpeed(circle->getSpeed());
    // Circle hits the top boundary:
    } else if (circle->getY() < circle->getSize()) {
        circle->setY(2 * circle->getSize() - circle->getY());
        circle->setAngle(M_PI - circle->getAngle());
        circle->setSpeed(circle->getSpeed());
    }
}

void Environment::update() {
    for (int i = 0; i < circles.size(); i++) {
        Circle *circle = circles[i];
        //start circles moving and colliding
        circle->accelerate(acceleration);
        circle->move();
        circle->drag();
        collisionResponse(circle);
        // individually check if circles intersect by size : collide
        for (int x = i + 1; x < circles.size(); x++) {
            Circle *otherCircle = circles[x];
            circle->collide(otherCircle);
        }
    }
}

