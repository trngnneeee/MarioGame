﻿#include "MarioGame.h"

/// MAIN FUNCTIONS
void MarioGame::Event(sf::RenderWindow& window, GameState& gameState)
{
	sf::Event event{};
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (gameState == GameState::Playing)
		{
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				gameState = GameState::Paused;
				pauseMenu.Initialize(window); // Khởi tạo menu tạm dừng
			}
		}
		else if (gameState == GameState::Paused)
		{
			pauseMenu.HandleInput(event, gameState, window); 
			if (gameState == GameState::Menu)
			{
				GameReset();
				mario.Reset();
				return;
			}
		}
		else if (gameState == GameState::Menu)
		{
			if (menu.HandleInput(window) == 1)
			{
				Begin(window);
				gameState = GameState::Playing;
			}
		}
	}
}


void MarioGame::Begin(sf::RenderWindow& window)
{
	MusicBegin();
	MapTransitionBegin();
	std::vector<sf::Vector2f> goombasPosition;
	std::vector<sf::Vector2f> koopasPosition;
	std::vector<sf::Vector2f> coinsPosition;
	std::vector<sf::Vector2f> chompersPosition;
	sf::Vector2f marioPosition;
	MapBegin(marioPosition, winPosition, goombasPosition, koopasPosition, coinsPosition, chompersPosition);
	MarioBegin(marioPosition);
	EnemyBegin(goombasPosition, koopasPosition);
	ChomperBegin(chompersPosition);
	CoinBegin(coinsPosition);
	BackgroundBegin();
	GameTimeBegin();
	UICounterBegin();
	CameraBegin();
}

void MarioGame::Update(const float& deltaTime, GameState& gameState, sf::RenderWindow& window)
{
	if (gameState == GameState::Menu)
	{
		// Xử lý menu chính
	}
	else if (gameState == GameState::Playing)
	{
		if (pause) return;

		updateRange = (window.getSize().x * 11.5f) / 1200;

		if (MapTransitionUpdate(deltaTime)) return;

		MusicUpdate();
		MapUpdate(deltaTime);
		MarioUpdate(deltaTime, map, gameState);
		GoombaUpdate(deltaTime, map);
		KoopaUpdate(deltaTime, map);
		ChomperUpdate(deltaTime);
		CoinUpdate(deltaTime);
		GameTimeUpdate(deltaTime);
		UIUpdate(deltaTime);
		CameraUpdate();
		MushroomUpdate(deltaTime, map);
		StarUpdate(deltaTime, map);
		DeadUpdate(gameState);

		if (WinDetect())
		{
			SoundManager::getInstance().stopSound("main");
			SoundManager::getInstance().setPlayedStatus("main", false);
			GameReset();
			Begin(window);
			SoundManager::getInstance().playSound("win");
		}
	}
	else if (gameState == GameState::Paused)
	{
		pauseMenu.Update(deltaTime, window);// Cập nhật PauseMenu
	}
	else if (gameState == GameState::GameOver)
	{
		gameState = GameState::Menu;
	}
}


void MarioGame::Render(sf::RenderWindow& window, GameState& gameState)
{
	if (gameState == GameState::Menu)
	{
		window.setView(window.getDefaultView());
		MenuDraw(window);
	}
	else if (gameState == GameState::Playing)
	{
		if (mapTransition.getTimer() > 0)
		{
			window.setView(window.getDefaultView());
			MapTransitionDraw(window);
			return;
		}
		window.setView(camera.GetView(window.getSize(), map.getCellSize() * map.getGrid().size()));
		BackgroundDraw(window);
		HiddenBoxItemDraw(window);
		ChomperDraw(window);
		MapDraw(window);
		MarioDraw(window);
		EnemyDraw(window);
		CoinDraw(window);
		UIDraw(window);
	}
	else if (gameState == GameState::Paused)
	{
		if (mapTransition.getTimer() > 0)
		{
			window.setView(window.getDefaultView());
			MapTransitionDraw(window);
			return;
		}
		window.setView(camera.GetView(window.getSize(), map.getCellSize() * map.getGrid().size()));
		BackgroundDraw(window);
		HiddenBoxItemDraw(window);
		ChomperDraw(window);
		MapDraw(window);
		MarioDraw(window);
		EnemyDraw(window);
		CoinDraw(window);
		UIDraw(window);
		window.setView(window.getDefaultView());
		pauseMenu.Render(window); // Vẽ giao diện tạm dừng
	}
	else if (gameState == GameState::GameOver)
	{
	}
}

