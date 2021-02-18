#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"
#include "Environment.hpp"
#include "Circle.hpp"

int main(int, char const**)
{
    Environment *env = new Environment(800, 600);
    Circle *selectedCircle = nullptr;
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Physics Engine window");
    window.setFramerateLimit(60);
    
    //Adds an arbritrary number of Circles to the Env
    for (int i = 0; i < 6; i++) {
        env->addCircle();
    }
    
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            
            //If Circle clicked
            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left){
                    float mouseX = event.mouseButton.x;
                    float mouseY = event.mouseButton.y;
                    selectedCircle = env->getCircle(mouseX, mouseY);
                }
            }
            //If Circle released
            if (event.type == sf::Event::MouseButtonReleased){
                if (event.mouseButton.button == sf::Mouse::Left){
                    selectedCircle = nullptr;
                }
            }
        }
        //Sets window colour to Green
        window.clear(sf::Color(0, 200, 0, 255));
        
        env->update();
        
        //move circle if it's clicked
        if(selectedCircle){
            float mouseX = sf::Mouse::getPosition(window).x;
            float mouseY = sf::Mouse::getPosition(window).y;
            selectedCircle->moveTo(mouseX, mouseY);
        }
        
        for (int i = 0; i < env->getCircle().size(); i++) {
            Circle *circle = env->getCircle()[i];
            sf::CircleShape shape(circle->getSize());
            shape.setOrigin(circle->getSize(), circle->getSize());
            shape.setPosition(circle->getX(), circle->getY());
            window.draw(shape);
        }
        
        window.display();
    }
    return EXIT_SUCCESS;
}
