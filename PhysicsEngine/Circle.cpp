//
//  Circle.cpp
//  PE
//
//  Created by Elliot Glaze on 06/03/2021.
//  Copyright © 2021 Elliot Glaze. All rights reserved.
//

#include "Circle.hpp"

Circle::Circle(Position position, Velocity velocity, Acceleration acceleration, Force force, float size, float mass):
position(position), velocity(velocity), acceleration(acceleration), force(force), size(size), mass(mass) {
}

void Circle::accelerate(){
    velocity.xSpeed += acceleration.x;
    velocity.ySpeed += acceleration.y;
}
void Circle::applyForce(){
    //Accelleration = force / mass
    acceleration.x = force.fx / mass;
    acceleration.y = force.fy / mass;
}

void Circle::applyDrag(){
    // Fd = - cd ||v2|| * UnitVector  Ive assumed area and density as constants that are counted in the coefficient
    float c = 0.1;
    float magx = sqrt(pow(c * velocity.xSpeed,2));
    float magy = sqrt(pow(c * velocity.ySpeed,2));
    
    drag.dx = magx/(velocity.xSpeed * -1); //normalise and apply an opposite force
    drag.dy = magy/(velocity.ySpeed * -1);
    
    velocity.xSpeed += drag.dx;
    velocity.ySpeed += drag.dy;
}

void Circle::collisionDetection(Circle *otherCircle){
    //distance
    float distance = sqrt((position.x - otherCircle->position.x)*(position.x - otherCircle->position.x) + (position.y - otherCircle->position.y)*(position.y - otherCircle->position.y));
    
    //Collision has occured
    if (size + otherCircle->size >= distance){
        //displacement
        float overlap = 0.5f * (distance - size - otherCircle->size);
        //displace circle1 away from collision
        position.x -= overlap * (position.x - otherCircle->position.x) / distance;
        position.y -= overlap * (position.y - otherCircle->position.y) / distance;
        //displace circle2 away from collision
        otherCircle->position.x += overlap * (position.x - otherCircle->position.x) / distance;
        otherCircle->position.y += overlap * (position.y - otherCircle->position.y) / distance;
        //normalise
        float nx = (otherCircle->position.x - position.x) / distance;
        float ny = (otherCircle->position.y - position.y) / distance;
        //formula
        float kx = (velocity.xSpeed - otherCircle->velocity.xSpeed);
        float ky = (velocity.ySpeed - otherCircle->velocity.ySpeed);
        float p = 2.0 * (nx * kx + ny * ky) / (mass + otherCircle->mass);
        //update velocities
        velocity.xSpeed = velocity.xSpeed - p * otherCircle->mass * nx;
        velocity.ySpeed = velocity.ySpeed - p * otherCircle->mass * ny;
        otherCircle->velocity.xSpeed = otherCircle->velocity.xSpeed + p * mass * nx;
        otherCircle->velocity.ySpeed = otherCircle->velocity.ySpeed + p * mass * ny;
    }
}

void Circle::moveTo(float x, float y){
    float dx = x - position.x;
    float dy = y - position.y;
    velocity.xSpeed = dx * 0.1;
    velocity.ySpeed = dy * 0.1;
}

void Circle::move(){
    position.x += velocity.xSpeed;
    position.y += velocity.ySpeed;
}
