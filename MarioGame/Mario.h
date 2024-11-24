#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Animation.h"
#include "Goombas.h"
#include "Koopa.h"
#include "PowerUpMushroom.h"
#include "InvicibleStar.h"
#include "Coin.h"

class Mario
{
private:
	float gravity;
	bool isOnGround = true;
	float jumpStrength;
	sf::Vector2f velocity;
	float movementSpeed;
	bool facingRight = true;

	// Animation
	Animation runAnimation;

	// Texture, Sprite
	sf::Texture textures[5];
	sf::Sprite sprite;

	// Points (Coints)
	int points;

	// Position
	sf::Vector2f position{};
	sf::Vector2f previousPos;

	// Jump sound
	sf::Music jumpEffect;

	// Box collision
	sf::FloatRect collisionBox;

	// Dead
	bool isDead;
	float deadTimer;
	sf::Texture deadTexture;
	float v;
	float tmpGravity;

	// Life
	int life;

	// Koopa kick speed
	float koopaKickSpeed;

	// Level up (Increase size)
	bool levelUp;
	// Invicible time when shrinking from big size to small size
	float invicibleTime;
	// Invicible time when getting a star
	float invicibleTime2;

	// Coin
	int coin;
public:
	// Constructor
	Mario();

	// Functions
	void Begin(const sf::Vector2f& marioPosition);

	void HandleMove(float deltaTime, Map& map, std::vector<PowerUpMushroom*>& mushroom, std::vector<InvicibleStar*>& stars);
	void HandleHorizontalMove(float deltaTime, Map& map, std::vector<PowerUpMushroom*>& mushroom, std::vector<InvicibleStar*>& stars);
	void HandleVerticalMove(float deltaTime, Map& map, std::vector<PowerUpMushroom*>& mushroom, std::vector<InvicibleStar*>& stars);
	
	void Update(float deltaTime, Map& map, std::vector<PowerUpMushroom*>& mushroom, std::vector<InvicibleStar*>& stars);

	void updateFlip();
	void Draw(sf::RenderWindow& window);

	bool mapCollision(Map& map, std::vector<PowerUpMushroom*>& mushroom, std::vector<InvicibleStar*>& stars);
	bool outOfMapCollision();
	bool goombasCollision(Goombas& goombas);
	bool koopaCollision(Koopa& koopa);
	bool mushroomCollision(PowerUpMushroom& mushroom);
	bool starCollision(InvicibleStar& star);
	bool coinCollision(Coin& coin);

	void Reset();

	// Getter/Setter
	int getPoints();
	void setPoints(const int& n);

	bool getDeadStatus();
	void setDeadStatus(const bool& value);

	float getDeadTimer();

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);

	int getLife();
	void setLife(const int& n);

	sf::FloatRect getCollisionBox() const;

	sf::Vector2f getVelocity();

	bool getLevelUpStatus();
	void setLevelUpStatus(const bool& value);

	float getInvicibleTime();
	void setInvicibleTime(const float& time);

	float getInvicibleTime2();
	void setInvicibleTime2(const float& time);

	int getCoin();
	void setCoin(const int coin);
};