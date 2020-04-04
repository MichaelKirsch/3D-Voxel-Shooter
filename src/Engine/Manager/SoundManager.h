#pragma once

#include <map>
#include "SFML/Audio.hpp"

class SoundManager {
public:
    enum Playstates
    {
        Play,Pause,Stop
    };
    SoundManager();
    int requestBuffering(std::string name, std::string filename);

    sf::Int16 getSound();
    void playSound(std::string name);


    void setSoundStatus(std::string name, Playstates state = Play);

    ~SoundManager() = default;

private:

    sf::Int16 findInMap(std::string name);

    sf::Music background_music;
    const int max_buffer_size = 250;
    std::map<std::string,sf::Int16> loadedSounds;
    std::string path_to_soundfolder;
    sf::SoundBuffer buffer;
    sf::Sound sound;
protected:
};



