#include "../headers/Game.hpp"

Game::Game()
{
    init();
}

Game::~Game()
{
    delete this->window;
}

void Game::update()
{
    updateInput();
    updatePosition();

    // update fps every 0.5 second
    if (std::chrono::steady_clock::now() - fpsClockStart > std::chrono::milliseconds(150))
    {
        updateFPS();
        fpsClockStart = std::chrono::steady_clock::now();
    }
}

void Game::run()
{
    while (this->window->isOpen())
    {
        auto start = std::chrono::high_resolution_clock::now();
        updatePollEvents();
        if (paused)
            continue;
        update();
        this->window->clear();
        draw();
        this->window->display();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        fps = static_cast<int>(1000000.f / duration.count());
    }
}

void Game::init()
{
    initWindow();
    initBall();
    initPlayers(windowWidth, windowHeight);
    initScore();
    initFPS();
}

void Game::initWindow()
{
    if (this->window != nullptr)
        delete this->window;
    this->window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Ping Pong", style);
    this->window->setFramerateLimit(framerate);
}

void Game::initPlayers(size_t width, size_t height)
{
    this->playerOne =
        Paddle(static_cast<float>(width) * 0.05f,
               static_cast<float>(height) * 0.5f - playerOne.getShape().getSize().y * 0.5f, width, height);
    this->playerTwo =
        Paddle(static_cast<float>(width) * 0.93f,
               static_cast<float>(height) * 0.5f - playerTwo.getShape().getSize().y * 0.5f, width, height);
    if (fullscreen)
    {
        playerOne.speedUpForFullscreen();
        playerTwo.speedUpForFullscreen();
    }
    else
    {
        playerOne.resetSpeed();
        playerTwo.resetSpeed();
    }
}

void Game::initFullscreen()
{
    if (!fullscreen)
    {
        windowHeight = sf::VideoMode::getDesktopMode().height;
        windowWidth = sf::VideoMode::getDesktopMode().width;
        style = sf::Style::Fullscreen;
        fullscreen = true;
        characterSize = 60;
    }
    else
    {
        windowHeight = 600;
        windowWidth = 800;
        style = sf::Style::Close;
        fullscreen = false;
        characterSize = 30;
    }
    init();
}

void Game::initBall()
{
    if (!fullscreen)
        this->ball =
            Ball(windowWidth * 0.5f, windowHeight * 0.5f, windowHeight * 0.025f, sf::Color::White, 500.f, 500.f);
    else
        this->ball =
            Ball(windowWidth * 0.5f, windowHeight * 0.5f, windowHeight * 0.025f, sf::Color::White, 1000.f, 1000.f);
}

void Game::initScore()
{
    if (!this->font.loadFromFile("arial.ttf"))
        std::cout << "Error loading font" << std::endl;
    this->playersScore.setFont(font);
    this->playersScore.setCharacterSize(characterSize);
    this->playersScore.setFillColor(sf::Color::White);
    this->playersScore.setPosition(windowWidth * 0.5f - 15.f, 0.f);
    this->playersScore.setString(std::to_string(PlayerOneScore) + " : " + std::to_string(PlayerTwoScore));
}

void Game::initFPS()
{
    this->fpsText.setFont(font);
    this->fpsText.setCharacterSize(characterSize);
    this->fpsText.setFillColor(sf::Color::White);
    this->fpsText.setPosition(windowWidth * 0.95f, windowHeight * 0.02f);
    std::cout << "FPS: " << fps << std::endl;
    this->fpsText.setString(std::to_string(fps));
}

void Game::updatePollEvents()
{
    sf::Event event;
    while (this->window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                this->window->close();
            if (event.key.code == sf::Keyboard::F)
                initFullscreen();
            if (event.key.code == sf::Keyboard::R)
                switchRefreshRate();
            if (event.key.code == sf::Keyboard::P)
                paused = !paused;
            if (event.key.code == sf::Keyboard::Space)
                ball.randomizeSpeedOfMovement();
            break;
        }
    }
}

void Game::updateInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and !checkCollisionUp(&playerOne))
        this->playerOne.moveUp(1.f / framerate);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) and !checkCollisionDown(&playerOne))
        this->playerOne.moveDown(1.f / framerate);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and !checkCollisionUp(&playerTwo))
        this->playerTwo.moveUp(1.f / framerate);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and !checkCollisionDown(&playerTwo))
        this->playerTwo.moveDown(1.f / framerate);
}

void Game::updatePosition()
{
    // check for collision with top and bottom of the window
    if (ball.getShape().getPosition().y < 0 or
        ball.getShape().getPosition().y + ball.getShape().getRadius() * 2 > windowHeight)
        ball.setSpeedOfMovementY(-ball.getSpeedOfMovement().y);
    ball.getShape().move(ball.getSpeedOfMovement().x / static_cast<float>(framerate),
                         ball.getSpeedOfMovement().y / static_cast<float>(framerate));
    // check for collision with paddles
    if (ball.getShape().getGlobalBounds().intersects(playerOne.getShape().getGlobalBounds()) or
        ball.getShape().getGlobalBounds().intersects(playerTwo.getShape().getGlobalBounds()))
    {
        if (ball.getSpeedOfMovement().x > 0)
            ball.setSpeedOfMovementX(ball.getSpeedOfMovement().x + 20);
        else
            ball.setSpeedOfMovementX(ball.getSpeedOfMovement().x - 20);
        ball.setSpeedOfMovementX(-ball.getSpeedOfMovement().x);
    }

    // check for collision with left and right of the window
    if (ball.getShape().getPosition().x < 0)
    {
        PlayerTwoScore++;
        initBall();
        updateScore();
    }
    if (ball.getShape().getPosition().x + ball.getShape().getRadius() * 2 > windowWidth)
    {
        PlayerOneScore++;
        initBall();
        updateScore();
    }
}

void Game::updateScore()
{
    playersScore.setString(std::to_string(PlayerOneScore) + " : " + std::to_string(PlayerTwoScore));
}

void Game::updateFPS()
{
    fpsText.setString(std::to_string(fps));
}

bool Game::checkCollisionUp(Paddle *paddle)
{
    if (paddle->getShape().getPosition().y < 0)
    {
        return true;
    }
    return false;
}

bool Game::checkCollisionDown(Paddle *paddle)
{
    if (paddle->getShape().getPosition().y + paddle->getShape().getSize().y > windowHeight)
    {
        return true;
    }
    return false;
}

void Game::switchRefreshRate()
{
    if (framerate == 60)
        framerate = 144;
    else
        framerate = 60;
    this->window->setFramerateLimit(framerate);
}

void Game::draw()
{
    this->window->draw(this->playerOne.getShape());
    this->window->draw(this->playerTwo.getShape());
    this->window->draw(this->ball.getShape());
    this->window->draw(this->playersScore);
    this->window->draw(this->fpsText);
}
