#pragma once

#include <chrono>

#include <SFML/Graphics.hpp>

#include "Paddle.hpp"
#include "Ball.hpp"

class Game
{
  private:
    unsigned int windowWidth = 800;
    unsigned int windowHeight = 600;
    sf::RenderWindow* window;
    Paddle playerOne;
    Paddle playerTwo;
    int PlayerOneScore = 0;
    int PlayerTwoScore = 0;
    Ball ball;
    bool fullscreen = false;
    int framerate = 60;
    sf::Uint32 style = sf::Style::Close;
    std::chrono::steady_clock::time_point fpsClockStart;

    sf::Text playersScore;
    sf::Text fpsText;
    sf::Font font;
    unsigned int characterSize = 30;

    unsigned int fps = 1;

    bool paused = false;

  public:
    Game();
    virtual ~Game();

    void init();
    void initWindow();
    void initPlayers(size_t width, size_t height);
    void initFullscreen();
    void initBall();
    void initScore();
    void initFPS();

    // multiple update functions which are called in the update() function
    void update();
    void updatePollEvents();
    void updateInput();
    void updatePosition();
    void updateScore();
    void updateOnResize();
    void updateFPS();

    bool checkCollisionUp(Paddle* paddle);
    bool checkCollisionDown(Paddle* paddle);

    void switchRefreshRate();

    void draw();

    void run();
};
