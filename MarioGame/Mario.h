#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Map.h"
#include "Animation.h"
#include "Goombas.h"
#include "Koopa.h"
#include "Chomper.h"
#include "Enemy.h"
#include "PowerUpMushroom.h"
#include "InvicibleStar.h"
#include "FireFlower.h"
#include "Coin.h"
#include "SoundManagement.h"
#include "Bullet.h"
#include "FlyingBridge.h"

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
	Animation bigRunAnimation;

	// Texture, Sprite
	std::vector< sf::Texture> textures;
	sf::Sprite sprite;
	std::vector< sf::Texture> bigTexture;
	sf::Sprite bigSprite;

	// Points (Coints)
	int points;

	// Position
	sf::Vector2f startPosition;
	sf::Vector2f position{};
	sf::Vector2f previousPos;

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

	// Map
	int mapArchive;

	// Shooting
	bool shootingAbility;
	std::vector<Bullet*> bullets;
	float shootCooldown;
	float shootCooldownTimer;

	// Swim
	bool isSwimming;
	float outOfWaterTime;
	std::vector<sf::Texture> smallSwimTextures;
	Animation smallSwimAnimation;
	std::vector<sf::Texture> bigSwimTextures;
	Animation bigSwimAnimation;

	// Win
	bool isWinning;
	std::vector<sf::Texture> winTextures;
	Animation smallWinAnimation;
	Animation bigWinAnimation;
public:
	// Constructor
	Mario();

	// Functions
	void Begin(const sf::Vector2f& marioPosition);
	void Update(float deltaTime, Map& map, const std::vector<FlyingBridge*>& bridges);
	void Draw(sf::RenderWindow& window);
	void Reset();
	void ResetAfterDead();
	void ResetAfterWin();

	void HandleMove(float deltaTime, Map& map);
	void HandleBridgeStanding(float deltaTime, std::vector<FlyingBridge*> bridges);
	void updateSwimmingState(float deltaTime);
	void handleSwimming(float deltaTime, Map& map);
	void UpdateCollisionBox();
	void handleJump(float deltaTime);
	void handleHorizontalMove(float deltaTime, Map& map);
	void handleVerticalMove(float deltaTime, Map& map);
	bool handleDead(float deltaTime);
	bool handleOutOfMap();
	void handleBlinkEffect(float deltaTime);
	void handleCollectCoin();
	void handleJumpStrength();
	void UpdateTexture(float deltaTime);
	void handleShoot(float deltaTime);
	void UpdateBullet(const float& deltaTime, const Map& map);
	void DrawBullet(sf::RenderWindow& window);
	void updateFlip();
	float distanceX(const Enemy& enemy);

	// Collsion
	bool mapCollision(Map& map);
	bool outOfMapCollision();
	bool goombasCollision(Goombas& goombas);
	bool koopaCollision(Koopa& koopa);
	bool mushroomCollision(PowerUpMushroom& mushroom);
	bool starCollision(InvicibleStar& star);
	bool flowerCollision(FireFlower& flower);
	bool coinCollision(Coin& coin);
	bool chomperCollision(Chomper& chomper);

	// Getter/Setter
	int getPoints();
	void setPoints(const int& n);
	bool getDeadStatus();
	void setDeadStatus(const bool& value);
	float getDeadTimer();
	sf::Vector2f getPosition();
	sf::Vector2f getStartPosition();
	void setPosition(sf::Vector2f position);
	int getLife();
	void setLife(const int& n);
	sf::FloatRect getCollisionBox() const;
	sf::Vector2f getVelocity();
	void setVelocity(const sf::Vector2f& value);
	bool getLevelUpStatus();
	void setLevelUpStatus(const bool& value);
	float getInvicibleTime();
	void setInvicibleTime(const float& time);
	float getInvicibleTime2();
	void setInvicibleTime2(const float& time);
	int getCoin();
	void setCoin(const int coin);
	int getMapArchive();
	void setMapArchive(const int& value);
	std::vector<Bullet*> getBullets() const;
	bool getShootingStatus();
	void setShootingStatus(const bool& value);
	bool getWinningState();
	void setWinningState(const bool& value);
	float getJumpStrength() const;
	int getFacingRightStatus();
	float getKoopaKickSpeed();
};