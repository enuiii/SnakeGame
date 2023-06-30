#include "Snake.h"
#include "Logger.h"

const int WindowWidth = 800;
const int WindowHeight = 600;

SnakeGame::Snake::Snake() {
    position.x = WindowWidth / 2;
    position.y = WindowHeight / 2;

    sf::RectangleShape head(sf::Vector2f(SnakeSize, SnakeSize));
    head.setFillColor(sf::Color::Green);
    head.setPosition(position);
    body.push_front(head);

    velocity.x = SnakeSize;
    velocity.y = 0;
}

void SnakeGame::Snake::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && velocity.y != SnakeSize) {
        velocity.x = 0;
        velocity.y = -SnakeSize;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && velocity.y != -SnakeSize) {
        velocity.x = 0;
        velocity.y = SnakeSize;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && velocity.x != SnakeSize) {
        velocity.x = -SnakeSize;
        velocity.y = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && velocity.x != -SnakeSize) {
        velocity.x = SnakeSize;
        velocity.y = 0;
    }
}

void SnakeGame::Snake::update() {
    sf::Vector2f newPosition = position + velocity;

    if (newPosition.x >= WindowWidth) {
        newPosition.x = 0;
    }
    else if (newPosition.x < 0) {
        newPosition.x = static_cast<float>(WindowWidth - SnakeSize);
    }

    if (newPosition.y >= WindowHeight) {
        newPosition.y = 0;
    }
    else if (newPosition.y < 0) {
        newPosition.y = static_cast<float>(WindowHeight - SnakeSize);
    }

    position = newPosition;

    sf::RectangleShape newBodyPart(sf::Vector2f(SnakeSize, SnakeSize));
    newBodyPart.setFillColor(sf::Color::Green);
    newBodyPart.setPosition(position);
    body.push_front(newBodyPart);

    checkWindowBoundaries();

    if (body.size() > 1) {
        body.pop_back();
    }
}

void SnakeGame::Snake::checkWindowBoundaries()
{
    if (position.x >= WindowWidth || position.x < 0 || position.y >= WindowHeight || position.y < 0)
    {
        throw std::runtime_error("Snake has gone out of bounds!");
    }
}

void SnakeGame::Snake::render(sf::RenderWindow& window) {
    for (const auto& bodyPart : body) {
        window.draw(bodyPart);
    }
}

void SnakeGame::Snake::grow() {
    sf::RectangleShape newBodyPart(sf::Vector2f(SnakeSize, SnakeSize));
    newBodyPart.setFillColor(sf::Color::Green);
    newBodyPart.setPosition(position);
    body.push_back(newBodyPart);
}

bool SnakeGame::Snake::isCollidingWithSelf() {
    for (auto it = std::next(body.begin()); it != body.end(); ++it) {
        if (body.front().getPosition() == (*it).getPosition()) {
            return true;
        }
    }
    return false;
}

bool SnakeGame::Snake::isCollidingWithApple(sf::Vector2f applePosition) {
    return body.front().getPosition() == applePosition;
}