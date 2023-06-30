#ifndef APPLE_H
#define APPLE_H

#include <SFML/Graphics.hpp>

namespace SnakeGame
{
    const int AppleSize = 20;

    class Apple
    {
    public:
        Apple();
        void respawn();
        void render(sf::RenderWindow& window);
        sf::Vector2f getPosition();

    private:
        sf::Vector2f position;
        sf::RectangleShape shape;
    };
}

#endif