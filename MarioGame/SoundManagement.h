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
    // Static method to access the singleton instance
    static SoundManager& getInstance()
    {
        static SoundManager instance; 
        return instance;
    }

    // Load a sound effect by name
    bool loadSound(const std::string& name, const std::string& filepath);

    // Play a sound effect by name
    void playSound(const std::string& name);

    // Stop a sound effect by name
    void stopSound(const std::string& name);

    // Setter/Getter
    bool getPlayedStatus(const std::string& name);
    void setPlayedStatus(const std::string& name, const bool& value);

    void setLoop(const std::string& name, const bool& value);
};