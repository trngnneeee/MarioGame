#include "Animation.h"

Animation::Animation(float length)
	: time(0.0f), length(length)
{
}

void Animation::addFrame(Frame frame)
{
	frames.push_back(frame);
}

sf::Texture* Animation::update(float deltaTime)
{
	time += deltaTime;
	while (time >= length)
		time -= length;
	for (auto& frame : frames)
	{
		if (time <= frame.time)
			return frame.texture;
	}
	return nullptr;
}