/// HELPER FUNCTIONS
/// Begin Function
void MarioGame::MusicBegin()
{
	SoundManager& soundManager = SoundManager::getInstance();
	soundManager.loadSound("main", "./resources/soundEffect/music.ogg");
	soundManager.loadSound("dead", "./resources/soundEffect/dead.ogg");
	soundManager.loadSound("levelUp", "./resources/soundEffect/level-up.ogg");
	soundManager.loadSound("win", "./resources/soundEffect/win.ogg");
	soundManager.loadSound("coin", "./resources/soundEffect/coin.ogg");
	soundManager.loadSound("goomba", "./resources/soundEffect/goomba.ogg");
	soundManager.loadSound("life-up", "./resources/soundEffect/mario-up.ogg");
	soundManager.loadSound("kick", "./resources/soundEffect/kick.wav");
	soundManager.loadSound("item", "./resources/soundEffect/item.wav");
	soundManager.loadSound("gameover", "./resources/soundEffect/gameover.wav");

	soundManager.loadSound("brick", "./resources/soundEffect/brick.wav");
	soundManager.setVolume("brick", 100);

	soundManager.loadSound("jump", "./resources/soundEffect/jump.wav");
	soundManager.setVolume("jump", 20);
}

void MarioGame::MapTransitionBegin()
{
	mapTransition.Begin();
}

void MarioGame::MapBegin(sf::Vector2f& marioPosition, sf::Vector2f& winPosition, std::vector<sf::Vector2f>& goombasPosition, std::vector<sf::Vector2f>& koopasPosition, std::vector<sf::Vector2f>& coinsPosition, std::vector<sf::Vector2f>& chompersPosition)
{
	map = Map(1.0f);
	int mapType = mario.getMapArchive();
	std::string mapName = "";
	if (mapType == 1)
		mapName = "map1.png";
	else if (mapType == 2)
		mapName = "map2.png";
	else if (mapType == 3)
		mapName = "map3.png";
	mapTransition.setMapType(mapType);
	map.Begin(mapName);
	map.CreateFromImage(marioPosition, winPosition, goombasPosition, koopasPosition, coinsPosition, chompersPosition);

	map.CreateCollisionBox();
}

void MarioGame::MarioBegin(const sf::Vector2f& marioPosition)
{
	mario.Begin(marioPosition);
}

void MarioGame::EnemyBegin(const std::vector<sf::Vector2f>& goombasPosition, const std::vector<sf::Vector2f>& koopasPosition)
{
	int mapType = mario.getMapArchive();
	EnemyFactory factory;
	for (int i = 0; i < goombasPosition.size(); i++)
	{
		Enemy* newEnemy = factory.createEnemy("Goomba");
		if (newEnemy)
		{
			newEnemy->Begin(goombasPosition[i]);
			goombas.push_back(static_cast<Goombas*>(newEnemy));
			static_cast<Goombas*>(newEnemy)->setSpeedBasedOnMapType(mapType);
		}
	}
	for (int i = 0; i < koopasPosition.size(); i++)
	{
		Enemy* newEnemy = factory.createEnemy("Koopa");
		if (newEnemy)
		{
			newEnemy->Begin(koopasPosition[i]);
			koopas.push_back(static_cast<Koopa*>(newEnemy));
			static_cast<Goombas*>(newEnemy)->setSpeedBasedOnMapType(mapType);
		}
	}
}

void MarioGame::ChomperBegin(const std::vector<sf::Vector2f>& chompersPosition)
{
	for (int i = 0; i < chompersPosition.size(); i++)
	{
		Chomper* newChomper = new Chomper;
		newChomper->Begin(chompersPosition[i]);
		chompers.push_back(newChomper);
	}
}

void MarioGame::CoinBegin(const std::vector<sf::Vector2f>& coinsPosition)
{
	for (int i = 0; i < coinsPosition.size(); i++)
	{
		auto newCoin = std::make_unique<Coin>();
		newCoin->Begin(coinsPosition[i]);
		coins.push_back(std::move(newCoin));
	}
}

void MarioGame::BackgroundBegin()
{
	background.Begin(camera.getZoomlevel(), map);
}

void MarioGame::GameTimeBegin()
{
	gameTime.Begin();
}

