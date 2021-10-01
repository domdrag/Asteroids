#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

#define PI static_cast<float>(atan(1)*4)

class Entity : public sf::Drawable, public sf::Transformable {
public:
    Entity(sf::Texture const& texture);
    void setVelocity(sf::Vector2f const& vel) { mVelocity = vel; }
    void checkCoordinates(const float& window_width, const float& window_height);
    virtual bool checkCollision(float x, float y, float radius);
    float getRadius() { return mRadius; }
    virtual size_t getSize() { return false; } //iskljucivo radi asteroida
    sf::Vector2f getVelocity() { return mVelocity; }
    virtual void update(sf::Time dt = sf::Time::Zero);
    virtual ~Entity() {}
    bool isAlive;
protected:
    //Predstavlja samo sliku, svojstva (pozicija itd.) predstavlja sf::Transformable
    sf::Sprite mSprite;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Vector2f mVelocity;
    sf::CircleShape mCircle;
    float mRadius;
};

class Animation : public Entity {
public:
    Animation(sf::Texture const& texture, int rows, int cols, int width, int height, float vel);
    virtual void update(sf::Time dt = sf::Time::Zero)  override;
private:
    int mRows, mCols, mWidth, mHeight;
    float mSpeed;
    float mCurrentCol;
    int mCurrentRow;
};

// dopuniti
class Asteroid : public Entity {
public:
    Asteroid(const sf::Texture& texture, size_t size);
    size_t getSize() override { return size; }
    virtual void update(sf::Time dt = sf::Time::Zero)  override;
private:
    size_t size;
};


// dopuniti
class Player : public Entity {
public:
    Player(const sf::Texture& texture);
    void playerRotate(float angle, float sec, bool right, bool restart);
    float getAngle() { return angle; }
private:
    float angle = PI / 2.0f;

};

class Bullet : public Entity {
public:
    Bullet(const sf::Texture& texture, float coord_x, float coord_y, float player_angle);

};




