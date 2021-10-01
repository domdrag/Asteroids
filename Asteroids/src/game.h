#pragma once
#include <SFML/Graphics.hpp>
#include "playstate.h"
#include <array>


class Game {
	friend class GameState;
	friend class WelcomeState;
	friend class PlayState;
	friend class ScoreState;
public:
	Game();
	~Game();
	void run();
	std::array<GameState*, 3> mAllStates;
	sf::RenderWindow* getWindow();
	void setState(GameState::State newState);
	void end();
private:
	void processEvents();
	void update(sf::Time dt);
	void render();

	sf::RenderWindow mWindow;
	GameState::State mState;
	sf::Time mDtFixed;
	int gameLives = 3;
	int gameScore = 0;
};

