#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
class Map;
class Coin {
private:
    sf::Sprite sprite;  // Sprite for the coin
    bool collected;  // Whether the coin is collected or not
    float cellSize;  // Size of each cell (for scaling)
    std::vector<sf::Texture> textures;  // List of textures for the coin
    int currentTextureIndex;  // Index of the current texture
    sf::SoundBuffer coinSoundBuffer; 
    sf::Sound coinSound;

public:
    // Constructor
    Coin(float x, float y, std::vector<sf::Texture>& coinTextures, float cellSize);

    // Functions
    void Draw(sf::RenderWindow& window);
    bool checkCollision(const sf::FloatRect& marioCollisionBox);
    void collect(Map& map);
    bool isCollected() const;
};
