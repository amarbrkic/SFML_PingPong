#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

class Paddle
{
  private:
    sf::RectangleShape shape;
    double movementSpeed = 1000.f;

  public:
    Paddle() = default;
    Paddle(float x, float y, float width, float height);

    // Accessors
    const sf::RectangleShape& getShape() const;

    // Functions
    void moveUp(double dt);
    void moveDown(double dt);

    void incrementScore();
    size_t getScore() const;
};