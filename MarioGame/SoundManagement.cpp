#include "SoundManagement.h"

bool SoundManager::loadSound(const std::string& name, const std::string& filepath)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filepath)) {
        return false;
    }

    soundBuffers[name] = buffer;
    sounds[name].first.setBuffer(soundBuffers[name]);
    sounds[name].second = false;
    return true;
}

void SoundManager::playSound(const std::string& name)
{
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        it->second.first.play();
    }
}

void SoundManager::stopSound(const std::string& name)
{
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        it->second.first.stop();
    }
}

bool SoundManager::getPlayedStatus(const std::string& name)
{
    auto it = sounds.find(name);
    if (it != sounds.end())
        return it->second.second;


    return false;
}

void SoundManager::setPlayedStatus(const std::string& name, const bool& value)
{
    auto it = sounds.find(name);
    if (it != sounds.end())
        it->second.second = value;
}

void SoundManager::setLoop(const std::string& name, const bool& value)
{
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        it->second.first.setLoop(value);
    }
}

void SoundManager::setVolume(const std::string& name, const int& value)
{
    if (value < 0 || value > 100) {
        throw std::out_of_range("Volume must be between 0 and 100.");
    }

    auto it = sounds.find(name);
    if (it != sounds.end()) {
        it->second.first.setVolume(value);
    }
    else {
        throw std::invalid_argument("Sound not found: " + name);
    }
}
