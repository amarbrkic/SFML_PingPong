#include "../headers/Paddle.hpp"

Paddle::Paddle(float x, float y, float width, float height)
{
    this->shape.setPosition(x, y);
    this->shape.setSize(sf::Vector2f(width * 0.025f, height * 0.25f));
    this->shape.setFillColor(sf::Color::White);
}

const sf::RectangleShape &Paddle::getShape() const
{
    return this->shape;
}

void Paddle::moveUp(double dt)
{
    this->shape.move(0.f, movementSpeed * -1.f * static_cast<double>(dt));
    std::cout << static_cast<double>(dt) << std::endl;
}

void Paddle::moveDown(double dt)
{
    this->shape.move(0.f, movementSpeed * static_cast<double>(dt));
    std::cout << static_cast<double>(dt) * movementSpeed << std::endl;
}

void Paddle::speedUpForFullscreen()
{
    this->movementSpeed = 2500.f;
}

void Paddle::resetSpeed()
{
    this->movementSpeed = 1000.f;
}