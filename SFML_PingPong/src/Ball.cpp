#include "../headers/Ball.hpp"

Ball::Ball(float xPosition, float yPosition, float radius, sf::Color color, float speedOfMovementX,
           float speedOfMovementY)
{
    this->shape.setPosition(xPosition, yPosition);
    this->shape.setRadius(radius);
    this->shape.setFillColor(color);
    this->speedOfMovementX = 0.f;
    this->speedOfMovementY = 0.f;
}

sf::CircleShape &Ball::getShape()
{
    return this->shape;
}

sf::Vector2f Ball::getSpeedOfMovement()
{
    return sf::Vector2f(speedOfMovementX, speedOfMovementY);
}

void Ball::setSpeedOfMovementX(float x)
{
    this->speedOfMovementX = x;
}

void Ball::setSpeedOfMovementY(float y)
{
    this->speedOfMovementY = y;
}

void Ball::randomizeSpeedOfMovement()
{
    srand(time(NULL));
    float x = static_cast<float>(rand() % 2);
    float y = static_cast<float>(rand() % 2);

    if (x == 0.f)
    {
        x = -1.f;
    }

    if (y == 0.f)
    {
        y = -1.f;
    }

    this->speedOfMovementX = x * standardSpeedOfMovementX;
    this->speedOfMovementY = y * standardSpeedOfMovementY;
}