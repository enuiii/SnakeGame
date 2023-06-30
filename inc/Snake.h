#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <deque>
#include "gameobject.h"

namespace SnakeGame
{
    const int SnakeSize = 20;

    class Snake : public GameObject
    {
    public:
        Snake();
        void handleInput();
        void update() override;
        void render(sf::RenderWindow& window) override;
        void grow();
        bool isCollidingWithSelf();
        bool isCollidingWithApple(sf::Vector2f applePosition);

    private:
        sf::Vector2f position;
        std::deque<sf::RectangleShape> body;
        sf::Vector2f velocity;
        void checkWindowBoundaries();
    };
}

#endif