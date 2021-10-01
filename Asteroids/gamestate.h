#pragma once

#include "textureHolder.h"
#include "entities.h"

#include <SFML/Graphics.hpp>
#include <memory>

#define V_MAX 250.0f
#define ASTEROID_BIG 1
#define SHOOT_RESET 198
#define FONT_SIZE_BIG 50
#define FONT_SIZE_SMALL 35
#define TEXT_1_X 60
#define TEXT_1_Y 0
#define TEXT_2_X 900
#define TEXT_2_Y 0
#define TEXT_END_X 10
#define TEXT_END_Y 15
#define SHOOT_BEGIN 4

class Game;

class GameState
{
public:
    GameState(Game* pGame);
    virtual ~GameState() {}
    enum State{
	    Welcome,
        Playing,
        Score,
        SIZE
    };
    virtual void init() = 0;
    virtual void handleEvents(sf::Event event) = 0;
    virtual void update(sf::Time dt = sf::Time::Zero) = 0;
    virtual void render() = 0;

protected:
    Game* const mpGame; 
       
};


class WelcomeState : public GameState{
public:
    WelcomeState(Game* pGame);
    void init() override {};
    void handleEvents(sf::Event event) override;
    void update(sf::Time dt = sf::Time::Zero) override;
    void render() override;
private:
    sf::Font mFont;
    std::unique_ptr<sf::Text> mText_1; 
    std::unique_ptr<sf::Text> mText_2; 
};

class ScoreState : public GameState{
public:
    ScoreState(Game* pGame);
    void init() override {};
    void handleEvents(sf::Event event) override;
    void update(sf::Time dt = sf::Time::Zero) override;
    void render() override;
private:
    sf::Font mFont;
    std::unique_ptr<sf::Text> mText_1; 
    std::unique_ptr<sf::Text> mText_2;
};


