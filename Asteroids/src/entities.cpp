#include "entities.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
// Dopuniti po potrebi.

Entity::Entity(sf::Texture const& texture) {
    mSprite.setTexture(texture);
    auto lb = mSprite.getLocalBounds();
    mSprite.setOrigin(lb.width / 2, lb.height / 2);
    mVelocity.x = mVelocity.y = 30.0f;
    isAlive = true;

    mRadius = 1.0 * std::min(lb.width / 2, lb.height / 2);
    mCircle.setRadius(mRadius);
    mCircle.setFillColor(sf::Color(0, 255, 0, 0));
    mCircle.setOutlineThickness(1);
    mCircle.setOutlineColor(sf::Color::Yellow);
    mCircle.setOrigin(mRadius, mRadius);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mSprite, states);
    //target.draw(mCircle, states);
}

//Ako entity izadje iz prozora, sljedeca funkcija ga vraca na torus
void Entity::checkCoordinates(const float& window_width, const float& window_height) {
    float entity_x = getPosition().x;
    float entity_y = getPosition().y;

    if (entity_x > window_width)
        setPosition(0, entity_y);
    if (entity_x < 0)
        setPosition(window_width, entity_y);

    if (entity_y > window_height)
        setPosition(entity_x, 0);
    if (entity_y < 0)
        setPosition(entity_x, window_height);
}

bool Entity::checkCollision(float x, float y, float radius) {
    float asteroid_x = getPosition().x;
    float asteroid_y = getPosition().y;
    float distance = sqrt(pow(x - asteroid_x, 2) + pow(y - asteroid_y, 2));
    if (distance <= radius + mRadius)
        return true;
    return false;
}

void Entity::update(sf::Time dt) {
    auto pos = getPosition();
    float x = pos.x + mVelocity.x * dt.asSeconds();
    float y = pos.y + mVelocity.y * dt.asSeconds();
    setPosition(x, y);
}

Animation::Animation(sf::Texture const& texture, int rows, int cols, int width, int height, float vel) :
    Entity(texture), mRows(rows), mCols(cols), mWidth(width / cols), mHeight(height / rows), mSpeed(vel),
    mCurrentCol(0.0f), mCurrentRow(0) {
    auto lb = mSprite.getLocalBounds();
    mSprite.setOrigin(lb.width/8, lb.height/8);

}

void Animation::update(sf::Time dt) {
    if (!isAlive) return;
    mCurrentCol += mSpeed;
    if (static_cast<int>(mCurrentCol) == mCols) {
        mCurrentCol = 0.0f;
        ++mCurrentRow;
    }
    if (mCurrentRow == mRows) {
        mCurrentCol = 0.0f;
        mCurrentRow = 0;
        isAlive = false;
        return;
    }

    int i = mCurrentCol;
    int j = mCurrentRow;
    mSprite.setTextureRect(sf::IntRect(i * mWidth, j * mHeight, mWidth, mHeight));
}

Asteroid::Asteroid(const sf::Texture& texture, size_t size) : Entity(texture), size(size) {
    //Random brzina asteroida
    mVelocity.x = static_cast<float>((rand() % 300) - 150);
    mVelocity.y = static_cast<float>((rand() % 300) - 150);
    if (abs(mVelocity.x) < 50.0f)
        if (mVelocity.x < 0.0f)
            mVelocity.x -= 50.0f;
        else mVelocity.x += 50.0f;

    if (abs(mVelocity.y) < 50.0f)
        if (mVelocity.y < 0.0f)
            mVelocity.y -= 50.0f;
        else mVelocity.y += 50.0f;

}

void Asteroid::update(sf::Time dt) {
    rotate(200 * dt.asSeconds());
    auto pos = getPosition();
    float x = pos.x + mVelocity.x * dt.asSeconds();
    float y = pos.y + mVelocity.y * dt.asSeconds();
    setPosition(x, y);

}

Player::Player(const sf::Texture& texture) : Entity(texture) {
    mSprite.setOrigin(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2);
    setVelocity(sf::Vector2f(0, 0));
}


//Rotacija broda
void Player::playerRotate(float ang, float sec, bool right, bool restart) {
    if (restart) {
        angle = PI / 2.0f;  //Dodano poslije roka
        setRotation(angle); //Dodano poslije roka
    }
    if (right) {
        angle -= (ang / 60.0f) * PI / 180.0f;
        rotate(ang * sec);
    }
    else {
        angle += (ang / 60.0f) * PI / 180.0f;
        rotate(-ang * sec);
    }
    if (angle > 2.0f * PI) angle -= 2.0f * PI;
}

Bullet::Bullet(const sf::Texture& texture, float coord_x, float coord_y, float player_angle) : Entity(texture) {
    setRotation(-player_angle * 180.0f / PI);
    setPosition(coord_x, coord_y);
    setVelocity(sf::Vector2f(static_cast<float>(800 * cos(player_angle)), static_cast<float>(-800 * sin(player_angle))));
}




