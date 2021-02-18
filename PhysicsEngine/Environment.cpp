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
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> sizeDist(10,20);
    float size = sizeDist(rd);
    std::uniform_int_distribution<int> massDist(100, 10000);
    float mass = massDist(rd);
    std::uniform_int_distribution<int> xDist(size, width - size);
    float x = xDist(rd);
    std::uniform_int_distribution<int> yDist(size, height - size);
    float y = yDist(rd);
    std::uniform_real_distribution<float> speedDist (0, 1);
    float speed = speedDist(rd);
    std::uniform_real_distribution<float> angleDist (0, 2 * M_PI);
    float angle = angleDist(rd);
    return addCircle(x, y, size, mass, 0, 0);
}

Circle * Environment::addCircle(float x, float y, float size, float mass, float speed, float angle) {
    Circle *circle = new Circle(x, y, size, mass, speed, angle);
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
        circle->move();
        collisionResponse(circle);
        // Allow circles to collide with eachother
        for (int x = i + 1; x < circles.size(); x++) {
            Circle *otherCircle = circles[x];
            circle->collide(otherCircle);
        }
    }
}

