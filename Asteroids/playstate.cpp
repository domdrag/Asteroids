#include "playstate.h"
#include "game.h"

#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>
#include <memory>
#include <typeinfo>

int PlayState::mShoot = SHOOT_BEGIN;

PlayState::PlayState(Game* pGame) : GameState(pGame), mWindow(pGame->getWindow()) {
    mDtFixed = sf::seconds(1.0f / 60.0f);
    mBackgroundSprite.setTexture(mTextureHolder.getTexture(Textures::background));
    if (!mFont.loadFromFile("design/Halo3.ttf"))
    {
        throw std::runtime_error("ERROR");
    }

    mText_1.reset(new sf::Text("Lives: " + std::to_string(mLives),mFont, FONT_SIZE_BIG));
    mText_1->setPosition(TEXT_1_X, TEXT_1_Y);

    mText_2.reset(new sf::Text("Score: " + std::to_string(mScore), mFont, FONT_SIZE_BIG));
    mText_2->setPosition(TEXT_2_X, TEXT_2_Y);

    mPlayer.reset(new Player(mTextureHolder.getTexture(Textures::player)));
    mPlayer->setPosition(mWindow->getView().getSize().x / 2, mWindow->getView().getSize().y / 2);

    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0;i < 6;++i) {
        //Big asteroids
        if (!i || i == 1) {
            mObjects.push_back(std::make_unique<Asteroid>(mTextureHolder.getTexture(static_cast<Textures::ID>((rand() % 4) + 4)),1));
            mObjects.back()->setPosition(static_cast<float>(rand() % 1280), static_cast<float>(rand() % 1024));
        }
        //Medium asteroids
        else if (i == 2 || i == 3){
            mObjects.push_back(std::make_unique<Asteroid>(mTextureHolder.getTexture(static_cast<Textures::ID>((rand() % 2) + 8)),2));
            mObjects.back()->setPosition(static_cast<float>(rand() % 1280), static_cast<float>(rand() % 1024));
        }
        //Small asteroids
        else {
            mObjects.push_back(std::make_unique<Asteroid>(mTextureHolder.getTexture(static_cast<Textures::ID>((rand() % 2) + 10)),4));
            mObjects.back()->setPosition(static_cast<float>(rand() % 1280), static_cast<float>(rand() % 1024));
        }
        ++mAsteroids;
    }

}

void PlayState::init(){
    mLives = 3;
    mScore = 0;
    mAsteroids = 0;
    PlayState::mShoot = 1;

    if (!mFont.loadFromFile("Halo3.ttf"))
    {
        std::cout << "CODE 440" << std::endl;
    }
    mText_1.reset(new sf::Text("Lives: " + std::to_string(mLives), mFont, FONT_SIZE_BIG));
    mText_1->setPosition(TEXT_1_X, TEXT_1_Y);
    mText_2.reset(new sf::Text("Score: " + std::to_string(mScore), mFont, FONT_SIZE_BIG));
    mText_2->setPosition(TEXT_2_X, TEXT_2_Y);

    mPlayer.reset(new Player(mTextureHolder.getTexture(Textures::player)));
    mPlayer->setPosition(mWindow->getView().getSize().x / 2, mWindow->getView().getSize().y / 2);
    mObjects.clear();

    for (int i = 0;i < 6;++i) {
        //Big asteroids
        if (!i || i == 1) {
            mObjects.push_back(std::make_unique<Asteroid>(mTextureHolder.getTexture(static_cast<Textures::ID>((rand() % 4) + 4)), 1));
            mObjects.back()->setPosition(static_cast<float>(rand() % 1280), static_cast<float>(rand() % 1024));
        }
        //Medium asteroids
        else if (i == 2 || i == 3) {
            mObjects.push_back(std::make_unique<Asteroid>(mTextureHolder.getTexture(static_cast<Textures::ID>((rand() % 2) + 8)), 2));
            mObjects.back()->setPosition(static_cast<float>(rand() % 1280), static_cast<float>(rand() % 1024));
        }
        //Small asteroids
        else {
            mObjects.push_back(std::make_unique<Asteroid>(mTextureHolder.getTexture(static_cast<Textures::ID>((rand() % 2) + 10)), 4));
            mObjects.back()->setPosition(static_cast<float>(rand() % 1280), static_cast<float>(rand() % 1024));
        }
        ++mAsteroids;
    }

    mIsMovingUp = false;
    mIsMovingDown = false;
    mIsMovingLeft = false;
    mIsMovingRight = false;
    mSpace = false;
}

void PlayState::handleEvents(sf::Event event){
    switch (event.type) {
        case sf::Event::Closed:
            mWindow->close();
            break;
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;
        case sf::Event::Resized:
            mWindow->setView(sf::View(sf::FloatRect(0.0f, 0.0f, event.size.width, event.size.height)));
            break;
    }
    }

