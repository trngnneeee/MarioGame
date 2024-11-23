#include "Coin.h"
#include "Map.h"
#include <iostream>
// Constructor
Coin::Coin(float x, float y, std::vector<sf::Texture>& coinTextures, float cellSize)
    : collected(false), cellSize(cellSize), currentTextureIndex(0) {
    textures = coinTextures;
    sprite.setTexture(textures[currentTextureIndex]);
    sprite.setPosition(x, y);
    if (!coinSoundBuffer.loadFromFile("resources/soundEffect/coin.mp3")) {
        // Kiểm tra lỗi nếu không tải được âm thanh
        std::cerr << "Không thể tải âm thanh coin!" << std::endl;
    }
    coinSound.setBuffer(coinSoundBuffer);
}

// Draw coin if not collected
void Coin::Draw(sf::RenderWindow& window) {
    if (!collected) {
        // Update texture every frame to create a "spinning" effect
        currentTextureIndex = (currentTextureIndex + 1) % textures.size();  // Cycle through the textures
        sprite.setTexture(textures[currentTextureIndex]);

        // Scale the sprite to fit the cell size
        float scaleX = cellSize / sprite.getTexture()->getSize().x;
        float scaleY = cellSize / sprite.getTexture()->getSize().y;
        sprite.setScale(scaleX, scaleY);

        // Draw the sprite
        window.draw(sprite);
    }
}

bool Coin::checkCollision(const sf::FloatRect& marioCollisionBox) {
    return sprite.getGlobalBounds().intersects(marioCollisionBox);
}

void Coin::collect(Map& map) {
    collected = true;
    coinSound.play();  // Phát âm thanh khi ăn đồng xu
    map.addFloatingScore(100, sprite.getPosition());  // Thêm điểm vào Map khi ăn đồng xu
}

bool Coin::isCollected() const {
    return collected;

}