void MarioGame::UICounterBegin()
{
	UI.Begin();
}

void MarioGame::CameraBegin()
{
	camera = Camera(16.0f);
}

void MarioGame::MenuBegin(sf::RenderWindow& window)
{
	menu.Begin(window);
}

/// Update Function
void MarioGame::MusicUpdate()
{
	if (!SoundManager::getInstance().getPlayedStatus("main"))
	{
		SoundManager::getInstance().playSound("main");
		SoundManager::getInstance().setPlayedStatus("main", true);
		SoundManager::getInstance().setLoop("main", true);
		SoundManager::getInstance().setVolume("main", 50);
	}
}

bool MarioGame::MapTransitionUpdate(const float& deltaTime)
{
	if (mapTransition.getTimer() > 0)
	{
		mapTransition.Update(deltaTime);
		return true;
	}
	else return false;
}

void MarioGame::MapUpdate(const float& deltaTime)
{
	map.Update(deltaTime);
}

void MarioGame::MarioUpdate(const float& deltaTime, Map& map, GameState& gameState)
{
	// Collision with goomba
	for (int i = 0; i < goombas.size(); i++)
	{
		if (goombas[i]->getDieStatus() == false && goombas[i]->getDieByKoopaStatus() == false && mario.goombasCollision(*goombas[i]))
		{
			if (mario.getInvicibleTime2() > 0)
				goombas[i]->setDieByKoopaStatus(true);
			else
			{
				if (mario.getLevelUpStatus() == false && mario.getInvicibleTime() <= 0)
					mario.setDeadStatus(true);
				else
				{
					if (mario.getInvicibleTime() <= 0)
						mario.setInvicibleTime(2.0f);
					mario.setLevelUpStatus(false);
				}
			}
		}
	}
	// Collision with koopa
	for (int i = 0; i < koopas.size(); i++)
	{
		if (mario.koopaCollision(*koopas[i]))
		{
			if (!koopas[i]->getInShellStatus())
			{
				if (mario.getInvicibleTime2() > 0)
					koopas[i]->setDieStatus(true);
				else
				{
					if (mario.getLevelUpStatus() == false && mario.getInvicibleTime() <= 0)
						mario.setDeadStatus(true);
					else
					{
						if (mario.getInvicibleTime() <= 0)
							mario.setInvicibleTime(2.0f);
						mario.setLevelUpStatus(false);
					}
				}
			}
		}
	}
	// Collision with chomper
	for (int i = 0; i < chompers.size(); i++)
	{
		if (mario.chomperCollision(*chompers[i]))
		{
			if (mario.getInvicibleTime2() > 0) continue;
			else
			{
				if (mario.getLevelUpStatus() == false && mario.getInvicibleTime() <= 0)
					mario.setDeadStatus(true);
				else
				{
					if (mario.getInvicibleTime() <= 0)
						mario.setInvicibleTime(2.0f);
					mario.setLevelUpStatus(false);
				}
			}
		}
	}
	mario.Update(deltaTime, map, mushrooms, stars);
}

void MarioGame::GoombaUpdate(const float& deltaTime, const Map& map)
{
	for (int i = 0; i < goombas.size(); i++)
	{
		for (int j = 0; j < goombas.size(); j++)
		{
			if (i != j)
			{
				if (goombas[i]->teamCollision(*goombas[j]))
				{
					goombas[i]->handleTeamCollision();
					goombas[j]->handleTeamCollision();
				}
			}
		}
		if (mario.distanceX(*goombas[i]) <= updateRange || goombas[i]->getGameState() == true)
		{
			if (goombas[i]->getGameState() == false)
			{
				goombas[i]->setGameState(true);
			}
			goombas[i]->Update(deltaTime, map);
		}
	}
	// Remove die goomba
	goombas.erase(
		std::remove_if(goombas.begin(), goombas.end(),
			[](const auto& goomba) {
				return (goomba->getDieStatus() && goomba->getDieTime() <= 0) ||
					goomba->getPosition().y >= 16.0f;
			}),
		goombas.end());
}

