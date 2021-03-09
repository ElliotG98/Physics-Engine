
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include "Environment.hpp"
#include "Circle.hpp"

int main(int, char const**)
{
    Environment *env = new Environment(800, 600);
    Circle *selectedCircle = nullptr;
    
    sf::RenderWindow window(sf::VideoMode(env->getWidth(), env->getHeight()), "window");
    window.setFramerateLimit(60);
    
    for (int i = 0; i < 2; i++) {
        env->addCircle();
    }
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            //Grab Circle
            if(event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left){
                    float mouseX = event.mouseButton.x;
                    float mouseY = event.mouseButton.y;
                    selectedCircle = env->getCircle(mouseX, mouseY);
                }else if (event.mouseButton.button == sf::Mouse::Right){
                    env->addCircle();
                }
            }
            //Release Circle
            if (event.type == sf::Event::MouseButtonReleased){
                if (event.mouseButton.button == sf::Mouse::Left) {
                    selectedCircle = nullptr;
                }
            }
        }
        
        window.clear();
        
        env->update();
        
        if (selectedCircle) {
            float mouseX = sf::Mouse::getPosition(window).x;
            float mouseY = sf::Mouse::getPosition(window).y;
            selectedCircle->moveTo(mouseX, mouseY);
        }
        
        for (int i = 0; i < env->getCircles().size(); i++) {
            Circle *circ = env->getCircles()[i];
            sf::CircleShape circle(circ->getSize());
            circle.setOrigin(circ->getSize(), circ->getSize());
            circle.setPosition(circ->getPosition().x, circ->getPosition().y);
            window.draw(circle);
        }
        
        // Update the window
        window.display();
    }
    
    return EXIT_SUCCESS;
}
