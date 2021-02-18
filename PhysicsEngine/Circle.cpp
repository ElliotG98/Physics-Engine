//
//  Circle.cpp
//  PhysicsEngine
//
//  Created by Elliot Glaze on 14/02/2021.
//  Copyright © 2021 Elliot Glaze. All rights reserved.
//

#include "Circle.hpp"

Velocity operator+(Velocity const& v1, Velocity const& v2) {
    float x = sin(v1.angle) * v1.speed + sin(v2.angle) * v2.speed;
    float y = cos(v1.angle) * v1.speed + cos(v2.angle) * v2.speed;
    return Velocity{static_cast<float>(0.5 * M_PI - atan2(y, x)), hypot(x, y)};
}

Circle::Circle(float x, float y, float size, float mass, float speed, float angle):
x(x), y(y), size(size), mass(mass), speed(speed), angle(angle) {
}

void Circle::collide(Circle *otherC) {
    float dx = x - otherC->x;
    float dy = y - otherC->y;
    float distance = hypot(dx, dy);
    
    if (distance < (size + otherC->size)) {
        float tangent = atan2(dy, dx);
        float newAngle = 0.5 * M_PI + tangent;
        float totalMass = mass + otherC->mass;
        
        Velocity v1 = Velocity{angle, speed * (mass - otherC->mass) / totalMass} + Velocity{newAngle, 2 * otherC->speed * otherC->mass / totalMass};
        Velocity v2 = Velocity{otherC->angle, otherC->speed * (otherC->mass - mass) / totalMass} + Velocity{static_cast<float>(newAngle+M_PI), 2 * speed * mass / totalMass};
        
        angle = v1.angle;
        speed = v1.speed;
        otherC->angle = v2.angle;
        otherC->speed = v2.speed;
        
        float overlap = 0.5 * (size + otherC->size - distance + 1);
        x += sin(newAngle) * overlap;
        y -= cos(newAngle) * overlap;
        otherC->x -= sin(newAngle) * overlap;
        otherC->y += cos(newAngle) * overlap;
    }
}

void Circle::move() {
    x += sin(angle) * speed;
    y -= cos(angle) * speed;
}

void Circle::moveTo(float moveX, float moveY) {
    float dx = moveX - x;
    float dy = moveY - y;
    angle = atan2(dy, dx) + 0.5 * M_PI;
    speed = hypot(dx, dy) * 0.1;
}

