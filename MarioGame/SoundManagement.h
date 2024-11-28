#pragma once
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
#include <utility>
class SoundManager
{
private:
    // Map for storing sound buffers (for sound effects)
    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;

    // Map for storing sound objects associated with the sound buffers
    std::unordered_map<std::string, std::pair<sf::Sound, bool>> sounds;

    // Private constructor to prevent instantiation
    SoundManager() {}

    // Delete copy constructor and assignment operator
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;
public:
    static SoundManager& getInstance()
    {
        static SoundManager instance; 
        return instance;
    }

    // Functions
    bool loadSound(const std::string& name, const std::string& filepath);
    void playSound(const std::string& name);
    void stopSound(const std::string& name);
    void setLoop(const std::string& name, const bool& value);

    // Setter/Getter
    bool getPlayedStatus(const std::string& name);
    void setPlayedStatus(const std::string& name, const bool& value);
};