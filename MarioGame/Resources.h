#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>

class Resources
{
public:
	// Link filename with a texture using std::map
	static std::unordered_map<std::string, sf::Texture> textures;
};

