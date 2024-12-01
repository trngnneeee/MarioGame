#pragma once
class GameTime
{
private:
	float timeAccumulator;
	int gameTime;
public:
	// Functions
	void Begin();
	void Update(const float& deltaTime);

	// Setter/Getter
	int getGameTime();
	void setGameTime(const int& value);
};

