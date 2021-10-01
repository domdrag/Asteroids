#include "textureHolder.h"
#include <stdexcept>

// Ne treba mijenjati
TextureHolder::TextureHolder() {
    setFileNames();
    mTextures.resize(Textures::size);
    for (int i = 0; i < Textures::size; ++i) {
        mTextures[i].reset(new sf::Texture);
        if (!mTextures[i]->loadFromFile(mFileNames[i]))
            throw std::runtime_error("Cannot open file " + mFileNames[i]);
    }
}


void TextureHolder::setFileNames() {
    mFileNames.resize(Textures::size);
    mFileNames[Textures::background] = "data/bg5.jpg";
    mFileNames[Textures::player] = "data/playerShip3_blue.png";
    mFileNames[Textures::bullet] = "data/bullet.png";
    mFileNames[Textures::explosion] = "data/exp2_0.png";
    mFileNames[Textures::meteorBig1] = "data/meteorBrown_big1.png";
    mFileNames[Textures::meteorBig2] = "data/meteorBrown_big2.png";
    mFileNames[Textures::meteorBig3] = "data/meteorBrown_big3.png";
    mFileNames[Textures::meteorBig4] = "data/meteorBrown_big4.png";
    mFileNames[Textures::meteorMedium1] = "data/meteorBrown_med1.png";
    mFileNames[Textures::meteorMedium2] = "data/meteorBrown_med2.png";
    mFileNames[Textures::meteorSmall1] = "data/meteorBrown_small1.png";
    mFileNames[Textures::meteorSmall2] = "data/meteorBrown_small2.png";
}
 