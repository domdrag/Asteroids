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
    mFileNames[Textures::background] = "design/bg5.jpg";
    mFileNames[Textures::player] = "design/playerShip3_blue.png";
    mFileNames[Textures::bullet] = "design/bullet.png";
    mFileNames[Textures::explosion] = "design/exp2_0.png";
    mFileNames[Textures::meteorBig1] = "design/meteorBrown_big1.png";
    mFileNames[Textures::meteorBig2] = "design/meteorBrown_big2.png";
    mFileNames[Textures::meteorBig3] = "design/meteorBrown_big3.png";
    mFileNames[Textures::meteorBig4] = "design/meteorBrown_big4.png";
    mFileNames[Textures::meteorMedium1] = "design/meteorBrown_med1.png";
    mFileNames[Textures::meteorMedium2] = "design/meteorBrown_med2.png";
    mFileNames[Textures::meteorSmall1] = "design/meteorBrown_small1.png";
    mFileNames[Textures::meteorSmall2] = "design/meteorBrown_small2.png";
}
 