void MarioGame::KoopaUpdate(const float& deltaTime, const Map& map)
{
	for (int i = 0; i < koopas.size(); i++)
	{
		// Collision with Goomba
		for (int j = 0; j < goombas.size(); j++)
		{
			if (goombas[j]->koopaCollision(*koopas[i]))
			{
				if (goombas[j]->getDieByKoopaStatus() == false)
					mario.setPoints(mario.getPoints() + 200);
				goombas[j]->setDieByKoopaStatus(true);
			}
		}
		// Collision with other koopa
		for (int j = 0; j < koopas.size(); j++)
		{
			if (i != j)
			{
				if (koopas[i]->teamCollision(*koopas[j]))
				{
					if (koopas[j]->getDieStatus() == false)
						mario.setPoints(mario.getPoints() + 200);
					koopas[j]->setDieStatus(true);
				}
			}
		}
		if (mario.distanceX(*koopas[i]) <= updateRange || koopas[i]->getGameState() == true)
		{
			if (koopas[i]->getGameState() == false)
			{
				koopas[i]->setGameState(true);
			}
			koopas[i]->Update(deltaTime, map);
		}
	}
	// Remove die koopa
	koopas.erase(
		std::remove_if(koopas.begin(), koopas.end(),
			[](const auto& koopa) {
				return (koopa->getDieStatus() && koopa->getDieTime() <= 0) ||
					koopa->getPosition().y >= 16.0f;
			}),
		koopas.end());
}

void MarioGame::ChomperUpdate(const float& deltaTime)
{
	for (int i = 0; i < chompers.size(); i++)
	{
		chompers[i]->Update(deltaTime);
	}
}

void MarioGame::CoinUpdate(const float& deltaTime)
{
	for (int i = 0; i < coins.size(); i++)
	{
		if (mario.coinCollision(*coins[i]))
		{
			if (coins[i]->isCollected() == false)
			{
				SoundManager::getInstance().playSound("coin");
				mario.setPoints(mario.getPoints() + 100);
				mario.setCoin(mario.getCoin() + 1);
				coins[i]->setCollected(true);
			}
		}
		coins[i]->Update(deltaTime);
	}
	// Remove collected coin
	coins.erase(
		std::remove_if(coins.begin(), coins.end(),
			[](const auto& coin) {
				return coin->isCollected() && coin->getDisapperTime() <= 0;
			}),
		coins.end());
}

void MarioGame::GameTimeUpdate(const float& deltaTime)
{
	gameTime.Update(deltaTime);
	if (gameTime.getGameTime() < 0)
	{
		mario.setDeadStatus(true);
		gameTime.setGameTime(0);
	}
}

void MarioGame::UIUpdate(const float& deltaTime)
{
	UI.Update(deltaTime, camera, mario.getPoints(), mario.getLife(), mario.getCoin(), gameTime.getGameTime());
}

void MarioGame::CameraUpdate()
{
	camera.setPosition(mario.getPosition());
}

void MarioGame::MushroomUpdate(const float& deltaTime, const Map& map)
{
	for (int i = 0; i < mushrooms.size(); i++)
	{
		if (mario.mushroomCollision(*mushrooms[i]) && mushrooms[i]->getDeadStatus() == false && mushrooms[i]->getOutStatus() == true)
		{
			mario.setPoints(mario.getPoints() + 1000);
			if (mario.getLevelUpStatus() == false)
			{
				SoundManager::getInstance().playSound("levelUp");
				mario.setLevelUpStatus(true);
				mario.setPosition(sf::Vector2f(mario.getPosition().x, mario.getPosition().y - 1.0f));
			}
			else
			{
				SoundManager::getInstance().playSound("life-up");
				mario.setLife(mario.getLife() + 1);
			}
			mushrooms[i]->setDeadStatus(true);
		}
		mushrooms[i]->Update(deltaTime, map);
	}
	// Remove die mushroom
	mushrooms.erase(
		std::remove_if(mushrooms.begin(), mushrooms.end(),
			[](const auto& item) {
				return (item->getDeadStatus() && item->getDieTime() <= 0) ||
					item->getPosition().y >= 16.0f;
			}),
		mushrooms.end());
}

void MarioGame::StarUpdate(const float& deltaTime, const Map& map)
{
	for (int i = 0; i < stars.size(); i++)
	{
		if (mario.starCollision(*stars[i]) && stars[i]->getDeadStatus() == false && stars[i]->getOutStatus() == true)
		{
			mario.setPoints(mario.getPoints() + 1000);
			stars[i]->setDeadStatus(true);
			mario.setInvicibleTime2(10.0f);
		}
		stars[i]->Update(deltaTime, map);
	}
	// Remove die star
	stars.erase(
		std::remove_if(stars.begin(), stars.end(),
			[](const auto& star) {
				return (star->getDeadStatus() && star->getDieTime() <= 0) ||
					star->getPosition().y >= 16.0f;
			}),
		stars.end());
}

