#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

struct Frame {
	Frame(sf::Texture* texture, float time)
		: texture(texture), time(time)
	{
	}
	sf::Texture* texture;
	float time;
};

class Animation
{
private:
	std::vector<Frame> frames;
	float length;
	float time;
public:
	Animation(float length);
	void addFrame(Frame frame);
	sf::Texture* update(float deltaTime);
	void Reset();
};

