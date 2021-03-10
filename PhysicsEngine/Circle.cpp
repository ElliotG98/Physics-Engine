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
    acceleration.x += force.fx / mass;
    acceleration.y += force.fy / mass;
}

void Circle::applyDrag(){
    // Fd = - cd ||v2|| * UnitVector  Ive assumed area and density as constants that are counted in the coefficient
    float c = 0.1;
    float magx = sqrt(pow(c * velocity.xSpeed,2));
    float magy = sqrt(pow(c * velocity.ySpeed,2));
    
    drag.dx = magx/(velocity.xSpeed * -1); //normalise and apply an opposite force
    drag.dy = magy/(velocity.ySpeed * -1);
    
    acceleration.x += drag.dx;
    acceleration.y += drag.dy;
}

//Collsion with boundarys
void Circle::bounce() {
    float height = 600;
    float width = 800;
    
    if ((position.x > (width-size)) || (position.x < 0+size)) {
        velocity.xSpeed *= -1;
    }
    if ((position.y > (height-size)) || (position.y < 0+size)) {
        velocity.ySpeed *= -1;
    }
    if (position.x > width-size) {
        position.x = width-size;
    }
    if (position.x < 0+size){
        position.x = 0+size;
    }
    if (position.y > height-size) {
        position.y = height-size;
    }
    if (position.y < 0+size){
        position.y = 0+size;
    }
}

void Circle::collisionDetection(Circle *otherCircle){
    float otherSize = otherCircle->getSize();
    float otherMass = otherCircle->mass;
    //distance between them
    float dx = otherCircle->position.x - position.x;
    float dy = otherCircle->position.y - position.y;
    float otherDx = position.x - otherCircle->position.x;
    float otherDy = position.y - otherCircle->position.y;
    //calculate the distance between circles
    float distance = sqrt(dx * dx + dy * dy);
    
    //Collision has occured
    if (size + otherSize >= distance){
        //normalise distance vector
        float nx = dx / distance;
        float ny = dy / distance;
        //Move the circles based on the angle between them using the ratio of the size to calculate contact point
        float distFromCircle1 = distance * (size/(size + otherSize));
        float contactX = position.x + nx * distFromCircle1;
        float contactY = position.y + ny * distFromCircle1;
        //stop intersecting
        position.x = contactX - nx * size;
        position.y = contactY - ny * size;
        otherCircle->position.x = contactX + nx * otherSize;
        otherCircle->position.y = contactY + ny * otherSize;
//          Get velocities and directions
        float v1 = sqrt(pow(dx,2) + pow(dy, 2));
        float v2 = sqrt(pow(otherDx,2) + pow(otherDy, 2));
        float dir1 = atan2(dy, dx);
        float dir2 = atan2(otherDy, otherDx);
        //direction from center to center
        float contactDir = atan2(ny, nx);
        //Elastic collision where v is velocity, d is direction, m is mass, p is angle of contact
        //
        //      v1* cos(d1-p) * (m1 - m2) + 2 * m2 * v2 * cos(d2- p)
        // vx = ----------------------------------------------------- * cos(p) + v1 * sin(d1-p) * cos(p + PI/2)
        //                    m1 + m2

        //      v1* cos(d1-p) * (m1 - m2) + 2 * m2 * v2 * cos(d2- p)
        // vy = ----------------------------------------------------- * sin(p) + v1 * sin(d1-p) * sin(p + PI/2)
        //                     m1 + m2
        //Formula to code
        float mm = mass - otherMass;
        float mmt = mass + otherMass;
        float firstHalf = ((v1 * cos(dir1-contactDir) * mm + 2 * otherMass * v2 * cos(dir2 - contactDir)) / mmt);
        float vx1 = firstHalf * cos(contactDir) + v1 * sin(dir1 - contactDir) * cos(contactDir + M_PI/2);
        float vy1 = firstHalf * sin(contactDir) + v1 * sin(dir1 - contactDir) * sin(contactDir + M_PI/2);
        mm = otherMass - mass;
        firstHalf = (v2 * cos(dir2-contactDir) * mm + 2 * mass * v1 * cos(dir1 - contactDir)) / mmt;
        float vx2 = firstHalf * cos(contactDir) + v2 * sin(dir2 - contactDir) * cos(contactDir + M_PI/2);
        float vy2 = firstHalf * sin(contactDir) + v2 * sin(dir2 - contactDir) * sin(contactDir + M_PI/2);
        
        velocity.xSpeed += vx1;
        velocity.ySpeed += vy1;
        otherCircle->velocity.xSpeed += vx2;
        otherCircle->velocity.ySpeed += vy2;
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
