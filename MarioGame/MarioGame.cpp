#include "MarioGame.h"

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
				SoundManager::getInstance().stopSound("main");
				SoundManager::getInstance().playSound("pause");
				pauseMenu.Initialize(window); 
			}
		}
		else if (gameState == GameState::Paused)
		{
			pauseMenu.HandleInput(event, gameState, window); 
			if (gameState == GameState::Menu)
			{
				mapTransition.setTimer(2.0f);
				GameReset();
				mario.Reset();
				return;
			}
		}
		else if (gameState == GameState::LoginMenu)
		{
			if (loginMenu.HandleInput(event, gameState, window) == 1)
			{
				window.clear();
				gameState = GameState::Menu;
			}
		}
		else if (gameState == GameState::Menu)
		{

			int opt = menu.HandleInput(event, window);
			if (opt == 0 || opt == 1 || opt == 2)
			{
				window.clear();
				Begin(window, opt, gameState);
				gameState = GameState::Playing;
			}
			else if (opt == 4)
			{
				gameState = GameState::LoginMenu;
			}
		}
	}
}

void MarioGame::Begin(sf::RenderWindow& window, const int& characterSelected, GameState& gameState)
{
	MusicBegin();
	MapTransitionBegin();
	GameOverBegin();
	std::vector<sf::Vector2f> goombasPosition;
	std::vector<sf::Vector2f> koopasPosition;
	std::vector<sf::Vector2f> coinsPosition;
	std::vector<sf::Vector2f> chompersPosition;
	std::vector<sf::Vector2f> bridgesPosition;
	std::vector<sf::Vector2f> hiddenBoxesPosition;
	std::vector<sf::Vector2f> bricksPosition;
	std::vector<sf::Vector2f> birdsPosition;
	sf::Vector2f marioPosition;
	MapBegin(marioPosition, winPosition, goombasPosition, koopasPosition, coinsPosition, chompersPosition, bridgesPosition, hiddenBoxesPosition, bricksPosition, birdsPosition);
	if (gameState == GameState::GameOver) return;
	MarioBegin(marioPosition, characterSelected);
	EnemyBegin(goombasPosition, koopasPosition, birdsPosition);
	FlyingBridgeBegin(bridgesPosition);
	ChomperBegin(chompersPosition);
	CoinBegin(coinsPosition);
	BrickBegin(bricksPosition);
	HiddenBoxBegin(hiddenBoxesPosition);
	BackgroundBegin();
	GameTimeBegin();
	UICounterBegin();
	CameraBegin();
	FlagBegin(winPosition);
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
		BirdUpdate(deltaTime);
		FlyingBridgeUpdate(deltaTime);
		CoinUpdate(deltaTime);
		BrickUpdate(deltaTime);
		BrickParticleUpdate(deltaTime);
		FloatingScoreUpdate(deltaTime);
		FloatingCoinUpdate(deltaTime);
		HiddenBoxUpdate(deltaTime);
		GameTimeUpdate(deltaTime);
		UIUpdate(deltaTime);
		CameraUpdate();
		MushroomUpdate(deltaTime, map);
		StarUpdate(deltaTime, map);
		FlowerUpdate(deltaTime, map);
		FlagUpdate(deltaTime);
		DeadUpdate(gameState);
		if (WinDetect())
		{
			GameReset();
			// Clear World
			if (mario.getMapArchive() > 3 || mapTransition.getMapType() > 3)
			{
				gameState = GameState::GameOver;
				SoundManager::getInstance().playSound("clear");
				mapTransition.Reset();
				mario.Reset();
				return;
			}
			// Move to next map
			else
			{
				mario.ResetAfterWin();
				Begin(window, mario.getCurrentCharacterSelected(), gameState);
				SoundManager::getInstance().playSound("win");
			}
		}
	}
	else if (gameState == GameState::Paused)
	{
		pauseMenu.Update(deltaTime, window);// Cập nhật PauseMenu
	}
	else if (gameState == GameState::GameOver)
	{
		if (gameOver.isTimeOut())
			gameState = GameState::Menu;
		else
			GameOverUpdate(deltaTime);
	}
}