void MarioGame::DeadUpdate(GameState& gameState)
{
	if (mario.getDeadStatus() == true)
	{
		SoundManager::getInstance().stopSound("main");
		SoundManager::getInstance().setPlayedStatus("main", false);
		if (SoundManager::getInstance().getPlayedStatus("dead") == false)
		{
			SoundManager::getInstance().playSound("dead");
			SoundManager::getInstance().setPlayedStatus("dead", true);
		}
		if (mario.getDeadTimer() <= 0)
		{
			if (mario.getLife() > 0)
			{
				mario.ResetAfterDead();
			}
			if (mario.getLife() <= 0)
			{
				GameReset();
				mario.Reset();
				gameState = GameState::GameOver;
			}
			SoundManager::getInstance().setPlayedStatus("dead", false);
		}
	}
}

bool MarioGame::WinDetect()
{
	if (mario.getPosition().x >= winPosition.x)
	{
		mario.setMapArchive(mario.getMapArchive() + 1);
		mario.ResetAfterWin();
		mapTransition.setMapType(mapTransition.getMapType() + 1);
		mapTransition.setTimer(5.5f);	
		return true;
	}
	return false;
}

/// Draw function
void MarioGame::MapTransitionDraw(sf::RenderWindow& window)
{
	mapTransition.Draw(window);
}

void MarioGame::MenuDraw(sf::RenderWindow& window)
{
	menu.Draw(window);
}

void MarioGame::BackgroundDraw(sf::RenderWindow& window)
{
	background.Draw(window);
}

void MarioGame::UIDraw(sf::RenderWindow& window)
{
	if (mapTransition.getTimer() > 0) return;
	window.setView(camera.GetUIView());
	UI.Draw(window);
}

void MarioGame::MapDraw(sf::RenderWindow& window)
{
	map.Draw(window);
}

void MarioGame::HiddenBoxItemDraw(sf::RenderWindow& window)
{
	for (int i = 0; i < mushrooms.size(); i++)
	{
		mushrooms[i]->Draw(window);
	}
	for (int i = 0; i < stars.size(); i++)
	{
		stars[i]->Draw(window);
	}
}

void MarioGame::MarioDraw(sf::RenderWindow& window)
{
	mario.Draw(window);
}

void MarioGame::EnemyDraw(sf::RenderWindow& window)
{
	for (int i = 0; i < goombas.size(); i++)
	{
		goombas[i]->Draw(window);
	}
	for (int i = 0; i < koopas.size(); i++)
	{
		koopas[i]->Draw(window);
	}
}

void MarioGame::ChomperDraw(sf::RenderWindow& window)
{
	for (int i = 0; i < chompers.size(); i++)
	{
		chompers[i]->Draw(window);
	}
}

void MarioGame::CoinDraw(sf::RenderWindow& window)
{
	for (int i = 0; i < coins.size(); i++)
	{
		coins[i]->Draw(window);
	}
}

/// Reset Functions
void MarioGame::GameReset()
{
	/// Reset map
	map.Reset();
	/// Reset enemy
	// Reset goomba
	for (int i = 0; i < goombas.size(); i++)
	{
		goombas[i]->Reset();
		delete goombas[i];
	}
	goombas.clear();
	// Reset koopa
	for (int i = 0; i < koopas.size(); i++)
	{
		koopas[i]->Reset();
		delete koopas[i];
	}
	koopas.clear();
	// Reset chomper
	for (int i = 0; i < chompers.size(); i++)
	{
		chompers[i]->Reset();
		delete chompers[i];
	}
	chompers.clear();
	/// Reset Mushroom
	for (int i = 0; i < mushrooms.size(); i++)
	{
		mushrooms[i]->Reset();
		delete mushrooms[i];
	}
	mushrooms.clear();
	/// Reset Star
	for (int i = 0; i < stars.size(); i++)
	{
		stars[i]->Reset();
		delete stars[i];
	}
	stars.clear();
	/// Reset coin
	for (int i = 0; i < coins.size(); i++)
	{
		coins[i]->Reset();
	}
	coins.clear();
	/// Reset music
}