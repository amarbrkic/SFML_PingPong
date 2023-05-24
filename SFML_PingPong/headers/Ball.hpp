#pragma once

#include <iostream>

#include <cmath>
#include <ctime>

#include <SFML/Graphics.hpp>

class Ball
{
  private:
    sf::CircleShape shape;
    float standardSpeedOfMovementX = 500.f;
    float standardSpeedOfMovementY = 500.f;
    float speedOfMovementX = 0.f;
    float speedOfMovementY = 0.f;

  public:
    Ball() = default;
    Ball(float xPosition, float yPosition, float radius, sf::Color color, float speedOfMovementX,
         float speedOfMovementY);
    sf::CircleShape& getShape();

    sf::Vector2f getSpeedOfMovement();

    void setSpeedOfMovementX(float x);
    void setSpeedOfMovementY(float y);
    void randomizeSpeedOfMovement();
};