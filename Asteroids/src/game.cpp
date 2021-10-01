#include "game.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Game::Game() : mWindow(sf::VideoMode(1280, 1024), "SFML window"), mState(GameState::Welcome) {
    mDtFixed = sf::seconds(1.0f / 60.0f);
    mAllStates.at(GameState::Welcome) = new WelcomeState(this);
    mAllStates.at(GameState::Playing) = new PlayState(this);
    mAllStates.at(GameState::Score) = new ScoreState(this);
}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate >= mDtFixed) {
            timeSinceLastUpdate -= mDtFixed;
            processEvents();
            update(mDtFixed);
        }
        render();
    }
    return;
}

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
	    mAllStates.at(mState)->handleEvents(event);
    }
    return;
}

void Game::update(sf::Time dt) {
    mAllStates.at(mState)->update(dt);
    return;
}

void Game::render() {  
    mWindow.clear();
    mAllStates.at(mState)->render();
    mWindow.display();
    return;  
}

sf::RenderWindow* Game::getWindow(){
    return &mWindow;
}

void Game::setState(GameState::State newState){
    mState = newState;
    if( mState == GameState::Playing && (!gameLives || gameScore))
	    mAllStates.at(mState)->init();
    mAllStates.at(mState)->update(mDtFixed);
    return;
}

void Game::end(){
    mWindow.close();
    return;
}

Game::~Game(){
    delete mAllStates.at(GameState::Welcome);
    delete mAllStates.at(GameState::Playing);
    delete mAllStates.at(GameState::Score);
}
