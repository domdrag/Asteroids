#pragma once

#include "gamestate.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <list>

class PlayState : public GameState{
public:
	PlayState(Game* pGame);
	void init() override;
	void handleEvents(sf::Event event) override;
	void update(sf::Time dt = sf::Time::Zero) override;
	void render() override;
	void handlePlayerInput(sf::Keyboard::Key code, bool isPressed);
	static int mShoot; //Osigurava cca 1 metak po 1 pritisku na tipku
private:
	sf::RenderWindow* mWindow;
	TextureHolder mTextureHolder;
	sf::Sprite mBackgroundSprite;
	std::unique_ptr<Player> mPlayer;
	std::list<std::unique_ptr<Entity> > mObjects; //Asteroidi,meci i eksplozije
	sf::Font mFont;
	std::unique_ptr<sf::Text> mText_1; //Lives
	std::unique_ptr<sf::Text> mText_2; //Score

	bool mIsMovingUp = false;
	bool mIsMovingDown = false;
	bool mIsMovingLeft = false;
	bool mIsMovingRight = false;
	bool mSpace = false;

	float mVelocity = 120.0f; // pixel/sec
	unsigned int mLives = 3;
	unsigned int mScore = 0;
	unsigned int mAsteroids = 0; //Broj asteroida
	sf::Time mDtFixed;
	bool mCollision = false;
};
