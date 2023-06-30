#include "Apple.h"
#include <random>

const int WindowWidth = 800;
const int WindowHeight = 600;

const int SnakeSize = 20;

SnakeGame::Apple::Apple() {
    shape.setSize(sf::Vector2f(AppleSize, AppleSize));
    shape.setFillColor(sf::Color::Red);
    respawn();
}

void SnakeGame::Apple::respawn() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> xDist(0, WindowWidth / SnakeSize - 1);
    std::uniform_int_distribution<int> yDist(0, WindowHeight / SnakeSize - 1);

    int x = xDist(rng) * SnakeSize;
    int y = yDist(rng) * SnakeSize;

    if (x >= WindowWidth || y >= WindowHeight)
    {
        throw std::runtime_error("Apple position is out of bounds!");
    }


    position.x = static_cast<float>(x);
    position.y = static_cast<float>(y);

    shape.setPosition(position);
}

void SnakeGame::Apple::render(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::Vector2f SnakeGame::Apple::getPosition() {
    return position;
}