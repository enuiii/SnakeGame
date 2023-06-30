#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Apple.h"
#include "Logger.h"
#include <iostream>

const int WindowWidth = 800;
const int WindowHeight = 600;

const float SnakeSpeed = 0.1f;

int main() {
    sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "Snake Game");

    SnakeGame::Snake snake;
    SnakeGame::Apple apple;

    sf::Clock clock;
    float timer = 0.0f;
    try {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            float deltaTime = clock.restart().asSeconds();
            timer += deltaTime;

            if (timer >= SnakeSpeed) {
                snake.handleInput();
                snake.update();

                if (snake.isCollidingWithSelf()) {
                    throw std::runtime_error("Snake collided with itself!");
                }

                if (snake.isCollidingWithApple(apple.getPosition())) {
                    snake.grow();
                    apple.respawn();
                }

                timer = 0.0f;

                if (snake.isCollidingWithApple(apple.getPosition()))
                {
                    snake.grow();
                    apple.respawn();
                }
            }

            window.clear();
            snake.render(window);
            apple.render(window);
            window.display();
        }
    }

    catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }

    Logger logger("log.txt", LogLevel::Debug);

    logger.log("This is an info message", LogLevel::Info);
    logger.log("This is a debug message", LogLevel::Debug);
    logger.log("This is an error message", LogLevel::Error);

    logger.setLogLevel(LogLevel::Info);

    logger.log("This message should be logged with Info level", LogLevel::Info);

    return 0;
}