void MarioGame::Render(sf::RenderWindow& window, GameState& gameState)
{
	if (gameState == GameState::Menu)
	{
		window.setView(window.getDefaultView());
		MenuDraw(window);
	}
	else if (gameState == GameState::LoginMenu)
	{
		window.setView(window.getDefaultView());
		LoginMenuDraw(window);
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
		BrickDraw(window);
		BrickParticleDraw(window);
		FloatingScoreDraw(window);
		FloatingCoinDraw(window);
		HiddenBoxDraw(window);
		FlyingBridgeDraw(window);
		FlagDraw(window);
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
		BrickDraw(window);
		BrickParticleDraw(window);
		FloatingScoreDraw(window);
		FloatingCoinDraw(window);
		HiddenBoxDraw(window);
		FlyingBridgeDraw(window);
		FlagDraw(window);
		MarioDraw(window);
		EnemyDraw(window);
		CoinDraw(window);
		UIDraw(window);
		window.setView(window.getDefaultView());
		pauseMenu.Render(window); // Vẽ giao diện tạm dừng
	}
	else if (gameState == GameState::GameOver)
	{
		window.setView(window.getDefaultView());
		GameOverDraw(window);
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
	soundManager.loadSound("levelDown", "./resources/soundEffect/level-down.wav");
	soundManager.loadSound("bullet", "./resources/soundEffect/bullet.wav");
	soundManager.loadSound("explode", "./resources/soundEffect/explode.wav");
	soundManager.loadSound("flag", "./resources/soundEffect/flag.wav");
	soundManager.loadSound("clear", "./resources/soundEffect/clear-world.wav");
	soundManager.loadSound("pause", "./resources/soundEffect/pause.wav");
	soundManager.loadSound("out-of-time", "./resources/soundEffect/out-of-time.wav");

	soundManager.loadSound("brick", "./resources/soundEffect/brick.wav");
	soundManager.setVolume("brick", 100);

	soundManager.loadSound("jump", "./resources/soundEffect/jump.wav");
	soundManager.setVolume("jump", 20);
}

void MarioGame::MapTransitionBegin()
{
	mapTransition.Begin();
}

void MarioGame::MapBegin(sf::Vector2f& marioPosition, sf::Vector2f& winPosition, std::vector<sf::Vector2f>& goombasPosition, std::vector<sf::Vector2f>& koopasPosition, std::vector<sf::Vector2f>& coinsPosition, std::vector<sf::Vector2f>& chompersPosition, std::vector<sf::Vector2f>& bridgesPosition, std::vector<sf::Vector2f>& hiddenBoxesPosition, std::vector<sf::Vector2f>& bricksPosition, std::vector<sf::Vector2f>& birdsPosition)
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
	map.CreateFromImage(marioPosition, winPosition, endWinPosition, goombasPosition, koopasPosition, coinsPosition, chompersPosition, bridgesPosition, hiddenBoxesPosition, bricksPosition, birdsPosition);
	map.CreateCollisionBox();
}

void MarioGame::MarioBegin(const sf::Vector2f& marioPosition, const int& characterSelected)
{
	mario.Begin(marioPosition, characterSelected);
}

