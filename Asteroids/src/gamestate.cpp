#include "gamestate.h"
#include "game.h"
#include <string>

GameState::GameState(Game* pGame) : mpGame(pGame) {

}

WelcomeState::WelcomeState(Game* pGame) : GameState(pGame) {
	if (!mFont.loadFromFile("data/Halo3.ttf"))
	{
		throw std::runtime_error("ERROR");
	}

	mText_1.reset(new sf::Text("Asteroids clone by D.Dragas",mFont, FONT_SIZE_BIG));
	mText_1->setPosition(250, 250);

	mText_2.reset(new sf::Text("Press any key to continue", mFont, FONT_SIZE_SMALL));
	mText_2->setPosition(350, 300);
}

void WelcomeState::handleEvents(sf::Event event){
	//Promijeni u switch naredbu
	if (event.type == sf::Event::KeyPressed){
		mpGame->setState(Playing);
	}
	if (event.type == sf::Event::Closed ){
		mpGame->end();
	}
	return;
}

void WelcomeState::update(sf::Time dt){
	return;
}

void WelcomeState::render(){
	(mpGame->getWindow())->draw(*mText_1);
	(mpGame->getWindow())->draw(*mText_2);
	return;
}

ScoreState::ScoreState(Game* pGame) : GameState(pGame) {
	if (!mFont.loadFromFile("data/Halo3.ttf"))
	{
		throw std::runtime_error("ERROR");
	}

	mText_1.reset(new sf::Text("Score = " + std::to_string(mpGame->gameScore), mFont, FONT_SIZE_BIG));
	mText_1->setPosition(750, 250);

	mText_2.reset(new sf::Text("Enter to continue, Esc to finish.", mFont, FONT_SIZE_BIG));
	mText_2->setPosition(250, 300);

}

void ScoreState::handleEvents(sf::Event event){
	if (event.type == sf::Event::KeyPressed){
		switch(event.key.code){
			case sf::Keyboard::Key::Escape:
				mpGame->end();
				break;
			case sf::Keyboard::Key::Return:
				mpGame->setState(Playing);
				break;
		}	
	}
	if (event.type == sf::Event::Closed ){
		mpGame->end();
	}
	return;
}

void ScoreState::update(sf::Time dt){
	mText_1.reset(new sf::Text("Score = " + std::to_string(mpGame->gameScore), mFont, FONT_SIZE_BIG));
	mText_1->setPosition(750, 250);
	return;
}

void ScoreState::render(){
	(mpGame->getWindow())->draw(*mText_1);
	(mpGame->getWindow())->draw(*mText_2);
	return;
}