void PlayState::handlePlayerInput(sf::Keyboard::Key code, bool isPressed) {
    if (code == sf::Keyboard::Key::Up)
        mIsMovingUp = isPressed;
    if (code == sf::Keyboard::Key::Down)
        mIsMovingDown = isPressed;
    if (code == sf::Keyboard::Key::Left)
        mIsMovingLeft = isPressed;
    if (code == sf::Keyboard::Key::Right)
        mIsMovingRight = isPressed;
    if (code == sf::Keyboard::Key::Space)
        mSpace = isPressed;
}

void PlayState::update(sf::Time dt) {
    float vel_x = mPlayer->getVelocity().x;
    float vel_y = mPlayer->getVelocity().y;
    const float window_size_x = mWindow->getView().getSize().x;
    const float window_size_y = mWindow->getView().getSize().y;
    float player_angle = mPlayer->getAngle();
    float player_x = mPlayer->getPosition().x;
    float player_y = mPlayer->getPosition().y;
    float player_radius = mPlayer->getRadius();
    sf::Vector2f velocity(vel_x * cos(player_angle), -vel_y * sin(player_angle));

    //Ako je pritisnuta tipa gore, brod se ubrzava sve do V_MAX
    if (mIsMovingUp)
        if (vel_x < V_MAX && vel_y < V_MAX)
            mPlayer->setVelocity(sf::Vector2f(vel_x + 10.0f, vel_y + 10.0f));

    //Ako je pritisnuta tipa dolje, brod usporava
    if (mIsMovingDown) {
        if (vel_x > 20.0f && vel_y > 20.0f)
            mPlayer->setVelocity(sf::Vector2f(vel_x - 20.0f, vel_y - 20.0f));
        else mPlayer->setVelocity(sf::Vector2f(0.0f, 0.0f));
    }

    if (mIsMovingLeft) {
        mPlayer->playerRotate(150, dt.asSeconds(), false, false);
    }
    if (mIsMovingRight)
        mPlayer->playerRotate(150, dt.asSeconds(), true, false);

    //Pucanje 
    if (mSpace) {
        ++PlayState::mShoot;
        if (PlayState::mShoot > SHOOT_RESET)
            PlayState::mShoot = 1;
        if ((PlayState::mShoot) % 9 == 0) {
            mObjects.push_back(std::make_unique<Bullet>(mTextureHolder.getTexture(Textures::bullet),
                mPlayer->getPosition().x, mPlayer->getPosition().y, player_angle));
        }
        if (!mLives || !mAsteroids) {
            mpGame->setState(Score);
        }

    }

    float asteroid_collide_x;
    float asteroid_collide_y;
    //Brisanje asteroida ako su se sudarili s player-om
    mObjects.erase(std::remove_if(mObjects.begin(), mObjects.end(),
        [&](decltype(*mObjects.begin()) object) {
            if (typeid(*object) == typeid(Asteroid)) {
                if (object->checkCollision(player_x, player_y, player_radius)) {
                    mCollision = true;
                    asteroid_collide_x = object->getPosition().x;
                    asteroid_collide_y = object->getPosition().y;
                    return true;
                }
                return false;
            }
            return false;
        }),
        mObjects.end());

    //Ako se dogodila kolizija igraca i asteroida, ubacujemo eksploziju u listu
    if (mCollision) {
        --mAsteroids;
        mObjects.push_back(std::make_unique<Animation>(mTextureHolder.getTexture(Textures::explosion), 4, 4, 256, 256, 0.2f)),
            mObjects.back()->setPosition(asteroid_collide_x, asteroid_collide_y);
        mText_1.reset(new sf::Text("Lives: " + std::to_string(--mLives), mFont, FONT_SIZE_BIG));
        mText_1->setPosition(TEXT_1_X, TEXT_1_Y);
        mCollision = false;
        //Dodano poslije roka
        mPlayer->setPosition(window_size_x / 2, window_size_y / 2); 
        mPlayer->setVelocity(sf::Vector2f(0, 0)); 
        mPlayer->playerRotate(0.f, 0.f, false, true); 
    }

    //Nalazimo prvi metak u listi
    auto bullet_it = find_if(mObjects.begin(), mObjects.end(), [](decltype(*mObjects.begin()) object) {
        return typeid(*object) == typeid(Bullet);});
    mCollision = false;
    for (auto asteroid = mObjects.begin(); asteroid != bullet_it;) {
        //Ako nema metaka -> nema kolizije
        if (bullet_it == mObjects.end()) break;
        //Svi asteroidi su na pocetku liste
        if (typeid(**asteroid) != typeid(Asteroid)) break;

        for (auto bullet = bullet_it; bullet != mObjects.end();) {
            if (typeid(**bullet) != typeid(Bullet)) {
                ++bullet;
                continue;
            }
            //Kolizija
            if ((*asteroid)->checkCollision((*bullet)->getPosition().x, (*bullet)->getPosition().y, (*bullet)->getRadius()))
            {
                --mAsteroids;
                mCollision = true;
                size_t size = (*asteroid)->getSize();
                //BIG_SIZE = 1 MEDIUM_SIZE = 2 SMALL_SIZE = 4
                mScore += size * 10;
                mText_2.reset(new sf::Text("Score: " + std::to_string(mScore), mFont, FONT_SIZE_BIG));
                mText_2->setPosition(TEXT_2_X, TEXT_2_Y);
                mObjects.erase(bullet);
                float old_x = (*asteroid)->getPosition().x;
                float old_y = (*asteroid)->getPosition().y;
                //Ako je veliki asteroid pogodjen stvaramo dva manja
                if (size == ASTEROID_BIG) {
                    mAsteroids += 2;
                    float new_x_1 = old_x + 10;
                    float new_y_1 = old_y + 10;
                    float new_x_2 = old_x - 10;
                    float new_y_2 = old_y + 10;
                    mObjects.push_front(std::make_unique<Asteroid>(mTextureHolder.getTexture(static_cast<Textures::ID>((rand() % 2) + 10)), 4));
                    mObjects.front()->setPosition(new_x_1, new_y_1);
                    sf::Vector2f previous_vel = mObjects.front()->getVelocity();
                    mObjects.push_front(std::make_unique<Asteroid>(mTextureHolder.getTexture(static_cast<Textures::ID>((rand() % 2) + 10)), 4));
                    mObjects.front()->setPosition(new_x_2, new_y_2);
                    sf::Vector2f new_vel(previous_vel.x - 2 * previous_vel.x, previous_vel.y - 2 * previous_vel.y);
                    mObjects.front()->setVelocity(new_vel);
                }
                mObjects.push_back(std::make_unique<Animation>(mTextureHolder.getTexture(Textures::explosion), 4, 4, 256, 256, 0.2f));
                mObjects.back()->setPosition(old_x, old_y);
                break;
            }
            else
                ++bullet;
        }
        //Ako se dogodila kolizija -> zavrsavamo
        //To mozemo dopustiti jer update() izvrsvamo puno puta u relativno malom vremenskom intervalu
        if (mCollision) {
            mObjects.erase(asteroid);
            mCollision = false;
            break;
        }
        else
            ++asteroid;  
    }

    //Brisanje metaka iz vektora ako odlutaju izvan granica window-a
    mObjects.erase(std::remove_if(mObjects.begin(), mObjects.end(),
        [&window_size_x](decltype(*mObjects.begin()) object) {
            if (typeid(*object) == typeid(Bullet)) {
                return object->getPosition().x > window_size_x || object->getPosition().x < 0;
            }
            return false;
        }),
        mObjects.end());

    //Brisanje metaka iz vektora ako odlutaju izvan granica window-a
    mObjects.erase(std::remove_if(mObjects.begin(), mObjects.end(),
        [&window_size_y](decltype(*mObjects.begin()) object) {
            if (typeid(*object) == typeid(Bullet)) {
                return object->getPosition().y > window_size_y || object->getPosition().y < 0;
            }
            return false;
        }),
        mObjects.end());

    //Brisanje eksplozija
    mObjects.erase(std::remove_if(mObjects.begin(), mObjects.end(),
        [&window_size_y](decltype(*mObjects.begin()) object) {
            if (typeid(*object) == typeid(Animation) && !object->isAlive)
                return true;
            return false;
        }),
        mObjects.end());

    //Update objekata(osim playera)
    //Animaciju uvijek update-amo, ostalo update-amo samo ako je preostalo zivota
    for (auto& object : mObjects) {
        if (typeid(*object) == typeid(Animation) || mLives) {
            object->checkCoordinates(window_size_x, window_size_y);
            object->update(dt);
        }
    }

    //Ako igra traje pomicemo igraca
    if (mLives && mAsteroids) {
        mPlayer->move(velocity * dt.asSeconds());
        mPlayer->checkCoordinates(window_size_x, window_size_y);
    }
    else {
        mpGame->gameScore = mScore;
        mpGame->gameLives = mLives;
        mpGame->setState(Score);
    }

}

void PlayState::render() {  
    mWindow->draw(mBackgroundSprite);
   
    if (mLives && mAsteroids)
        mWindow->draw(*mPlayer);

    for (auto& object : mObjects)
        mWindow->draw(*object);

    mWindow->draw(*mText_1);
    mWindow->draw(*mText_2); 
}