void MarioGame::EnemyBegin(const std::vector<sf::Vector2f>& goombasPosition, const std::vector<sf::Vector2f>& koopasPosition, const std::vector<sf::Vector2f>& birdsPosition)
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
	for (int i = 0; i < birdsPosition.size(); i++)
	{
		Enemy* newEnemy = factory.createEnemy("Bird");
		if (newEnemy)
		{
			newEnemy->Begin(birdsPosition[i]);
			birds.push_back(static_cast<Bird*>(newEnemy));
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

void MarioGame::FlyingBridgeBegin(const std::vector<sf::Vector2f>& bridgesPosition)
{
	// Only treat for map 3
	if (mario.getMapArchive() == 3)
	{
		for (int i = 0; i < bridgesPosition.size() - 1; i++)
		{
			FlyingBridge* newBridge = new FlyingBridge(sf::Vector2f(0.0f, 5.0f), 0.0f, 0.0f, 15.0f, 5.0f);
			newBridge->Begin(bridgesPosition[i]);
			bridges.push_back(newBridge);
		}
		FlyingBridge* newBridge1 = new FlyingBridge(sf::Vector2f(3.0f, 0.0f), bridgesPosition[3].x + 2.0f, bridgesPosition[3].x - 6.0f, 0.0f, 0.0f);
		newBridge1->Begin(bridgesPosition[3]);
		bridges.push_back(newBridge1);
	}
	// Other map
	else
	{
		for (int i = 0; i < bridgesPosition.size(); i++)
		{
			FlyingBridge* newBridge = new FlyingBridge(sf::Vector2f(0.0f, 5.0f), 0.0f, 0.0f, 15.0f, 5.0f);
			newBridge->Begin(bridgesPosition[i]);
			bridges.push_back(newBridge);
		}
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

void MarioGame::BrickBegin(const std::vector<sf::Vector2f>& bricksPosition)
{
	for (int i = 0; i < bricksPosition.size(); i++)
	{
		Brick* newBrick = new Brick;
		newBrick->Begin(bricksPosition[i], 1);
		bricks.push_back(newBrick);
	}
}

void MarioGame::HiddenBoxBegin(const std::vector<sf::Vector2f>& hiddenBoxesPosition)
{
	for (int i = 0; i < hiddenBoxesPosition.size(); i++)
	{
		HiddenBox* newHiddenBox = new HiddenBox;
		newHiddenBox->Begin(hiddenBoxesPosition[i]);
		hiddenBoxes.push_back(newHiddenBox);
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

void MarioGame::LoginMenuBegin(sf::RenderWindow& window)
{
	loginMenu.Begin(window);
}

void MarioGame::GameOverBegin()
{
	gameOver.Begin();
}

void MarioGame::FlagBegin(sf::Vector2f winPosition)
{
	winFlag.Begin(winPosition);
}

/// Update Function
void MarioGame::MusicUpdate()
{
	if (!SoundManager::getInstance().getPlayedStatus("main") && mario.getWinningState() == false)
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

void MarioGame::GameOverUpdate(const float& deltaTime)
{
	gameOver.Update(deltaTime);
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
			// Jump on head
			if (mario.getVelocity().y > 0 && mario.getPosition().y + mario.getCollisionBox().height <= goombas[i]->getPosition().y + goombas[i]->getCollisionBox().height / 2)
			{
				mario.setPoints(mario.getPoints() + 100);
				mario.setVelocity(sf::Vector2f(mario.getVelocity().x, -mario.getJumpStrength() / 2));
				goombas[i]->setDieStatus(true);
				SoundManager::getInstance().playSound("goomba");
			}
			// Kicked by Koopa
			else if (mario.getInvicibleTime2() > 0)
				goombas[i]->setDieByKoopaStatus(true);
			else
			{
				if (mario.getLevelUpStatus() == false && mario.getInvicibleTime() <= 0)
					mario.setDeadStatus(true);
				else
				{
					if (mario.getInvicibleTime() <= 0)
						mario.setInvicibleTime(2.0f);
					if (mario.getLevelUpStatus() == true)
					{
						SoundManager::getInstance().playSound("levelDown");
					}
					mario.setLevelUpStatus(false);
				}
			}
		}
		if ((goombas[i]->getDieStatus() == true || goombas[i]->getDieByKoopaStatus() == true) && (goombas[i]->getAddedFloatingScore() == false))
		{
			FloatingScore* newScore = new FloatingScore(100, goombas[i]->getPosition());
			floatingScore.push_back(newScore);
			goombas[i]->setAddedFloatingScore(true);
		}
	}
	// Collision with koopa
	for (int i = 0; i < koopas.size(); i++)
	{
		if (mario.koopaCollision(*koopas[i]))
		{
			// Jump on head
			if (mario.getVelocity().y > 0 && mario.getPosition().y + mario.getCollisionBox().height <= koopas[i]->getPosition().y + koopas[i]->getCollisionBox().height / 2)
			{
				if (koopas[i]->getInShellStatus() == false)
				{
					SoundManager::getInstance().playSound("goomba");
					mario.setVelocity(sf::Vector2f(mario.getVelocity().x, -mario.getJumpStrength() / 2));
					koopas[i]->setInShellStatus(true);
				}
				else
				{
					mario.setVelocity(sf::Vector2f(mario.getVelocity().x, -mario.getJumpStrength() / 2));
					koopas[i]->setStandTimer(3.0f);
				}
				koopas[i]->setVelocity(sf::Vector2f(0.0f, 0.0f));
			}
			// Kick
			else if (koopas[i]->getInShellStatus() == true)
			{
				if (koopas[i]->getVelocity().x == 0)
				{
					int kickDirection = (!mario.getFacingRightStatus()) ? 1 : -1;
					koopas[i]->setVelocity(sf::Vector2f(mario.getKoopaKickSpeed() * kickDirection, 0));
					SoundManager::getInstance().playSound("kick");
				}
			}
			else
			{
				// Taking Star
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
						if (mario.getLevelUpStatus() == true)
						{
							SoundManager::getInstance().playSound("levelDown");
						}
						mario.setLevelUpStatus(false);
					}
				}
			}
		}
		if (koopas[i]->getDieStatus() == true && koopas[i]->getAddedFloatingScore() == false)
		{
			FloatingScore* newScore = new FloatingScore(100, koopas[i]->getPosition());
			floatingScore.push_back(newScore);
			koopas[i]->setAddedFloatingScore(true);
		}
	}
	// Collision with chomper
	for (int i = 0; i < chompers.size(); i++)
	{
		if (mario.chomperCollision(*chompers[i]) && chompers[i]->getDeadStatus() == false)
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
					if (mario.getLevelUpStatus() == true)
					{
						SoundManager::getInstance().playSound("levelDown");
					}
					mario.setLevelUpStatus(false);
				}
			}
		}
	}
	// Collision with Bird
	for (int i = 0; i < birds.size(); i++)
	{
		if (mario.birdCollision(*birds[i]))
		{
			// Jump on head
			if (mario.getVelocity().y > 0 && mario.getPosition().y + mario.getCollisionBox().height <= birds[i]->getPosition().y + birds[i]->getCollisionBox().height / 2)
			{
				SoundManager::getInstance().playSound("goomba");
				mario.setVelocity(sf::Vector2f(mario.getVelocity().x, -mario.getJumpStrength() / 2));
				birds[i]->setDieStatus(true);
			}
			else if (mario.getInvicibleTime2() > 0) birds[i]->setDieStatus(true);
			else
			{
				if (mario.getLevelUpStatus() == false && mario.getInvicibleTime() <= 0)
					mario.setDeadStatus(true);
				else
				{
					if (mario.getInvicibleTime() <= 0)
						mario.setInvicibleTime(2.0f);
					if (mario.getLevelUpStatus() == true)
					{
						SoundManager::getInstance().playSound("levelDown");
					}
					mario.setLevelUpStatus(false);
				}
			}
		}
		if (birds[i]->getDieStatus() == true && birds[i]->getAddedFloatingScore() == false)
		{
			FloatingScore* newScore = new FloatingScore(300, birds[i]->getPosition());
			floatingScore.push_back(newScore);
			birds[i]->setAddedFloatingScore(true);
		}
	}
	// Collision with Hidden Box
	sf::FloatRect marioCollisionBox = mario.getCollisionBox();
	sf::Vector2f marioVelocity = mario.getVelocity();
	for (int i = 0; i < hiddenBoxes.size(); i++)
	{
		sf::FloatRect hiddenBoxCollisionBox = hiddenBoxes[i]->getCollisionBox();
		if (hiddenBoxCollisionBox.intersects(marioCollisionBox) && hiddenBoxes[i]->getUsedStatus() == false && hiddenBoxes[i]->getBounceStatus() == false)
		{
			if (marioVelocity.y < 0 && marioCollisionBox.top <= hiddenBoxCollisionBox.top + hiddenBoxCollisionBox.height && marioCollisionBox.top >= hiddenBoxCollisionBox.top)
			{
				hiddenBoxes[i]->setBounceStatus(true);
				std::srand(static_cast<unsigned>(std::time(0)));
				int randomNumber = 1 + (std::rand() % 100);
				HiddenBoxItemFactory factory;
				sf::Vector2f position = sf::Vector2f(hiddenBoxes[i]->getPosition().x, hiddenBoxes[i]->getPosition().y);
				/*
					Coin: 80%
					Mushroom: 15%
					Star: 3%
					Flower: 2%
				*/
				if (randomNumber <= 2)
				{
					SoundManager::getInstance().playSound("item");
					HiddenBoxItem* newItem = factory.createItem("Flower");
					if (newItem)
					{
						newItem->Begin(position);
						flowers.push_back(static_cast<FireFlower*>(newItem));
					}
				}
				else if (randomNumber <= 5)
				{
					SoundManager::getInstance().playSound("item");
					HiddenBoxItem* newItem = factory.createItem("Star");
					if (newItem)
					{
						newItem->Begin(position);
						stars.push_back(static_cast<InvicibleStar*>(newItem));
					}
				}
				else if (randomNumber <= 20)
				{
					SoundManager::getInstance().playSound("item");
					HiddenBoxItem* newItem = factory.createItem("Mushroom");
					if (newItem)
					{
						newItem->Begin(position);
						mushrooms.push_back(static_cast<PowerUpMushroom*>(newItem));
					}
				}
				else if (randomNumber <= 100)
				{
					mario.setCoin(mario.getCoin() + 1);
					SoundManager::getInstance().playSound("coin");
					FloatingCoin* newFloatingCoin = new FloatingCoin(hiddenBoxes[i]->getPosition());
					floatingCoin.push_back(newFloatingCoin);
					mario.setPoints(mario.getPoints() + 100);
				}
			}
		}
	}
	// Collision with brick
	for (int i = 0; i < bricks.size(); i++)
	{
		if (mario.getCollisionBox().intersects(bricks[i]->getCollisionBox()))
		{
			if (marioVelocity.y < 0 && marioCollisionBox.top <= bricks[i]->getCollisionBox().top + bricks[i]->getCollisionBox().height && marioCollisionBox.top >= bricks[i]->getCollisionBox().top && mario.getLevelUpStatus() == true)
			{
				bricks[i]->setBounceStatus(true);
			}
		}
	}
	mario.Update(deltaTime, map, bridges);
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
					if (goombas[j]->getDieStatus() == false) goombas[i]->handleTeamCollision();
					if (goombas[i]->getDieStatus() == false) goombas[j]->handleTeamCollision();
				}
			}
		}
		std::vector<Bullet*> bullets = mario.getBullets();
		for (int j = 0; j < bullets.size(); j++)
		{
			if (goombas[i]->bulletCollision(*bullets[j]) && bullets[j]->getExplodeStatus() == false)
			{	
				goombas[i]->setDieByKoopaStatus(true);
				bullets[j]->setAppearTime(0.0f);
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
		std::vector<Bullet*> bullets = mario.getBullets();
		for (int j = 0; j < bullets.size(); j++)
		{
			if (koopas[i]->bulletCollision(*bullets[j]) && bullets[j]->getExplodeStatus() == false)
			{
				koopas[i]->setDieStatus(true);
				bullets[j]->setAppearTime(0.0f);
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
		std::vector<Bullet*> bullets = mario.getBullets();
		for (int j = 0; j < bullets.size(); j++)
		{
			if (chompers[i]->bulletCollision(*bullets[j]))
			{
				chompers[i]->setDeadStatus(true);
				bullets[j]->setAppearTime(0.0f);
			}
		}
		if (chompers[i]->getDeadStatus() == true)
		{
			FloatingScore* newScore = new FloatingScore(200, chompers[i]->getPosition());
			floatingScore.push_back(newScore);
		}
		chompers[i]->Update(deltaTime);
	}
	chompers.erase(
		std::remove_if(chompers.begin(), chompers.end(),
			[](const auto& chomper) {
				return (chomper->getDeadStatus());
			}),
		chompers.end());
}

void MarioGame::BirdUpdate(const float& deltaTime)
{
	for (int i = 0; i < birds.size(); i++)
	{
		std::vector<Bullet*> bullets = mario.getBullets();
		for (int j = 0; j < bullets.size(); j++)
		{
			if (birds[i]->bulletCollision(*bullets[j]) && bullets[j]->getExplodeStatus() == false)
			{
				birds[i]->setDieStatus(true);
				bullets[j]->setAppearTime(0.0f);
			}
		}
		birds[i]->Update(deltaTime, map);
	}
	birds.erase(
		std::remove_if(birds.begin(), birds.end(),
			[](const auto& bird) {
				return (bird->getDieStatus() == true && bird->getDieTime() <= 0);
			}),
		birds.end());
}

void MarioGame::FlyingBridgeUpdate(const float& deltaTime)
{
	for (int i = 0; i < bridges.size(); i++)
	{
		bridges[i]->Update(deltaTime);
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

void MarioGame::BrickUpdate(const float& deltaTime)
{
	for (int i = 0; i < bricks.size();)
	{
		bricks[i]->Update(deltaTime);
		if (bricks[i]->getBrokeStatus() == true)
		{
			SoundManager::getInstance().playSound("brick");
			FloatingScore* newFloatingScore = new FloatingScore(50, bricks[i]->getPosition());
			floatingScore.push_back(newFloatingScore);
			map.handleBrickCollision(bricks[i]->getStartPosition());
			// Spawm brick particles
			for (int j = 0; j < 4; j++)
			{
				sf::Vector2f velocity(
					(std::rand() % 21 - 10), 
					(std::rand() % 21 - 10)
				);
				BrickParticle* newBrickParticle = new BrickParticle;
				newBrickParticle->Begin(bricks[i]->getPosition(), velocity);
				brickParticles.push_back(newBrickParticle);
			}
			delete bricks[i];
			bricks.erase(bricks.begin() + i);

		}
		else
		{
			i++;
		}
	}
}

void MarioGame::BrickParticleUpdate(const float& deltaTime)
{
	for (int i = 0; i < brickParticles.size();)
	{
		brickParticles[i]->Update(deltaTime);
		if (brickParticles[i]->isTimeOut())
		{
			brickParticles[i]->Reset();
			delete brickParticles[i];
			brickParticles.erase(brickParticles.begin() + i);
		}
		else
		{
			i++;
		}
	}
}

void MarioGame::FloatingScoreUpdate(const float& deltaTime)
{
	for (int i = 0; i < floatingScore.size();)
	{
		floatingScore[i]->Update(deltaTime);
		if (floatingScore[i]->isTimeout())
		{
			delete floatingScore[i];
			floatingScore.erase(floatingScore.begin() + i);
		}
		else
		{
			i++;
		}
	}
}

void MarioGame::FloatingCoinUpdate(const float& deltaTime)
{
	for (int i = 0; i < floatingCoin.size();)
	{
		floatingCoin[i]->Update(deltaTime);
		if (floatingCoin[i]->isTimeOut())
		{
			delete floatingCoin[i]; 
			floatingCoin.erase(floatingCoin.begin() + i);
		}
		else
		{
			i++;
		}
	}
}

void MarioGame::HiddenBoxUpdate(const float& deltaTime)
{
	for (int i = 0; i < hiddenBoxes.size(); i++)
	{
		hiddenBoxes[i]->Update(deltaTime);
	}
}

void MarioGame::GameTimeUpdate(const float& deltaTime)
{
	if (mario.getDeadStatus() == false) gameTime.Update(deltaTime);
	if (gameTime.getGameTime() < 0)
	{
		mario.setDeadStatus(true);
		mario.setLife(0);
		gameTime.setGameTime(0);
		SoundManager::getInstance().playSound("out-of-time");
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

void MarioGame::FlowerUpdate(const float& deltaTime, const Map& map)
{
	for (int i = 0; i < flowers.size(); i++)
	{
		if (mario.flowerCollision(*flowers[i]) && flowers[i]->getDeadStatus() == false && flowers[i]->getOutStatus() == true)
		{
			if (mario.getShootingStatus() == false)
			{
				mario.setShootingStatus(true);
				SoundManager::getInstance().playSound("levelUp");
			}
			else
			{
				mario.setLife(mario.getLife() + 1);
				SoundManager::getInstance().playSound("life-up");
			}
			mario.setPoints(mario.getPoints() + 1000);
			flowers[i]->setDeadStatus(true);
		}
		flowers[i]->Update(deltaTime, map);
	}
	// Remove die flower
	flowers.erase(
		std::remove_if(flowers.begin(), flowers.end(),
			[](const auto& flower) {
				return (flower->getDeadStatus() && flower->getDieTime() <= 0) ||
					flower->getPosition().y >= 16.0f;
			}),
		flowers.end());
}

void MarioGame::FlagUpdate(const float& deltaTime)
{
	if (mario.getWinningState() == true)
	{
		winFlag.Update(deltaTime);
	}
}

void MarioGame::DeadUpdate(GameState& gameState)
{
	if (mario.getDeadStatus() == true)
	{
		SoundManager::getInstance().stopSound("main");
		SoundManager::getInstance().setPlayedStatus("main", false);
		if (SoundManager::getInstance().getPlayedStatus("dead") == false && gameTime.getGameTime() > 0.0f)
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
				SoundManager::getInstance().playSound("gameover");
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
		if (mario.getWinningState() == false)
		{
			SoundManager::getInstance().stopSound("main");
			SoundManager::getInstance().setPlayedStatus("main", false);
			mario.setWinningState(true);
			mario.setPosition(winPosition);
			winFlag.setPosition(sf::Vector2f(mario.getPosition().x - 0.5f, mario.getPosition().y));
			SoundManager::getInstance().playSound("flag");
		}
		if (mario.getPosition().y >= endWinPosition.y - 1.0f)
		{
			mario.setMapArchive(mario.getMapArchive() + 1);
			mapTransition.setMapType(mapTransition.getMapType() + 1);
			mapTransition.setTimer(5.5f);
			return true;
		}
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

void MarioGame::LoginMenuDraw(sf::RenderWindow& window)
{
	loginMenu.Draw(window);
}

void MarioGame::GameOverDraw(sf::RenderWindow& window)
{
	gameOver.Draw(window);
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

void MarioGame::BrickDraw(sf::RenderWindow& window)
{
	for (int i = 0; i < bricks.size(); i++)
	{
		bricks[i]->Draw(window);
	}
}

void MarioGame::BrickParticleDraw(sf::RenderWindow& window)
{
	for (int i = 0; i < brickParticles.size(); i++)
	{
		brickParticles[i]->Draw(window);
	}
}

void MarioGame::FloatingScoreDraw(sf::RenderWindow& window)
{
	for (int i = 0; i < floatingScore.size(); i++)
	{
		floatingScore[i]->Draw(window);
	}
}

void MarioGame::FloatingCoinDraw(sf::RenderWindow& window)
{
	for (int i = 0; i < floatingCoin.size(); i++)
	{
		floatingCoin[i]->Draw(window);
	}
}

void MarioGame::HiddenBoxDraw(sf::RenderWindow& window)
{
	for (int i = 0; i < hiddenBoxes.size(); i++)
	{
		hiddenBoxes[i]->Draw(window);
	}
}

void MarioGame::FlagDraw(sf::RenderWindow& window)
{
	winFlag.Draw(window);
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
	for (int i = 0; i < flowers.size(); i++)
	{
		flowers[i]->Draw(window);
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
	for (int i = 0; i < birds.size(); i++)
	{
		birds[i]->Draw(window);
	}
}

void MarioGame::FlyingBridgeDraw(sf::RenderWindow& window)
{
	for (int i = 0; i < bridges.size(); i++)
	{
		bridges[i]->Draw(window);
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
	// Reset bird
	for (int i = 0; i < birds.size(); i++)
	{
		birds[i]->Reset();
		delete birds[i];
	}
	birds.clear();
	/// Reset Floating Score
	for (int i = 0; i < floatingScore.size(); i++)
	{
		delete floatingScore[i];
	}
	floatingScore.clear();
	/// Reset Floating Coin
	for (int i = 0; i < floatingCoin.size(); i++)
	{
		floatingCoin[i]->Reset();
		delete floatingCoin[i];
	}
	floatingCoin.clear();
	/// Reset hidden box
	for (int i = 0; i < hiddenBoxes.size(); i++)
	{
		hiddenBoxes[i]->Reset();
		delete hiddenBoxes[i];
	}
	hiddenBoxes.clear();
	/// Reset Brick
	for (int i = 0; i < bricks.size(); i++)
	{
		delete bricks[i];
	}
	bricks.clear();
	/// Reset Brick Particles
	for (int i = 0; i < brickParticles.size(); i++)
	{
		brickParticles[i]->Reset();
		delete brickParticles[i];
	}
	brickParticles.clear();
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
	/// Reset Flower
	for (int i = 0; i < flowers.size(); i++)
	{
		flowers[i]->Reset();
		delete flowers[i];
	}
	flowers.clear();
	/// Reset coin
	for (int i = 0; i < coins.size(); i++)
	{
		coins[i]->Reset();
	}
	/// Reset bridge
	for (int i = 0; i < bridges.size(); i++)
	{
		delete bridges[i];
	}
	bridges.clear();
	coins.clear();
}